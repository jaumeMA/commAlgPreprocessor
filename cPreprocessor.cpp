#include "cPreprocessor.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "cMacroInvoker.h"
#include "cMacroCall.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>

FILE* errFile;

namespace preprocessor
{
    std::string collapsePath(const std::string& path)
    {
        std::string res;

        std::string::const_iterator itChar = path.begin();
        size_t counter = 0;
        for(;itChar!=path.end();itChar++,counter++)
        {
            if(*itChar == '/')
            {
                if(counter > 0 && *(itChar-1) == '/')
                {
                    continue;
                }
                else if(counter > 1 && *(itChar-1) == '.' && *(itChar-2) == '/')
                {
                    res.pop_back();

                    continue;
                }
            }

            res.push_back(*itChar);
        }

        return res;
    }


    cToken::cToken()
    : m_type(tokenType::NONE)
    {
    }
    cToken::cToken(const std::string& name, tokenType type)
    : m_name(name)
    , m_type(type)
    {
    }
    cPreprocessor::cProcessor::cProcessor()
    : m_pScanner(NULL)
    , m_pParser(NULL)
    {
    }
    cPreprocessor::cProcessor::cProcessor(const std::string& filename, cPreprocessor* handler)
    : m_pScanner(NULL)
    , m_pParser(NULL)
    {
        m_pScanner = new cScanner(handler,filename);
        m_pParser = new cParser(*m_pScanner,handler);
    }
    cPreprocessor::cProcessor::cProcessor(const cProcessor& other)
    : m_pScanner(NULL)
    , m_pParser(NULL)
    {
        if(other.m_pScanner)
        {
            m_pScanner = new cScanner(*other.m_pScanner);
        }

        if(other.m_pParser)
        {
            m_pParser = new cParser(*other.m_pParser);
        }
    }
    cPreprocessor::cProcessor::cProcessor(cProcessor&& other)
    : m_pScanner(NULL)
    , m_pParser(NULL)
    {
        if(other.m_pScanner)
        {
            m_pScanner = new cScanner(*other.m_pScanner);
            other.m_pScanner = NULL;
        }

        if(other.m_pParser)
        {
            m_pParser = new cParser(*other.m_pParser);
            other.m_pParser = NULL;
        }
    }
    cPreprocessor::cProcessor::~cProcessor()
    {
        if(m_pScanner)
        {
            delete m_pScanner;
        }
        if(m_pParser)
        {
            delete m_pParser;
        }
    }
    cPreprocessor::cProcessor& cPreprocessor::cProcessor::operator=(const cProcessor& other)
    {
        //delete previous parser and scanner
        if(m_pScanner)
        {
            delete m_pScanner;
        }
        if(m_pParser)
        {
            delete m_pParser;
        }

        //create new parser and scanner
        if(other.m_pScanner)
        {
            m_pScanner = new cScanner(*other.m_pScanner);
        }

        if(other.m_pParser)
        {
            m_pParser = new cParser(*other.m_pParser);
        }

        return *this;
    }
    cPreprocessor::cProcessor& cPreprocessor::cProcessor::operator=(cProcessor&& other)
    {
        //delete previous parser and scanner
        if(m_pScanner)
        {
            delete m_pScanner;
        }
        if(m_pParser)
        {
            delete m_pParser;
        }

        //create new parser and scanner
        if(other.m_pScanner)
        {
            m_pScanner = other.m_pScanner;
            other.m_pScanner = NULL;
        }

        if(other.m_pParser)
        {
            m_pParser = other.m_pParser;
            other.m_pParser = NULL;
        }

        return *this;
    }
    bool cPreprocessor::cProcessor::operator==(const cProcessor& other) const
    {
        return m_pScanner==other.m_pScanner && m_pParser==other.m_pParser;
    }
    int cPreprocessor::cProcessor::eval(const std::string& formulae)
    {
        cScanner scanner(NULL);
        cParser parser(scanner,NULL);

        return scanner.eval(formulae, parser);
    }
    void cPreprocessor::cProcessor::preprocess()
    {
        m_pParser->parse();
    }
    void cPreprocessor::cProcessor::pushParsingFile(const std::string& relPath, const std::string& filename, bool isSystemHeader)
    {
        if(m_pScanner)
        {
            m_pScanner->pushFileToParse(relPath, filename, isSystemHeader);
        }
    }
    void cPreprocessor::cProcessor::popParsingFile()
    {
        if(m_pScanner)
        {
            m_pScanner->popFileToParse();
        }
    }
    const cScanner* cPreprocessor::cProcessor::getScanner() const
    {
        return m_pScanner;
    }
    const cParser* cPreprocessor::cProcessor::getParser() const
    {
        return m_pParser;
    }

    cPreprocessor::cScope::cScope(cScope* parent)
    : m_pParent(parent)
    , m_state(cPreprocessorState::RECEIVING_TOKENS)
    {
    }
    cPreprocessor::cScope* cPreprocessor::cScope::getParent() const
    {
        return m_pParent;
    }
    void cPreprocessor::cScope::setLocalState(const cPreprocessorState& state)
    {
        if(m_state != state)
        {
            m_state = state;
        }

        return;
    }
    cPreprocessorState cPreprocessor::cScope::getLocalState() const
    {
        return m_state;
    }
    cPreprocessorState cPreprocessor::cScope::getState() const
    {
        //construct state towards begin
        cPreprocessorState res = m_state;
        cScope* pParent = m_pParent;

        while(pParent)
        {
            if(pParent->getLocalState() == cPreprocessorState::DISCARDING_TOKENS || pParent->getLocalState() == cPreprocessorState::CLOSED_SCOPE)
            {
                res = pParent->getLocalState();

                break;
            }

            pParent = pParent->getParent();
        }

        return res;
    }
    cPreprocessor::cScope* cPreprocessor::cScope::pushScope()
    {
        return new cScope(this);
    }
    cPreprocessor::cScope* cPreprocessor::cScope::popScope()
    {
        cScope* res = m_pParent;

        delete this;

        return res;
    }

    cPreprocessor::cPreprocessor(const std::string& compiler)
    : IPreprocessor()
    , m_initialized(false)
    , m_pCurrScope(&m_mainScope)
    , m_invoker(*this)
    {
        init(compiler);
    }

    template<>
    void cPreprocessor::treatPragma<cPreprocessor::PRAGMA_ONCE>(const std::vector<cToken>& directive)
    {
        ASSERT(!directive.empty(), "Treating an empty pragma!");

        const std::string& filename = m_processor.getScanner()->getCurrFile();

        if(!isExcludedFile(filename))
        {
            m_excludedFiles.push_back(filename);
        }

        return;
    }
    std::string cPreprocessor::getSystemPath(const std::string& filename, bool incrSearch) const
    {
        std::vector<std::string>::const_iterator itPath;

        if(incrSearch)
        {
            std::string currRelPath = m_processor.getScanner()->getCurrFileRelPath();
            itPath = std::find(m_systemSearchPath.begin(),m_systemSearchPath.end(),currRelPath);
            if(itPath != m_systemSearchPath.end()) itPath++;
        }
        else
        {
            itPath = m_systemSearchPath.begin();
        }

        for(;itPath!=m_systemSearchPath.end();itPath++)
        {
            std::string absPath = (*itPath) + "/" + filename;
            struct stat buf;
            stat(absPath.c_str(),&buf);

            if(S_ISREG(buf.st_mode))
            {
                return *itPath;
            }
        }

        return std::string();
    }
    std::string cPreprocessor::getLocalPath(const std::string& filename, bool getLocal) const
    {
        if(getLocal)
        {
            std::string currRelPath = m_processor.getScanner()->getCurrFileRelPath();
            std::string absPath = currRelPath + "/" + filename;
            struct stat buf;
            stat(absPath.c_str(),&buf);

            if(S_ISREG(buf.st_mode))
            {
                return currRelPath;
            }
        }

        std::vector<std::string>::const_iterator itPath = m_localSearchPath.begin();
        for(;itPath!=m_localSearchPath.end();itPath++)
        {
            std::string absPath = (*itPath) + "/" + filename;
            struct stat buf;
            stat(absPath.c_str(),&buf);

            if(S_ISREG(buf.st_mode))
            {
                return *itPath;
            }
        }

        return std::string();
    }
    std::pair<std::string,std::string> cPreprocessor::getPath(const std::string& filename, bool incrSearch, bool isSystemHeader) const
    {
        std::pair<std::string,std::string> fileTokens;

        size_t baseNamePos = filename.find_last_of('/');

        if(baseNamePos != std::string::npos)
        {
            fileTokens.first = filename.substr(0,baseNamePos);
            fileTokens.second = filename.substr(baseNamePos+1);
        }
        else
        {
            fileTokens.second = filename;
        }

        std::string res = getLocalPath(filename, !isSystemHeader);

        if(!res.empty())
        {
            return std::make_pair(collapsePath((fileTokens.first.empty()) ? res : res + "/" + fileTokens.first),fileTokens.second);
        }
        else
        {
            res = getSystemPath(filename, incrSearch);

            if(!res.empty())
            {
                return std::make_pair(collapsePath((fileTokens.first.empty()) ? res : res + "/" + fileTokens.first),fileTokens.second);
            }
        }

        return std::make_pair(std::string(),std::string());
    }

    void cPreprocessor::init(const std::string& compiler)
    {
        m_builtInMacros["__Base_File__"] = new cBaseFileMacro(m_inputFile);
        m_builtInMacros["__Include_Level__"] = new cIncludeLevelMacro();
        m_builtInMacros["__Concat__"] = new cConcatMacro();
        m_builtInMacros["__CollapseVariadic__"] = new cCollapseVariadic();
        m_builtInMacros["__Stringized__"] = new cStringized();

        m_systemSearchPath.push_back("/usr/lib/gcc/i686-linux-gnu/4.8/include");
        m_systemSearchPath.push_back("/usr/lib/gcc/i686-linux-gnu/4.8/include-fixed");
        m_systemSearchPath.push_back("/usr/include");
        m_systemSearchPath.push_back("/usr/include/c++/4.8");
        m_systemSearchPath.push_back("/usr/include/c++/4.8/tr1");
        m_systemSearchPath.push_back("/usr/include/i386-linux-gnu");
        m_systemSearchPath.push_back("/usr/include/i386-linux-gnu/c++/4.8");
    }

    void cPreprocessor::deInit()
    {
        std::map<std::string,IMacro*>::iterator itBuiltInMacro = m_builtInMacros.begin();
        for(;itBuiltInMacro!=m_builtInMacros.end();itBuiltInMacro++)
        {
            delete (*itBuiltInMacro).second;
        }
        m_builtInMacros.clear();
    }

    bool cPreprocessor::preprocess(const std::string& filename, const std::string& outputFile, const std::vector<std::string>& searchPath, const std::vector<std::string>& flags)
    {
        bool res = false;

        m_localSearchPath = searchPath;
        m_flags = flags;
        m_outputFile = (!outputFile.empty()) ? outputFile : filename + ".i";

        //execute in order the different stages of a preprocessor
        if(!filename.empty())
        {
            //firs of all convert contents of input file into tokens and acquire macro definitions
            m_inputFile = filename;
            parse(filename);
            //once this is done, expand all macros present in parsed tokens
            expand();

            //save it to proper file
            save();

            res = true;
        }


        return res;
    }

    void cPreprocessor::parse(const std::string& filename)
    {
        m_processor = cProcessor(filename,this);

        m_processor.preprocess();

        return;
    }

    void cPreprocessor::expand()
    {

        return;
    }

    void cPreprocessor::save()
    {
        std::filebuf fb;

        fb.open (m_outputFile,std::ios::out);
        std::ostream os(&fb);

        for(const cToken& _token : m_tokens)
        {
            os << _token.m_name;
        }

        fb.close();
    }

    void cPreprocessor::forwardToken(const cToken& token)
    {
        ASSERT(m_pCurrScope,"New token with null scope!");

        if(m_pCurrScope->getState() == cPreprocessorState::RECEIVING_TOKENS)
        {
            std::vector<cToken> expandedMacro = m_invoker.expand(token);

            m_tokens.insert(m_tokens.end(),expandedMacro.begin(),expandedMacro.end());
        }
    }

    bool cPreprocessor::isExcludedFile(const std::string& filename) const
    {
        return std::find(m_excludedFiles.begin(),m_excludedFiles.end(),filename) != m_excludedFiles.end();
    }

    void cPreprocessor::startPreprocessing()
    {
        return;
    }

    void cPreprocessor::endPreprocessing()
    {

        return;
    }

    void cPreprocessor::newIf(bool cond)
    {
        ASSERT(m_pCurrScope, "Attempting to push scope while no current scope!");

        m_pCurrScope = m_pCurrScope->pushScope();

        m_pCurrScope->setLocalState(cond ? cPreprocessorState::RECEIVING_TOKENS : cPreprocessorState::DISCARDING_TOKENS);
    }
    void cPreprocessor::newElse(bool cond)
    {
        ASSERT(m_pCurrScope, "Attempting to push scope while no current scope!");

        if(m_pCurrScope->getState() == cPreprocessorState::RECEIVING_TOKENS)
        {
            m_pCurrScope->setLocalState(cPreprocessorState::CLOSED_SCOPE);
        }
        else if(m_pCurrScope->getState() == cPreprocessorState::DISCARDING_TOKENS)
        {
            if(cond)
            {
                m_pCurrScope->setLocalState(cPreprocessorState::RECEIVING_TOKENS);
            }
            else
            {
                //do nothing
            }
        }
        else if(m_pCurrScope->getState() == cPreprocessorState::CLOSED_SCOPE)
        {
            //do nothing
        }
        else
        {
            ASSERT(false, "Unconsistent scope!");
        }
    }
    void cPreprocessor::newIfEnd()
    {
        ASSERT(m_pCurrScope, "Attempting to push scope while no current scope!");

        m_pCurrScope = m_pCurrScope->popScope();
    }
    void cPreprocessor::newInclude(const cToken& fileName, bool isSystemHeader, bool incrSearch)
    {
        ASSERT(m_pCurrScope,"New token with null scope!");

        if(m_pCurrScope->getState() == cPreprocessorState::RECEIVING_TOKENS)
        {
            std::pair<std::string,std::string> path = getPath(fileName.m_name, incrSearch, isSystemHeader);
            std::string fullPath = collapsePath(path.first + "/" + path.second);

            std::string errorMsg = std::string("Empty path: ") + fileName.m_name;
            ASSERT((!path.first.empty() && !path.second.empty()), errorMsg.c_str());

            if(!isExcludedFile(fullPath))
            {
                //in this case, create a new parser and start parsing filename
                if(!fullPath.empty())
                {
                    if(fileName.m_name == "stdarg.h" || fileName.m_name == "cstdarg")
                    {
                        int a = 0;
                        a++;
                    }

                    m_processor.pushParsingFile(path.first, fullPath, isSystemHeader);
                }
            }
        }

        return;
    }

    void cPreprocessor::newFailMsg(const std::vector<cToken>& failMsg, cFailMsgType level)
    {
        ASSERT(m_pCurrScope,"New token with null scope!");

        if(m_pCurrScope->getState() == cPreprocessorState::RECEIVING_TOKENS)
        {
            //stop preprocessing!
            std::string errorMsg = "Error in: ";
            errorMsg += m_processor.getScanner()->getCurrFile();
            errorMsg += ", line: ";
            errorMsg += m_processor.getScanner()->getCurrLine();
            ASSERT(false, errorMsg.c_str());
        }

        return;
    }

    void cPreprocessor::newPragma(const std::vector<cToken>& directive)
    {
        ASSERT(m_pCurrScope,"New token with null scope!");

        if(m_pCurrScope->getState() == cPreprocessorState::RECEIVING_TOKENS)
        {
            ASSERT(directive.size() > 0, "Empty pragma!");

            if(directive[0].m_name == "GCC")
            {
                //GCC specific pragma

            }
            else
            {
                //standard pragmas
                if(directive[0].m_name == "once")
                {
                    treatPragma<PRAGMA_ONCE>(directive);
                }
            }
        }

        return;
    }

    void cPreprocessor::defineMacro(const cToken& name, const std::vector<cToken>& vars, const std::vector<cToken>& body, cMacroType type)
    {
        ASSERT(m_pCurrScope,"New token with null scope!");

        if(m_pCurrScope->getState() == cPreprocessorState::RECEIVING_TOKENS)
        {
            //by language definition, macro shall not exist (scope independent)
            std::map<std::string,cMacro>::iterator itMacro = m_macros.find(name.m_name);

            ASSERT((itMacro==m_macros.end() || (*itMacro).second.m_assocCode==body), "Macro already has a definition");

            m_macros[name.m_name] = cMacro(name,vars,body,type);
        }
    }

    void cPreprocessor::undefMacro(const cToken& name)
    {
        ASSERT(m_pCurrScope,"New token with null scope!");

        if(m_pCurrScope->getState() == cPreprocessorState::RECEIVING_TOKENS)
        {
            std::map<std::string,cMacro>::iterator itMacro = m_macros.find(name.m_name);

            if(itMacro!=m_macros.end())
            {
                m_macros.erase(itMacro);
            }
        }
    }

    void cPreprocessor::newToken(const cToken& token)
    {
        forwardToken(token);

        return;
    }

    void cPreprocessor::newTokens(const std::vector<cToken>&  tokens)
    {
        std::vector<cToken>::const_iterator itToken = tokens.begin();

        for(;itToken!=tokens.end();itToken++)
        {
            forwardToken(*itToken);
        }
    }
    bool cPreprocessor::hasMacro(const cToken& name) const
    {
        if(name.m_name == "__ASSEMBLER__")
        {
            int a = 0;
            a++;
        }

        return m_builtInMacros.find(name.m_name)!=m_builtInMacros.end() || m_macros.find(name.m_name)!=m_macros.cend();
    }
    const IMacro& cPreprocessor::getMacro(const cToken& name) const
    {
        {
            std::map<std::string,IMacro*>::const_iterator itMacro = m_builtInMacros.find(name.m_name);

            if(itMacro != m_builtInMacros.end())
            {
                return *((*itMacro).second);
            }
        }

        {
            std::map<std::string,cMacro>::const_iterator itMacro = m_macros.find(name.m_name);

            if(itMacro != m_macros.end())
            {
                return (*itMacro).second;
            }
        }

        ASSERT(false, "Getting unexistent macro!");

        return cMacro();
    }
    int cPreprocessor::macroEval(const cToken& name, const std::vector<cToken>& args)
    {
        int res = 0;

        bool accepToken = m_pCurrScope->getParent() == NULL || m_pCurrScope->getParent()->getState() == cPreprocessorState::RECEIVING_TOKENS;

        if(accepToken)
        {
            std::map<std::string,cMacro>::const_iterator itMacro = m_macros.find(name.m_name);

            if((name.m_type == tokenType::IDENT_CALL || name.m_type == tokenType::IDENT) && hasMacro(name))
            {
                cMacroInvoker invoker(*this);
                cMacroCall callArgs(name);

                callArgs.openContext(')');

                std::vector<cToken>::const_iterator itArg = args.begin();
                for(;itArg!=args.end();itArg++)
                {
                    callArgs.pushArg(arg_t(1,*itArg));
                }

                callArgs.closeContext(')');

                std::vector<cToken> body = invoker.call(callArgs);
                std::vector<cToken>::iterator itToken = body.begin();
                std::string expandedCode;

                for(;itToken!=body.end();itToken++)
                {
                    const cToken& token = *itToken;
                    std::string localToken = token.m_name;

                    if(token.m_type == tokenType::IDENT)
                    {
                        localToken = std::to_string(macroEval(token, std::vector<cToken>()));
                    }
                    expandedCode += localToken;
                }

                //finally parse expression
                res = cProcessor::eval(expandedCode);
            }
            else if(name.m_type == tokenType::NUMBER)
            {
                res = stoi(name.m_name);
            }
        }

        return res;
    }
    void cPreprocessor::pushFile(const std::string& filename, const std::vector<int>& flags)
    {
        if(!m_processor.getScanner()->empty())
        {
            std::string msg = std::string("Entering file ") + filename;
            LOG(msg.c_str());
            flushLocationInfo(m_processor.getScanner()->getCurrFile(), m_processor.getScanner()->getCurrLine());
        }
    }
    void cPreprocessor::popFile(const std::string& filename)
    {
        if(!m_processor.getScanner()->empty())
        {
            flushLocationInfo(m_processor.getScanner()->getCurrFile(), m_processor.getScanner()->getCurrLine());
        }
    }
    void cPreprocessor::flushLocationInfo(const std::string& filename, int lineNumber)
    {
        std::string lineStr = "# ";

        std::ostringstream formatter;
        formatter << lineNumber;

        lineStr += formatter.str();

        lineStr += " \"";

        lineStr += filename;

        lineStr += std::string("\"");

        lineStr += std::string("\n");

        m_tokens.push_back(cToken(lineStr,tokenType::SYMBOL));
    }
    void cPreprocessor::newLine(int numLines)
    {
        for(int i=0;i<numLines;i++)
        {
            m_tokens.push_back(cToken("\n",tokenType::SYMBOL));
        }
    }
}

void handler(int sig)
{
    void *array[64];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}
//entry point
int main(int argc, char *argv[])
{
    signal(SIGSEGV, handler);
    errFile = fopen("./log.txt", "w+");

    ASSERT(argc >= 3, "Incorrect number of input arguments!");

    std::vector<std::string> searchPath;
    std::vector<std::string> flags;
    preprocessor::cPreprocessor *preprocessor = NULL;

    //the first two arguments are for input file and output file (by now)
    std::string compiler = std::string(argv[1]);
    std::string inputFile = std::string(argv[2]);
    std::string outputFile = std::string(argv[3]);

    for(u8 i=4;i<argc;i++)
    {
        searchPath.push_back(argv[i]);
        printf("Adding search path: %s", argv[i]);
    }

    std::cout << "Preprocessing file" << std::endl;

    preprocessor = new preprocessor::cPreprocessor(compiler);

    preprocessor->preprocess(inputFile,outputFile,searchPath,flags);

    delete preprocessor;

    fclose(errFile);

    return 0;
}

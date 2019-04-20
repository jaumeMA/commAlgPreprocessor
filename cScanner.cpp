#include "cScanner.h"
#include <fstream>
#include <sstream>

//we have to redefine those macros we dont see them from here :(
#define YY_BUF_SIZE 16384
#define YY_CURRENT_BUFFER ( (yy_buffer_stack) \
                          ? (yy_buffer_stack)[(yy_buffer_stack_top)] \
                          : NULL)
#define MAX_NUM_BUFFERS 10

namespace preprocessor
{
    cScanner::ProcessedFile::ProcessedFile(const std::string& relPath, const std::string& filename, bool isSystemHeader)
    : m_pStream(NULL)
    , m_relPath(relPath)
    , m_filename(filename)
    , m_line(1)
    , m_word(0)
    , m_isSystemHeader(isSystemHeader)
    {
        m_pStream = new std::ifstream(filename.c_str());
    }
    cScanner::ProcessedFile::ProcessedFile(const ProcessedFile& other)
    : m_pStream(NULL)
    , m_line(other.m_line)
    , m_word(other.m_word)
    , m_isSystemHeader(other.m_isSystemHeader)
    {
        m_filename = other.m_filename;
        m_relPath = other.m_relPath;

        if(other.m_pStream)
        {
            m_pStream = new std::ifstream(other.m_filename.c_str());
        }
    }
    cScanner::ProcessedFile::ProcessedFile(ProcessedFile&& other)
    : m_pStream(NULL)
    , m_line(other.m_line)
    , m_word(other.m_word)
    , m_isSystemHeader(other.m_isSystemHeader)
    {
        m_filename = std::move(other.m_filename);
        m_relPath = std::move(other.m_relPath);

        if(other.m_pStream)
        {
            m_pStream = other.m_pStream;
            other.m_pStream = NULL;
        }
    }
    cScanner::ProcessedFile& cScanner::ProcessedFile::operator=(const ProcessedFile& other)
    {
        if(m_pStream)
        {
            delete m_pStream;
            m_filename.clear();
        }

        if(other.m_pStream)
        {
            m_line = other.m_line;
            m_word = other.m_word;
            m_filename = other.m_filename;
            m_relPath = other.m_relPath;
            m_isSystemHeader = other.m_isSystemHeader;
            m_pStream = new std::ifstream(other.m_filename.c_str());
        }

        return *this;
    }
    cScanner::ProcessedFile& cScanner::ProcessedFile::operator=(ProcessedFile&& other)
    {
        if(m_pStream)
        {
            delete m_pStream;
            m_filename.clear();
        }

        if(other.m_pStream)
        {
            m_line = other.m_line;
            m_word = other.m_word;
            m_filename = std::move(other.m_filename);
            m_relPath = std::move(other.m_relPath);
            m_isSystemHeader = other.m_isSystemHeader;
            m_pStream = other.m_pStream;
            other.m_pStream = NULL;
        }

        return *this;
    }

    cScanner::cScanner(IFileProcessor* fileProcessor, const std::string& filename)
    : m_fileProcessor(fileProcessor)
    , m_underEval(false)
    {
        m_filesToProcess.reserve(MAX_NUM_BUFFERS);

        m_filesToProcess.push_back(ProcessedFile("./", filename));

        const ProcessedFile& processor = m_filesToProcess.back();

        yypush_buffer_state(yy_create_buffer(processor.m_pStream,YY_BUF_SIZE));
    }
    cScanner::cScanner(IFileProcessor* fileProcessor)
    : m_fileProcessor(fileProcessor)
    , m_underEval(false)
    {
        m_filesToProcess.reserve(MAX_NUM_BUFFERS);
    }
    cScanner::cScanner(const cScanner& other)
    : m_fileProcessor(other.m_fileProcessor)
    , m_filesToProcess(other.m_filesToProcess)
    , m_underEval(other.m_underEval)
    {
        if(!m_filesToProcess.empty())
        {
            const ProcessedFile& processor = m_filesToProcess.back();
            yypush_buffer_state(yy_create_buffer(processor.m_pStream,YY_BUF_SIZE));
        }
    }
    cScanner::~cScanner()
    {
    }
    cScanner& cScanner::operator=(const cScanner& other)
    {
        m_filesToProcess = other.m_filesToProcess;
        m_underEval = other.m_underEval;

        if(!m_filesToProcess.empty())
        {
            const ProcessedFile& processor = m_filesToProcess.back();
            yy_switch_to_buffer(yy_create_buffer(processor.m_pStream,YY_BUF_SIZE));
        }

        return *this;
    }
    cScanner& cScanner::operator=(cScanner&& other)
    {
        m_filesToProcess = std::move(other.m_filesToProcess);
        m_underEval = other.m_underEval;

        if(!m_filesToProcess.empty())
        {
            const ProcessedFile& processor = m_filesToProcess.back();
            yy_switch_to_buffer(yy_create_buffer(processor.m_pStream,YY_BUF_SIZE));
        }

        return *this;
    }
    int cScanner::yylex(cParser::semantic_type* lval)
    {
        yylval = lval;

        if(!empty())
        {
            ProcessedFile& currProcessingFile = m_filesToProcess.back();

            currProcessingFile.m_word++;
        }

        return yylex();
    }
    int cScanner::eval(const std::string& formulae, cParser& parser)
    {
        std::istringstream input(std::string("#__compute__ ") + formulae);

        ASSERT(!m_underEval, "Evaluating an expression while evaluating another one!");

        m_underEval = true;

        yypush_buffer_state(yy_create_buffer(&input,YY_BUF_SIZE));

        parser.parse();

        return getComputeValue();
    }
    void cScanner::pushFileToParse(const std::string& relPath, const std::string& filename, bool isSystemHeader)
    {
        m_filesToProcess.push_back(ProcessedFile(relPath, filename, isSystemHeader));

        const ProcessedFile& processor = m_filesToProcess.back();

        if(m_fileProcessor)
        {
            std::vector<int> flags;
            flags.push_back(1);

            if(isSystemHeader)
            {
                flags.push_back(3);
            }

            m_fileProcessor->pushFile(filename, flags);
        }

        yypush_buffer_state(yy_create_buffer(processor.m_pStream,YY_BUF_SIZE));
    }
    void cScanner::popFileToParse()
    {
        if(!empty())
        {
            ProcessedFile& currProcessingFile = m_filesToProcess.back();
            std::string filename = currProcessingFile.m_filename;

            char msgLine[32];
            memset(msgLine,0,sizeof(char)*32);
            sprintf(msgLine," in line %d and word %d",currProcessingFile.m_line, currProcessingFile.m_word);

            m_filesToProcess.pop_back();

            if(m_fileProcessor)
            {
                std::string msg = std::string("Leaving file ") + filename + std::string(msgLine);
                LOG(msg.c_str());
                m_fileProcessor->popFile(filename);
            }

            yypop_buffer_state();
        }
    }
    bool cScanner::finishedStream()
    {
        if(m_underEval)
        {
            yypop_buffer_state();
            m_underEval = false;
        }
        else
        {
            popFileToParse();

            if(!empty())
            {
                ProcessedFile& currProcessingFile = m_filesToProcess.back();
                std::vector<int> flags;
                flags.push_back(2);

                if(currProcessingFile.m_isSystemHeader)
                {
                    flags.push_back(3);
                }

                m_fileProcessor->pushFile(currProcessingFile.m_filename, flags);

                return false;
            }
            else
            {
                return true;
            }
        }

        return empty();
    }
    bool cScanner::empty() const
    {
        return m_filesToProcess.empty();
    }
    void cScanner::incrCurrLine()
    {
        ASSERT(!m_filesToProcess.empty(), "Empty processing file stack!");

        ProcessedFile& currProcessingFile = m_filesToProcess.back();

        currProcessingFile.m_line++;

        yylineno++;
    }
    void cScanner::flushLocationInfo() const
    {
        if(!m_filesToProcess.empty())
        {
            m_fileProcessor->flushLocationInfo(getCurrFile(),getCurrLine());
        }
    }
    size_t cScanner::getCurrLine() const
    {
        ASSERT(!m_filesToProcess.empty(), "Empty processing file stack!");

        const ProcessedFile& currProcessingFile = m_filesToProcess.back();

        return currProcessingFile.m_line;
    }
    std::string cScanner::getCurrFile() const
    {
        ASSERT(!m_filesToProcess.empty(), "Empty processing file stack!");

        const ProcessedFile& currProcessingFile = m_filesToProcess.back();

        return currProcessingFile.m_filename;
    }
    std::string cScanner::getCurrFileRelPath() const
    {
        ASSERT(!m_filesToProcess.empty(), "Empty processing file stack!");

        const ProcessedFile& currProcessingFile = m_filesToProcess.back();

        return currProcessingFile.m_relPath;
    }
    void cScanner::setComputeValue(int val)
    {
        m_computeVal = val;
    }
    int cScanner::getComputeValue() const
    {
        return m_computeVal;
    }
}

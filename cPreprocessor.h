#pragma once

#include <map>
#include "cScanner.h"
#include "IPreprocessor.h"
#include "cMacroInvoker.h"
#include "cMacro.h"

extern FILE* errFile;

namespace preprocessor
{
    struct cPreprocessorStateDef
    {
        enum type
        {
            RECEIVING_TOKENS = 1<<0,
            DISCARDING_TOKENS = 1<<1,
            CLOSED_SCOPE = 1<<2
        };
    };

    typedef safe_enum<cPreprocessorStateDef> cPreprocessorState;

    class cPreprocessor : public IPreprocessor, public IFileProcessor
    {
        friend std::vector<cToken> cMacroInvoker::_expand(const cToken&);
        friend std::vector<cToken> cMacroInvoker::call(const cMacroCall&);

        enum
        {
            PRAGMA_ONCE=0,
            NONE
        };

        public:
            cPreprocessor(const std::string& compiler);
            bool preprocess(const std::string& filename, const std::string& outputFile, const std::vector<std::string>& searchPath, const std::vector<std::string>& flags);

        private:
            struct cProcessor
            {
                cProcessor();
                cProcessor(const std::string& filename, cPreprocessor* handler);
                cProcessor(const cProcessor& other);
                cProcessor(cProcessor&& other);
                ~cProcessor();

                cProcessor& operator=(const cProcessor& other);
                cProcessor& operator=(cProcessor&& other);
                bool operator==(const cProcessor& other) const;

                static int eval(const std::string& formulae);
                void preprocess();
                void pushParsingFile(const std::string& relPath, const std::string& filename, bool isSystemHeader);
                void popParsingFile();
                const cScanner* getScanner() const;
                const cParser* getParser() const;

                private:
                    cScanner*       m_pScanner;
                    cParser*        m_pParser;
            };

            struct cScope
            {
                cScope*             m_pParent;
                cPreprocessorState  m_state;

                cScope(cScope* parent=NULL);
                void setLocalState(const cPreprocessorState& state);
                cPreprocessorState getLocalState() const;
                cPreprocessorState getState() const;
                cScope* pushScope();
                cScope* popScope();
                cScope* getParent() const;
            };

            //preprocessor interface
            void startPreprocessing();
            void endPreprocessing();
            void newLine(int numLines);
            void newIf(bool cond);
            void newElse(bool cond);
            void newIfEnd();
            void newInclude(const cToken& fileName, bool isSystemHeader, bool incrSearch);
            void newFailMsg(const std::vector<cToken>& failMsg, cFailMsgType level);
            void newPragma(const std::vector<cToken>& directive);
            void defineMacro(const cToken& name, const std::vector<cToken>& vars, const std::vector<cToken>& body, cMacroType type);
            void undefMacro(const cToken& name);
            void newToken(const cToken& token);
            void newTokens(const std::vector<cToken>&  tokens);
            bool hasMacro(const cToken& name) const;
            const IMacro& getMacro(const cToken& name) const;
            int macroEval(const cToken& name, const std::vector<cToken>& args);

            // IFileProcessor interface
            void pushFile(const std::string& filename, const std::vector<int>& flags);
            void popFile(const std::string& filename);
            void flushLocationInfo(const std::string& filename, int lineNumber);


            void init(const std::string& compiler);
            void deInit();

            //translation phases
            void parse(const std::string& filename);
            void expand();
            void save();

            //facilities
            void forwardToken(const cToken& token);
            bool isExcludedFile(const std::string& filename) const;
            template<int type>
            void treatPragma(const std::vector<cToken>& directive)
            {
                static_assert(type==-1, "Unsupported pragma");
            }
            std::pair<std::string,std::string> getPath(const std::string& filename, bool incrSearch, bool isSystemHeader) const;
            std::string getSystemPath(const std::string& filename, bool incrSearch) const;
            std::string getLocalPath(const std::string& filename, bool getLocal) const;

            bool                            m_initialized;
            cScope                          m_mainScope;
            cScope*                         m_pCurrScope;
            std::string                     m_inputFile;
            std::string                     m_outputFile;
            cProcessor                      m_processor;
            cMacroInvoker                   m_invoker;
            std::vector<cToken>             m_tokens;
            std::map<std::string,IMacro*>   m_builtInMacros;
            std::map<std::string,cMacro>    m_macros;
            std::vector<std::string>        m_excludedFiles;
            std::vector<std::string>        m_systemSearchPath;
            std::vector<std::string>        m_localSearchPath;
            std::vector<std::string>        m_flags;
    };
}


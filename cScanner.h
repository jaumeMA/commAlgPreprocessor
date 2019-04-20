#pragma once

#if !defined(yyFlexLexerOnce)
#define yyFlexLexer preproc_FlexLexer
#include <FlexLexer.h>
#endif

//redefine yylex
#undef YY_DECL
#define YY_DECL int preprocessor::cScanner::yylex()

#include "preprocessor/preProcessor.tab.hpp"

namespace preprocessor
{
    class cParser;

    class cScanner : public preproc_FlexLexer
    {
        public:
            cScanner(IFileProcessor* fileProcessor = NULL);
            cScanner(IFileProcessor* fileProcessor, const std::string& filename);
            cScanner(const cScanner& other);
            ~cScanner();

            cScanner& operator=(const cScanner& other);
            cScanner& operator=(cScanner&& other);

            int yylex(cParser::semantic_type* lval);
            int eval(const std::string& formulae, cParser& parser);
            void popFileToParse();
            void pushFileToParse(const std::string& relPath, const std::string& filename, bool isSystemHeader);
            bool empty() const;
            void incrCurrLine();
            void flushLocationInfo() const;
            size_t getCurrLine() const;
            std::string getCurrFile() const;
            std::string getCurrFileRelPath() const;
            void setComputeValue(int val);
            int getComputeValue() const;
            bool finishedStream();

        private:
            struct ProcessedFile
            {
                std::istream*           m_pStream = NULL;
                std::string             m_relPath;
                std::string             m_filename;
                size_t                 m_line;
                size_t                  m_word;
                bool                    m_isSystemHeader;

                ProcessedFile(const std::string& relPath, const std::string& filename, bool isSystemHeader=false);
                ProcessedFile(const ProcessedFile& other);
                ProcessedFile(ProcessedFile&& other);
                ProcessedFile& operator=(const ProcessedFile& other);
                ProcessedFile& operator=(ProcessedFile&& other);
            };

            int yylex();

            IFileProcessor*             m_fileProcessor;
            cParser::semantic_type*     yylval;
            std::vector<ProcessedFile>  m_filesToProcess;
            int                         m_computeVal;
            bool                        m_underEval;
    };
}

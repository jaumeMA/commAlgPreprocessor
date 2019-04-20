#pragma once

#include <string>
#include <vector>
#include "cPreProcessorDefs.h"

static const int cplusplus = 201103L;

namespace preprocessor
{
    struct tokenTypeDef
    {
        enum type
        {
            NONE,
            IDENT,
            IDENT_CALL,
            NUMBER,
            SYMBOL,
            LITERAL
        };
    };

    typedef safe_enum<tokenTypeDef> tokenType;

    struct cToken
    {
        std::string     m_name;
        tokenType       m_type;

        cToken();
        cToken(const std::string& name, tokenType type);
        bool operator==(const cToken& other) const
        {
            return m_name==other.m_name && m_type==other.m_type;
        }
        bool operator!=(const cToken& other) const
        {
            return m_type!=other.m_type || m_name!=other.m_name;
        }
        bool empty() const
        {
            return m_type == tokenType::NONE;
        }
        void clear()
        {
            m_type = tokenType::NONE;
            m_name.clear();
        }
    };

    typedef std::vector<cToken> arg_t;

    struct cMacroTypeDef
    {
        enum type
        {
            OBJECT_LIKE,
            FUNCTION_LIKE,
            VARIADIC
        };
    };

    typedef safe_enum<cMacroTypeDef> cMacroType;

    struct cFailMsgTypeDef
    {
        enum type
        {
            WARNING,
            ERROR
        };
    };

    typedef safe_enum<cFailMsgTypeDef> cFailMsgType;

    struct IMacro
    {
        public:
            virtual ~IMacro() {};
            virtual std::vector<cToken> expand() const = 0;
            virtual std::vector<cToken> expand(const std::vector<arg_t>& args) const = 0;
            virtual cMacroType getType() const = 0;
    };

    class IFileProcessor
    {
        public:
            virtual ~IFileProcessor() {};
            virtual void pushFile(const std::string& filename, const std::vector<int>& flags) = 0;
            virtual void popFile(const std::string& filename) = 0;
            virtual void flushLocationInfo(const std::string& filename, int lineNumber) = 0;
    };

    class IPreprocessor
    {
        public:
            virtual ~IPreprocessor(){};
            virtual void startPreprocessing() = 0;
            virtual void endPreprocessing() = 0;
            virtual void newLine(int numLines) = 0;
            virtual void newIf(bool cond) = 0;
            virtual void newElse(bool cond) = 0;
            virtual void newIfEnd() = 0;
            virtual void newInclude(const cToken& fileName, bool isSystemHeader, bool incrSearch) = 0;
            virtual void newFailMsg(const std::vector<cToken>& failMsg, cFailMsgType level) = 0;
            virtual void newPragma(const std::vector<cToken>& directive) = 0;
            virtual void defineMacro(const cToken& name, const std::vector<cToken>& vars, const std::vector<cToken>& body, cMacroType type) = 0;
            virtual void undefMacro(const cToken& name) = 0;
            virtual void newToken(const cToken& token) = 0;
            virtual void newTokens(const std::vector<cToken>& token) = 0;
            virtual bool hasMacro(const cToken& name) const = 0;
            virtual const IMacro& getMacro(const cToken& name) const = 0;
            virtual int macroEval(const cToken& name, const std::vector<cToken>& args) = 0;
    };
}

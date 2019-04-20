#pragma once

#include <vector>
#include "IPreprocessor.h"

namespace preprocessor
{
    struct cBaseFileMacro : public IMacro
    {
        public:
            cBaseFileMacro(const std::string& filename);
            std::vector<cToken> expand() const;
            std::vector<cToken> expand(const std::vector<arg_t>& args) const;
            cMacroType getType() const;

        private:
            const std::string& m_baseFile;
    };

    struct cIncludeLevelMacro : public IMacro
    {
        public:
            cIncludeLevelMacro();
            std::vector<cToken> expand() const;
            std::vector<cToken> expand(const std::vector<arg_t>& args) const;
            cMacroType getType() const;
            void increment();
            void decrement();

        private:
            size_t m_currLevel;
    };

    struct cConcatMacro : public IMacro
    {
        public:
            std::vector<cToken> expand() const;
            std::vector<cToken> expand(const std::vector<arg_t>& args) const;
            cMacroType getType() const;
    };

    struct cCollapseVariadic : public IMacro
    {
        public:
            std::vector<cToken> expand() const;
            std::vector<cToken> expand(const std::vector<arg_t>& args) const;
            cMacroType getType() const;
    };

    struct cStringized : public IMacro
    {
        public:
            std::vector<cToken> expand() const;
            std::vector<cToken> expand(const std::vector<arg_t>& args) const;
            cMacroType getType() const;
    };

    struct cMacro : public IMacro
    {
        struct cVar
        {
            struct cVarTypeDef
            {
                enum type
                {
                    SINGLE,
                    VARIADIC
                };
            };

            typedef safe_enum<cVarTypeDef> cVarType;

            cVarType                m_type;
            size_t                  m_argPos;
            size_t                  m_codePos;

            cVar();
            cVar(const std::string& name, size_t argPos, size_t codePos);
        };
        //an object macro will be this one with zero vars
        std::vector<cVar>   m_occurrences;
        cToken              m_name;
        std::vector<cToken> m_assocCode;
        cMacroType          m_type;
        size_t              m_numArgs;
        bool                m_variadic;

        cMacro();
        cMacro(const cToken& name, const std::vector<cToken>& vars, const std::vector<cToken>& code, cMacroType type);
        std::vector<cToken> expand() const;
        std::vector<cToken> expand(const std::vector<arg_t>& args) const;
        cMacroType getType() const;
    };
}

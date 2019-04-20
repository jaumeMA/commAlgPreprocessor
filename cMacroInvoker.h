#pragma once

#include "IPreprocessor.h"
#include "cMacroCall.h"

namespace preprocessor
{
    class cPreprocessor;

    class cMacroInvoker
    {
        public:

            cMacroInvoker(cPreprocessor& handler);

            std::vector<cToken> expand(const std::vector<cToken>& tokens);
            std::vector<cToken> expand(const cToken& token);
            std::vector<cToken> _expand(const cToken& token);
            std::vector<cToken> call(const cMacroCall& macroCall);

        private:
            struct cInvoker
            {
                struct cInvokerStateDef
                {
                    enum type
                    {
                        RECEIVING_TOKENS,
                        PARSING_MACRO_PARAMS
                    };
                };

                typedef safe_enum<cInvokerStateDef> cInvokerState;

                cInvokerState   m_state;
                cMacroCall      m_macroCall;

                cInvoker();
                cInvoker(const cToken& call);
                cInvoker(const cToken& call, const cInvokerState& state);
                cMacroCall& getMacro();
                void setState(const cInvokerState& state);
                cInvokerState getState() const;
                bool operator==(const cToken& name) const;
            };

            cPreprocessor&              m_handler;
            std::vector<cInvoker>       m_expansionStack;
    };
}

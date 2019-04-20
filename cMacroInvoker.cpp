#include "cMacroInvoker.h"
#include "cPreprocessor.h"

#define CALL_PARSED_MACRO(_res_)    cInvoker& __currCall = m_expansionStack.back(); \
                                    cMacroCall _macro = __currCall.getMacro(); \
                                    cMacroCall __macro(_macro.m_name); \
                                    \
                                    __currCall.setState(cInvoker::cInvokerState::RECEIVING_TOKENS); \
                                    \
                                    __macro.openContext(')'); \
                                    \
                                    std::vector<arg_t>::iterator itArg = _macro.begin(); \
                                    for(;itArg!=_macro.end();itArg++) \
                                    { \
                                        __macro.pushArg(expand(*itArg)); \
                                    } \
                                    \
                                    __macro.closeContext(')'); \
                                    \
                                    _res_ = call(__macro); \
                                    m_expansionStack.pop_back();


namespace preprocessor
{
    cMacroInvoker::cInvoker::cInvoker()
    : m_state(cInvokerState::RECEIVING_TOKENS)
    , m_macroCall()
    {
    }
    cMacroInvoker::cInvoker::cInvoker(const cToken& token)
    : m_state(cInvokerState::RECEIVING_TOKENS)
    , m_macroCall(token)
    {
    }
    cMacroInvoker::cInvoker::cInvoker(const cToken& token, const cInvokerState& state)
    : m_state(state)
    , m_macroCall(token)
    {
    }
    void cMacroInvoker::cInvoker::setState(const cInvokerState& state)
    {
        m_state = state;
    }
    cMacroInvoker::cInvoker::cInvokerState cMacroInvoker::cInvoker::getState() const
    {
        return m_state;
    }
    cMacroCall& cMacroInvoker::cInvoker::getMacro()
    {
        return m_macroCall;
    }
    bool cMacroInvoker::cInvoker::operator==(const cToken& name) const
    {
        return m_macroCall.m_name == name;
    }

    cMacroInvoker::cMacroInvoker(cPreprocessor& handler)
    : m_handler(handler)
    {
        m_expansionStack.emplace_back();
    }
    std::vector<cToken> cMacroInvoker::_expand(const cToken& token)
    {
        std::vector<cToken> res = {token};

        if(m_handler.hasMacro(token))
        {
            const IMacro& macro = m_handler.getMacro(token);
            std::vector<cToken> expandedCode;

            if(macro.getType() == cMacroType::OBJECT_LIKE)
            {
                expandedCode = macro.expand();

                bool notAlreadyScanned = std::find(m_expansionStack.begin(),m_expansionStack.end(),token) == m_expansionStack.end();

                ASSERT(notAlreadyScanned, "Attempting to expand recursive macro!");

                m_expansionStack.emplace_back(token);

                if(notAlreadyScanned)
                {
                    //check every token in case of subsequent expansion
                    for(size_t index=0;index<expandedCode.size();)
                    {
                        cToken _code = expandedCode[index];

                        if(_code != token)
                        {
                            expandedCode.erase(expandedCode.begin()+index);

                            std::vector<cToken> expandedId = expand(_code);

                            expandedCode.insert(expandedCode.begin()+index,expandedId.begin(),expandedId.end());

                            if(expandedId.size() == 1 && expandedId[0] == _code)
                            {
                                index++;
                            }
                        }
                        else
                        {
                            index++;
                        }
                    }
                }
                m_expansionStack.pop_back();
            }
            else if(token.m_type == tokenType::IDENT_CALL)
            {
                m_expansionStack.emplace_back(token, cInvoker::cInvokerState::PARSING_MACRO_PARAMS);
            }
            else
            {
                expandedCode = std::vector<cToken>(1,token);
            }

            res = expandedCode;
        }

        return res;
    }

    std::vector<cToken> cMacroInvoker::expand(const std::vector<cToken>& tokens)
    {
        std::vector<cToken> res;

        std::vector<cToken>::const_iterator itToken = tokens.begin();
        for(;itToken!=tokens.end();itToken++)
        {
            std::vector<cToken> _res = expand(*itToken);
            res.insert(res.end(),_res.begin(),_res.end());
        }

        return res;
    }

    std::vector<cToken> cMacroInvoker::expand(const cToken& token)
    {
        cInvoker& currCall = m_expansionStack.back();
        std::vector<cToken> res;

        if(token.m_name == "YY_INPUT")
        {
            int a = 0;
            a++;
        }

        if(currCall.getState() == cInvoker::cInvokerState::RECEIVING_TOKENS)
        {
            res = _expand(token);
        }
        else if(currCall.getState() == cInvoker::cInvokerState::PARSING_MACRO_PARAMS)
        {
            if(currCall.getMacro().scanArgs(token))
            {
                CALL_PARSED_MACRO(res);
            }
        }

        return res;
    }

    std::vector<cToken> cMacroInvoker::call(const cMacroCall& macroCall)
    {
        ASSERT(m_handler.hasMacro(macroCall.m_name), "Invoking unexistent macro!");

        const IMacro& macro = m_handler.getMacro(macroCall.m_name);

        std::vector<cToken> expandedCode = macro.expand(macroCall.getArgs());

        //check every token in case of subsequent expansion
        for(size_t index=0;index<expandedCode.size();)
        {
            cToken _code = expandedCode[index];
            bool recursive = std::find(m_expansionStack.begin(),m_expansionStack.end(),_code) != m_expansionStack.end();

            ASSERT(!recursive, "Attempting to expand a recursive macro!");

            if(!recursive)
            {
                cInvoker& currCall = m_expansionStack.back();

                if(currCall.getState() == cInvoker::cInvokerState::RECEIVING_TOKENS)
                {
                    expandedCode.erase(expandedCode.begin()+index);
                    std::vector<cToken> expandedId = _expand(_code);
                    expandedCode.insert(expandedCode.begin()+index,expandedId.begin(),expandedId.end());
                    index += expandedId.size();
                }
                else if(currCall.getState() == cInvoker::cInvokerState::PARSING_MACRO_PARAMS)
                {
                    expandedCode.erase(expandedCode.begin()+index);
                    cMacroCall& macro = currCall.getMacro();

                    if(macro.scanArgs(_code))
                    {
                        //expanded function-like macro
                        std::vector<cToken> expandedMacro;
                        CALL_PARSED_MACRO(expandedMacro);
                        expandedCode.insert(expandedCode.begin()+index,expandedMacro.begin(),expandedMacro.end());
                        index += expandedMacro.size();
                    }
                }
            }
            else
            {
                index++;
            }
        }

        return expandedCode;
    }
}

#include "cMacroCall.h"

namespace preprocessor
{
    extern std::vector<cToken> collapseTokens(const std::vector<arg_t>& tokens);

    cMacroCall::cMacroCall()
    : m_receiving(false)
    {
    }
    cMacroCall::cMacroCall(const cToken& name)
    : m_name(name)
    , m_receiving(false)
    {
    }
    void cMacroCall::pushArg(const arg_t& arg)
    {
        cCallContext& _currContext = m_contextStack.back();

        if(!_currContext.m_currArg.empty())
        {
            _currContext.m_args.push_back(_currContext.m_currArg);
        }

        _currContext.m_currArg = arg;

        return;
    }
    void cMacroCall::reset()
    {
        m_name = cToken();
        m_receiving = false;
        m_contextStack.clear();
        m_args.clear();

        return;
    }
    void cMacroCall::receiving(bool rec)
    {
        if(m_receiving != rec)
        {
            m_receiving = rec;
        }

        return;
    }
    bool cMacroCall::isReceiving() const
    {
        return m_receiving;
    }
    bool cMacroCall::scanArgs(std::vector<cToken>::iterator itInit, std::vector<cToken>::iterator itEnd)
    {
        bool res = false;
        std::vector<cToken>::iterator itCode = itInit;

        for(;itCode!=itEnd;itCode++)
        {
            if(scanArgs(*itCode))
            {
                res = true;
                break;
            }
        }

        return res;
    }
    bool cMacroCall::scanArgs(const cToken& token)
    {
        bool res = false;
        const std::string& tokenName = token.m_name;
        std::string::const_iterator itName = tokenName.begin();

        if(!m_contextStack.empty() && token.m_type == tokenType::LITERAL)
        {
            cCallContext& _currContext = m_contextStack.back();

            if(!_currContext.m_atom.empty())
            {
                _currContext.m_currArg.push_back(_currContext.m_atom);
                _currContext.m_atom.clear();
            }

            _currContext.m_atom.m_name = token.m_name;
            _currContext.m_atom.m_type = tokenType::LITERAL;

            return false;
        }

        for(;itName!=tokenName.end() && !res;itName++)
        {
            const char& val = *itName;

            if(val == '(')
            {
                if(!m_contextStack.empty())
                {
                    cCallContext& _currContext = m_contextStack.back();
                    if(!_currContext.m_atom.empty())
                    {
                        _currContext.m_currArg.push_back(_currContext.m_atom);
                        _currContext.m_atom.clear();
                    }
                    _currContext.m_currArg.push_back(cToken(std::string(1,val),tokenType::SYMBOL));
                }
                else
                {
                    m_args.clear();
                }

                openContext(')');
            }
            else if(val == '<')
            {
                ASSERT(!m_contextStack.empty(), "Received delimiter in empty context stack!");

                cCallContext& _currContext = m_contextStack.back();

                if(!_currContext.m_atom.empty())
                {
                    _currContext.m_currArg.push_back(_currContext.m_atom);
                    _currContext.m_atom.clear();
                }

                _currContext.m_currArg.push_back(cToken(std::string(1,val),tokenType::SYMBOL));

                openContext('>');
            }
            else if(val == '>')
            {
                ASSERT(!m_contextStack.empty(), "Closing brace on 0-based context!");

                cCallContext& _currContext = m_contextStack.back();

                if(!_currContext.m_atom.empty())
                {
                    _currContext.m_currArg.push_back(_currContext.m_atom);
                    _currContext.m_atom.clear();
                }

                ASSERT(!closeContext(val,_currContext), "Unconsistent state while closing > brace!");
            }
            else if(val == ')')
            {
                ASSERT(!m_contextStack.empty(), "Closing brace on 0-based context!");

                cCallContext& _currContext = m_contextStack.back();

                if(!_currContext.m_atom.empty())
                {
                    _currContext.m_currArg.push_back(_currContext.m_atom);
                    _currContext.m_atom.clear();
                }

                res = closeContext(val,_currContext);
            }
            else if(val == ',')
            {
                cCallContext& _currContext = m_contextStack.back();
                _currContext.m_atom.m_type = (_currContext.m_atom.m_type == tokenType::NONE) ? tokenType::SYMBOL : _currContext.m_atom.m_type;
                _currContext.m_currArg.push_back(_currContext.m_atom);
                pushArg(_currContext.m_currArg);
                _currContext.m_currArg.clear();
                _currContext.m_atom.clear();
                //fake symbol for consistency
                _currContext.m_atom = cToken(std::string(""), tokenType::SYMBOL);
            }
            else if(val == ' ')
            {
                if(!m_contextStack.empty())
                {
                    cCallContext& _currContext = m_contextStack.back();

                    if(!_currContext.m_atom.empty())
                    {
                        _currContext.m_currArg.push_back(_currContext.m_atom);
                        _currContext.m_atom.clear();

                        _currContext.m_currArg.push_back(cToken(std::string(1,val),tokenType::SYMBOL));
                    }
                }
            }
            else
            {
                if(!m_contextStack.empty())
                {
                    cCallContext& _currContext = m_contextStack.back();

                    if(_currContext.m_atom.m_type != token.m_type && !_currContext.m_atom.empty())
                    {
                        _currContext.m_currArg.push_back(_currContext.m_atom);
                        _currContext.m_atom.clear();
                    }

                    _currContext.m_atom.m_name += val;
                    _currContext.m_atom.m_type = token.m_type;
                }
            }
        }

        return res;
    }
    void cMacroCall::openContext(const char& delim)
    {
        m_contextStack.emplace_back(delim);
    }
    void cMacroCall::closeContext(const char& delim)
    {
        ASSERT(!m_contextStack.empty(), "Closing empty stack!");

        cCallContext& currContext = m_contextStack.back();

        closeContext(delim, currContext);
    }
    bool cMacroCall::closeContext(const char& delim, cCallContext& _context)
    {
        ASSERT(!m_contextStack.empty(), "Closing empty stack!");

        if(m_contextStack.size() == 1)
        {
            if(_context.delimiter == delim)
            {
                if(!_context.m_currArg.empty())
                {
                    _context.m_args.push_back(_context.m_currArg);
                    _context.m_currArg.clear();
                }

                m_args = _context.m_args;
                m_contextStack.pop_back();
            }
            else if(delim == '>')
            {
                arg_t& _currArg = m_contextStack.back().m_currArg;
                _currArg.push_back(cToken(std::string(1,'>'),tokenType::SYMBOL));
            }
            else
            {
                ASSERT(false, "Unbalanced braces!");
            }
        }
        else
        {
            if(_context.delimiter == delim)
            {
                if(!_context.m_currArg.empty())
                {
                    _context.m_args.push_back(_context.m_currArg);
                    _context.m_currArg.clear();
                }

                std::vector<cToken> collapsedArgs = collapseTokens(_context.m_args);
                collapsedArgs.push_back(cToken(std::string(1,delim),tokenType::SYMBOL));
                m_contextStack.pop_back();
                cCallContext& currContext = m_contextStack.back();
                arg_t& _currArg = currContext.m_currArg;
                _currArg.insert(_currArg.end(),collapsedArgs.begin(),collapsedArgs.end());
            }
            else if(delim == '>')
            {
                arg_t& _currArg = m_contextStack.back().m_currArg;
                _currArg.push_back(cToken(std::string(1,'>'),tokenType::SYMBOL));
            }
            else
            {
                if(!_context.m_currArg.empty())
                {
                    _context.m_args.push_back(_context.m_currArg);
                    _context.m_currArg.clear();
                }

                std::vector<arg_t> _args = _context.m_args;
                ASSERT(!_args.empty(), "Current context should have at least one argument!");
                m_contextStack.pop_back();
                cCallContext& currContext = m_contextStack.back();
                std::vector<arg_t>& _currArgs = currContext.m_args;
                arg_t& _currArg = currContext.m_currArg;
                _currArg.insert(_currArg.end(),_args[0].begin(),_args[0].end());

                if(!_currArg.empty())
                {
                    _currArgs.push_back(_currArg);
                    _currArg.clear();
                }

                _currArgs.insert(_currArgs.end(),_args.begin()+1,_args.end());
                closeContext(delim,currContext);
            }
        }

        return m_contextStack.empty();
    }
    const std::vector<arg_t>& cMacroCall::getArgs() const
    {
        return m_args;
    }
    std::vector<arg_t>::iterator cMacroCall::begin()
    {
        return m_args.begin();
    }
    std::vector<arg_t>::const_iterator cMacroCall::begin() const
    {
        return m_args.cbegin();
    }
    std::vector<arg_t>::iterator cMacroCall::end()
    {
        return m_args.end();
    }
    std::vector<arg_t>::const_iterator cMacroCall::end() const
    {
        return m_args.cend();
    }
}

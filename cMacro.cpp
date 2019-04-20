#include "cMacro.h"
#include <sstream>
#include <map>

namespace preprocessor
{
    std::vector<cToken> collapseTokens(const std::vector<arg_t>& tokens)
    {
        std::vector<cToken> res;

        std::vector<arg_t>::const_iterator itToken=tokens.begin();
        for(;itToken!=tokens.end();)
        {
            const std::vector<cToken>& _assocTokens = *itToken;
            res.insert(res.end(),_assocTokens.begin(),_assocTokens.end());

            itToken++;

            if(itToken != tokens.end())
            {
                res.push_back(cToken(",",tokenType::SYMBOL));
            }
        }

        return res;
    }

    cBaseFileMacro::cBaseFileMacro(const std::string& filename)
    : m_baseFile(filename)
    {
    }
    std::vector<cToken> cBaseFileMacro::expand() const
    {
        return std::vector<cToken>(1,cToken(m_baseFile,tokenType::SYMBOL));
    }
    std::vector<cToken> cBaseFileMacro::expand(const std::vector<arg_t>& args) const
    {
        return std::vector<cToken>(1,cToken(m_baseFile,tokenType::SYMBOL));
    }
    cMacroType cBaseFileMacro::getType() const
    {
        return cMacroType::OBJECT_LIKE;
    }

    cIncludeLevelMacro::cIncludeLevelMacro()
    : m_currLevel(0)
    {
    }
    std::vector<cToken> cIncludeLevelMacro::expand() const
    {
        std::ostringstream formatter;
        formatter << m_currLevel;
        return std::vector<cToken>(1,cToken(formatter.str(),tokenType::NUMBER));
    }
    std::vector<cToken> cIncludeLevelMacro::expand(const std::vector<arg_t>& args) const
    {
        std::ostringstream formatter;
        formatter << m_currLevel;
        return std::vector<cToken>(1,cToken(formatter.str(),tokenType::NUMBER));
    }
    cMacroType cIncludeLevelMacro::getType() const
    {
        return cMacroType::OBJECT_LIKE;
    }
    void cIncludeLevelMacro::increment()
    {
        m_currLevel++;
    }
    void cIncludeLevelMacro::decrement()
    {
        m_currLevel--;
    }

    std::vector<cToken> cConcatMacro::expand(const std::vector<arg_t>& args) const
    {
        ASSERT(args.size() > 1, "You have to provide at least two arguments in concatenation macro!");

        std::string tokenStr;

        std::vector<arg_t>::const_iterator itArg = args.begin();
        for(;itArg!=args.end();itArg++)
        {
            const std::vector<cToken>& _assocTokens = *itArg;

            std::vector<cToken>::const_iterator itToken = _assocTokens.begin();
            for(;itToken!=_assocTokens.end();itToken++)
            {
                tokenStr += (*itToken).m_name;
            }
        }

        cToken concatToken = cToken(tokenStr, tokenType::IDENT);

        return std::vector<cToken>(1,concatToken);
    }

    cMacroType cConcatMacro::getType() const
    {
        return cMacroType::FUNCTION_LIKE;
    }

    std::vector<cToken> cConcatMacro::expand() const
    {
        return std::vector<cToken>(1,cToken("__Concat__",tokenType::IDENT_CALL));
    }

    std::vector<cToken> cCollapseVariadic::expand() const
    {
        return std::vector<cToken>(1,cToken("__CollapseVariadic__",tokenType::IDENT_CALL));
    }
    std::vector<cToken> cCollapseVariadic::expand(const std::vector<arg_t>& args) const
    {
        std::vector<cToken> res = collapseTokens(args);

        if(!res.empty())
        {
            res.insert(res.begin(),cToken(",",tokenType::SYMBOL));
        }

        return res;
    }
    cMacroType cCollapseVariadic::getType() const
    {
        return cMacroType::FUNCTION_LIKE;
    }

    std::vector<cToken> cStringized::expand() const
    {
        return std::vector<cToken>(1,cToken("__Stringized__",tokenType::IDENT_CALL));
    }
    std::vector<cToken> cStringized::expand(const std::vector<arg_t>& args) const
    {
        ASSERT(args.size() == 1, "You have to provide one argument in stringized macro!");

        std::vector<cToken> res = args[0];
        std::vector<cToken>::iterator itToken = res.begin();
        for(;itToken!=res.end();itToken++)
        {
            std::string& _name = (*itToken).m_name;
            std::string::iterator itChar = _name.begin();
            for(;itChar!=_name.end();)
            {
                if(*itChar == '\"')
                {
                    itChar = _name.insert(itChar,'\\');
                    itChar++;
                    itChar++;
                }
                else
                {
                    itChar++;
                }
            }
        }

        res.insert(res.begin(), cToken(std::string("\""),tokenType::SYMBOL));
        res.insert(res.end(), cToken(std::string("\""),tokenType::SYMBOL));

        return res;
    }
    cMacroType cStringized::getType() const
    {
        return cMacroType::FUNCTION_LIKE;
    }

    cMacro::cVar::cVar()
    : m_type(cVarType::SINGLE)
    , m_argPos(0)
    , m_codePos(0)
    {
    }

    cMacro::cVar::cVar(const std::string& name, size_t argPos, size_t codePos)
    {
        m_argPos = argPos;
        m_codePos = codePos;
        m_type = (name.find("...") != std::string::npos) ? cVarType::VARIADIC : cVarType::SINGLE;
    }

    cMacro::cMacro()
    : m_type(cMacroType::OBJECT_LIKE)
    , m_numArgs(0)
    , m_variadic(false)
    {
    }
    cMacro::cMacro(const cToken& name, const std::vector<cToken>& vars, const std::vector<cToken>& code, cMacroType type)
    : m_name(name)
    , m_assocCode(code)
    , m_type(type)
    , m_numArgs(vars.size())
    {
        std::vector<cToken>::const_iterator itCode = m_assocCode.begin();
        for(size_t counterCode=0;itCode!=m_assocCode.end();itCode++,counterCode++)
        {
            const cToken& atomCode = *itCode;

            std::vector<cToken>::const_iterator itVar = vars.begin();
            for(size_t counterArg=0;itVar!=vars.end();itVar++,counterArg++)
            {
                const cToken& _name = *itVar;
                ASSERT(_name.m_type==tokenType::IDENT, "Variable of wrong type!");
                cVar _var(_name.m_name, counterArg, counterCode);

                m_variadic = (_name.m_name.find("...") != std::string::npos) ? true : m_variadic;

                if(_var.m_type == cVar::cVarType::VARIADIC)
                {
                    size_t varNamePos = _name.m_name.find("...");
                    ASSERT(varNamePos != std::string::npos, "Variadic variable malformed!");
                    std::string varName = _name.m_name.substr(0,varNamePos);

                    if((!varName.empty() && atomCode.m_name == varName) || (varName.empty() && atomCode.m_name == "__VA_ARGS__"))
                    {
                        m_occurrences.push_back(_var);
                    }
                }
                else if(atomCode.m_name == _name.m_name)
                {
                    m_occurrences.push_back(_var);
                }
            }
        }
    }
    std::vector<cToken> cMacro::expand() const
    {
        return (m_type == cMacroType::OBJECT_LIKE) ? m_assocCode : std::vector<cToken>(1,m_name);
    }
    std::vector<cToken> cMacro::expand(const std::vector<arg_t>& args) const
    {
        ASSERT((args.size() == m_numArgs || (args.size() >= m_numArgs-1 && m_variadic)), "Mismatch on number of arguments to macro!");

        std::vector<cToken> expandedCode = m_assocCode;

        size_t remainingVars = args.size();

        //exapnd arguments
        std::vector<cVar>::const_reverse_iterator itOcc = m_occurrences.rbegin();
        for(;itOcc!=m_occurrences.rend();itOcc++)
        {
            const cVar& _var = *itOcc;
            std::vector<arg_t> inputTokens = (_var.m_type==cVar::cVarType::SINGLE) ? std::vector<arg_t>(1,args[_var.m_argPos])
                                                                                    : std::vector<arg_t>(args.begin()+_var.m_argPos,args.end());
            std::vector<cToken> mappedToken = collapseTokens(inputTokens);

            expandedCode.erase(expandedCode.begin()+_var.m_codePos);
            expandedCode.insert(expandedCode.begin()+_var.m_codePos,mappedToken.begin(),mappedToken.end());

            remainingVars -= inputTokens.size();
        }

        return expandedCode;
    }

    cMacroType cMacro::getType() const
    {
        return m_type;
    }

}

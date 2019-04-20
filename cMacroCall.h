#pragma once

#include "IPreprocessor.h"

namespace preprocessor
{
    struct cMacroCall
    {
        struct cCallContext
        {
            char               delimiter;
            std::vector<arg_t>  m_args;
            arg_t               m_currArg;
            cToken              m_atom;

            cCallContext(char _delimiter) : delimiter(_delimiter){};
        };

        cToken                      m_name;
        bool                       m_receiving;
        std::vector<cCallContext>   m_contextStack;
        std::vector<arg_t>          m_args;

        cMacroCall();
        cMacroCall(const cToken& name);
        void pushArg(const arg_t& arg);
        void reset();
        void receiving(bool rec);
        bool isReceiving() const;
        bool scanArgs(std::vector<cToken>::iterator itInit, std::vector<cToken>::iterator itEnd);
        bool scanArgs(const cToken& token);
        void openContext(const char& delim);
        void closeContext(const char& delim);
        const std::vector<arg_t>& getArgs() const;
        std::vector<arg_t>::iterator begin();
        std::vector<arg_t>::const_iterator begin() const;
        std::vector<arg_t>::iterator end();
        std::vector<arg_t>::const_iterator end() const;

        private:
            bool closeContext(const char& delim, cCallContext& _context);
    };
}

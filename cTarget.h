#pragma once

#include "IPreprocessor.h"
#include <sstream>

using namespace std;

namespace preprocessor
{
    static const char gccVersion[3] = {'4','8','0'};
    static int counter = 0;


    inline bool isBuiltIn(const cToken& name)
    {
        return name.m_name == "__LINE__" || name.m_name == "__FILE__" || name.m_name == "__cplusplus" || name.m_name == "__ELF__" ||
                name.m_name == "__COUNTER__" || name.m_name == "__GNUC__" || name.m_name == "__GNUC_MINOR__" || name.m_name == "__GNUC_PATCHLEVEL__" ||
                name.m_name == "__GNUG__" || name.m_name == "__VERSION__" || name.m_name == "__SIZE_TYPE__" || name.m_name == "__PTRDIFF_TYPE__" ||
                name.m_name ==  "__WCHAR_TYPE__" || name.m_name ==  "__WINT_TYPE__" || name.m_name ==  "__INTMAX_TYPE__" || name.m_name ==  "__UINTMAX_TYPE__" ||
                name.m_name ==  "__SIG_ATOMIC_TYPE__" || name.m_name ==  "__INT8_TYPE__" || name.m_name == "__INT16_TYPE__" || name.m_name == "__INT32_TYPE__" ||
                name.m_name == "__INT64_TYPE__" || name.m_name == "__UINT8_TYPE__" || name.m_name == "__UINT16_TYPE__" || name.m_name == "__UINT32_TYPE__" ||
                name.m_name ==  "__UINT64_TYPE__" || name.m_name ==  "__INT_LEAST8_TYPE__" || name.m_name == "__INT_LEAST16_TYPE__" || name.m_name == "__INT_LEAST32_TYPE__" ||
                name.m_name == "__INT_LEAST64_TYPE__" || name.m_name == "__UINT_LEAST8_TYPE__" || name.m_name == "__UINT_LEAST16_TYPE__"||
                name.m_name == "__UINT_LEAST32_TYPE__" || name.m_name == "__UINT_LEAST64_TYPE__" || name.m_name == "__INT_FAST8_TYPE__" ||
                name.m_name == "__INT_FAST16_TYPE__" || name.m_name == "__INT_FAST32_TYPE__" || name.m_name == "__INT_FAST64_TYPE__" ||
                name.m_name == "__UINT_FAST8_TYPE__" || name.m_name == "__UINT_FAST16_TYPE__" || name.m_name == "__UINT_FAST32_TYPE__" ||
                name.m_name == "__UINT_FAST64_TYPE__" || name.m_name == "__INTPTR_TYPE__" || name.m_name == "__UINTPTR_TYPE__" || name.m_name == "__CHAR_BIT__" ||
                name.m_name == "__FLT_MANT_DIG__" || name.m_name == "__DBL_MANT_DIG__" || name.m_name == "__LDBL_MANT_DIG__" || name.m_name == "__FLT_DIG__" ||
                name.m_name == "__DBL_DIG__" || name.m_name == "__LDBL_DIG__" || name.m_name == "__FLT_MAX_10_EXP__" || name.m_name == "__DBL_MAX_10_EXP__" ||
                name.m_name == "__LDBL_MAX_10_EXP__" || name.m_name == "__STDC__" || name.m_name == "_GNU_SOURCE" || name.m_name == "__ATOMIC_ACQ_REL" ||
                name.m_name == "__SHRT_MAX__" || name.m_name == "__INT_MAX__" || name.m_name == "__LONG_MAX__" || name.m_name == "__LONG_LONG_MAX__" ||
                name.m_name == "__unix__";
    }

    inline cToken expandBuiltinMacro(const char* str, cScanner& scanner, const tokenType& type)
    {
        std::string stdStr = std::string(str);
        cToken res = cToken(stdStr,type);

        if(stdStr == "__LINE__")
        {
            ostringstream formatter;
            formatter << scanner.getCurrLine();
            res = cToken(formatter.str(),tokenType::NUMBER);
        }
        else if(stdStr == "__FILE__")
        {
            res = cToken(std::string("\"") + scanner.getCurrFile() + std::string("\""),tokenType::SYMBOL);
        }
        else if(stdStr == "__COUNTER__")
        {
            ostringstream formatter;
            formatter << counter++;
            res = cToken(formatter.str(),tokenType::NUMBER);
        }
        else if(stdStr == "__GNUC__")
        {
            ostringstream formatter;
            formatter << gccVersion[0];
            res = cToken(formatter.str(),tokenType::NUMBER);
        }
        else if(stdStr == "__GNUC_MINOR__")
        {
            ostringstream formatter;
            formatter << gccVersion[1];
            res = cToken(formatter.str(),tokenType::NUMBER);
        }
        else if(stdStr == "__GNUC_PATCHLEVEL__")
        {
            ostringstream formatter;
            formatter << gccVersion[2];
            res = cToken(formatter.str(),tokenType::NUMBER);
        }
        else if(stdStr == "__GNUG__")
        {
            ostringstream formatter;
            formatter << 1;
            res = cToken(formatter.str(),tokenType::NUMBER);
        }
        else if(stdStr == "__VERSION__")
        {
            ostringstream formatter;
            formatter << gccVersion[0] << "." << gccVersion[1] << "." << gccVersion[2];
            res = cToken(formatter.str(),tokenType::NUMBER);
        }
        else if(stdStr == "__SIZE_TYPE__")
        {
            res = cToken("unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__PTRDIFF_TYPE__")
        {
            res = cToken("int",tokenType::SYMBOL);
        }
        else if(stdStr == "__WCHAR_TYPE__")
        {
            res = cToken("long int",tokenType::SYMBOL);
        }
        else if(stdStr == "__WINT_TYPE__")
        {
            res = cToken("unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INTMAX_TYPE__")
        {
            res = cToken("long long int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINTMAX_TYPE__")
        {
            res = cToken("long long unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__SIG_ATOMIC_TYPE__")
        {
            res = cToken("int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT8_TYPE__")
        {
            res = cToken("signed char",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT16_TYPE__")
        {
            res = cToken("short int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT32_TYPE__")
        {
            res = cToken("int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT64_TYPE__")
        {
            res = cToken("long long int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT8_TYPE__")
        {
            res = cToken("unsigned char",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT16_TYPE__")
        {
            res = cToken("short unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT32_TYPE__")
        {
            res = cToken("unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT64_TYPE__")
        {
            res = cToken("long long unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT_LEAST8_TYPE__")
        {
            res = cToken("signed char",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT_LEAST16_TYPE__")
        {
            res = cToken("short int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT_LEAST32_TYPE__")
        {
            res = cToken("int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT_LEAST64_TYPE__")
        {
            res = cToken("long long int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT_LEAST8_TYPE__")
        {
            res = cToken("unsigned char",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT_LEAST16_TYPE__")
        {
            res = cToken("short unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT_LEAST32_TYPE__")
        {
            res = cToken("unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT_LEAST64_TYPE__")
        {
            res = cToken("long long unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT_FAST8_TYPE__")
        {
            res = cToken("signed char",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT_FAST16_TYPE__")
        {
            res = cToken("int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT_FAST32_TYPE__")
        {
            res = cToken("int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INT_FAST64_TYPE__")
        {
            res = cToken("long long int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT_FAST8_TYPE__")
        {
            res = cToken("unsigned char",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT_FAST16_TYPE__")
        {
            res = cToken("unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT_FAST32_TYPE__")
        {
            res = cToken("unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINT_FAST64_TYPE__")
        {
            res = cToken("long long unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__INTPTR_TYPE__")
        {
            res = cToken("int",tokenType::SYMBOL);
        }
        else if(stdStr == "__UINTPTR_TYPE__")
        {
            res = cToken("unsigned int",tokenType::SYMBOL);
        }
        else if(stdStr == "__CHAR_BIT__")
        {
            res = cToken("8", tokenType::NUMBER);
        }
        else if(stdStr == "__FLT_MANT_DIG__")
        {
            res = cToken("24", tokenType::NUMBER);
        }
        else if(stdStr == "__DBL_MANT_DIG__")
        {
            res = cToken("53", tokenType::NUMBER);
        }
        else if(stdStr == "__LDBL_MANT_DIG__")
        {
            res = cToken("64", tokenType::NUMBER);
        }
        else if(stdStr == "__FLT_DIG__")
        {
            res = cToken("6", tokenType::NUMBER);
        }
        else if(stdStr == "__DBL_DIG__")
        {
            res = cToken("15", tokenType::NUMBER);
        }
        else if(stdStr == "__LDBL_DIG__")
        {
            res = cToken("18", tokenType::NUMBER);
        }
        else if(stdStr == "__FLT_MAX_10_EXP__")
        {
            res = cToken("38", tokenType::NUMBER);
        }
        else if(stdStr == "__DBL_MAX_10_EXP__")
        {
            res = cToken("308", tokenType::NUMBER);
        }
        else if(stdStr == "__LDBL_MAX_10_EXP__")
        {
            res = cToken("4932", tokenType::NUMBER);
        }
        else if(stdStr == "__ATOMIC_ACQ_REL")
        {
            res = cToken("4", tokenType::NUMBER);
        }
        else if(stdStr == "__SHRT_MAX__")
        {
            res = cToken("32767", tokenType::NUMBER);
        }
        else if(stdStr == "__INT_MAX__")
        {
            res = cToken("2147483647", tokenType::NUMBER);
        }
        else if(stdStr == "__LONG_MAX__")
        {
            res = cToken("2147483647L", tokenType::NUMBER);
        }
        else if(stdStr == "__LONG_LONG_MAX__")
        {
            res = cToken("9223372036854775807LL", tokenType::NUMBER);
        }
        else if(stdStr == "__cplusplus")
        {
            ostringstream formatter;
            formatter << cplusplus;
            res = cToken(formatter.str(),tokenType::NUMBER);
        }
        else if(stdStr == "__STDC__")
        {
            res = cToken("1", tokenType::SYMBOL);
        }

        return res;
    }



}

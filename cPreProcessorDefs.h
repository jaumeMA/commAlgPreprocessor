#pragma once

#include <climits>
#include <cfloat>
#include <cstdio>
#include <cstring>
#include <cstddef>
#include <assert.h>

extern FILE* errFile;

#define ASSERT(cond,msg)    {\
                                bool _cond = (cond); \
                                if(!_cond) { \
                                                fwrite("err: ", 5, 1, errFile); \
                                                fwrite(msg, std::strlen(msg), 1, errFile); \
                                                fwrite("\n", 1, 1, errFile); \
                                            }\
                            }
#define LOG(msg)    {\
                        fwrite("log: ", 5, 1, errFile); \
                        fwrite(msg, std::strlen(msg), 1, errFile); \
                        fwrite("\n", 1, 1, errFile); \
                    }

struct dataStr
{
    char*   m_data;
    int     m_leng;
};

typedef unsigned char		u8;
typedef signed char		    s8;
typedef char			    c8;

typedef unsigned short		u16;
typedef signed short		s16;

typedef unsigned int		u32;
typedef signed int		    s32;

typedef float				f32;
typedef double				    f64;

typedef size_t                  size;

typedef unsigned long           l64;

template<typename def, typename inner = typename def::type>
class safe_enum : public def
{
        typedef inner type;
        inner val;

    public:

        safe_enum() {}
        safe_enum(type v) : val(v) {}
        type value() const { return val; }
        const char* name() { return def::name((typename def::type)val); }

        friend bool operator == (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val == rhs.val; }
        friend bool operator != (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val != rhs.val; }
        friend bool operator <  (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val <  rhs.val; }
        friend bool operator <= (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val <= rhs.val; }
        friend bool operator >  (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val >  rhs.val; }
        friend bool operator >= (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val >= rhs.val; }
};

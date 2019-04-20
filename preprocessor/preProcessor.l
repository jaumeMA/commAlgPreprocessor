/********************************************************
 * preProcessor.l
 ********************************************************/
%option noyywrap
%option prefix="preproc_"
%option c++
%option yyclass="cScanner"
%option stack

%{
#include "cPreProcessorDefs.h"
#include <vector>
#include <string>

typedef std::vector<std::string> stringArray;
#include "cScanner.h"

typedef preprocessor::cParser::token token;

static int numComments = 0;
%}

IDENT_WITH_SHARP_SPACE [a-zA-Z_][a-zA-Z0-9_#]*
IDENT [a-zA-Z_][a-zA-Z0-9_]*
FILENAME [a-zA-Z0-9_./+\-]+
INTEGER [0-9]+|[0-9]+l|[0-9]+L|"0x"[0-9]+
FLOAT [0-9]+\.[0-9]*|[0-9]+\.[0-9]*f|[0-9]+\.[0-9]*F
NUMBER {INTEGER}|{FLOAT}
IDENT_INTEGER {IDENT}|{INTEGER}
IDENT_FLOAT {IDENT}|{FLOAT}
IDENT_NUMBER {IDENT}|{NUMBER}
IDENT_WITH_SHARP_SPACE_NUMBER {IDENT_WITH_SHARP_SPACE}|{NUMBER}
OPERATOR [+\-*]+
TOKEN_PASTING_L {IDENT_NUMBER}|{OPERATOR}
TOKEN_PASTING_R {IDENT_WITH_SHARP_SPACE_NUMBER}|{OPERATOR}
SPACE [ \t]
SPACES {SPACE}+
OPT_SPACES {SPACE}*
MACRO_SIGN {OPT_SPACES}"#"{OPT_SPACES}
CONCAT {OPT_SPACES}"##"{OPT_SPACES}
CHAR "'"
ESCAPE "\\"
LITERAL "\""
COMMENT {OPT_SPACES}"/*"
COMMENT_LINE {OPT_SPACES}"//"
BINARY_OPERATION "&&"|"||"|"=="|"!="|">"|">="|"<"|"<="|"+"|"-"|"*"|"/"|"<<"|">>"|"&"|"|"
IDENTCALL {IDENT}{OPT_SPACES}"("
END_LINE "\n"|"\r\n"
NO_ENDLINE [^'\n|\r\n']

%x comment comment_line include include_filename ident_macro ident_compute literal ident_error
%s macro define_macro define_args define_definition compute error pragma line code
%%

<macro>
{
    "__compute__"{SPACES}                      { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(compute); return token::COMPUTE; }
    "line"{SPACES}                             { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(line); }
    "pragma"{SPACES}                           { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(pragma); return token::PRAGMA; }
    "error"{OPT_SPACES}                        { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(error); return token::ERROR; }
    "warning"{SPACES}                          { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(error); return token::WARNING; }
    "define"{SPACES}                           { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(define_macro); return token::DEFINE; }
    "undef"{SPACES}                            { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(code); return token::UNDEFINE; }
    "include"{OPT_SPACES}                      { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(include); return token::INCLUDE; }
    "include_next"{OPT_SPACES}                 { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(include); return token::INCLUDE_NEXT; }
    "if"{SPACES}                               { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(compute); return token::IF; }
    "ifdef"{SPACES}                            { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(compute); return token::IFDEF; }
    "ifndef"{SPACES}                           { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(compute); return token::IFNDEF; }
    "elif"{SPACES}                             { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(compute); return token::ELIF; }
    "else"{OPT_SPACES}                         { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(code); return token::ELSE; }
    "endif"{OPT_SPACES}                        { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; BEGIN(code); return token::END; }
    {END_LINE}                                 { BEGIN(code); incrCurrLine(); return token::END_LINE; }
    .                                          { }
}

<line>
{
    {INTEGER}{SPACES}               {
                                        std::string tmp = std::string(yytext,yyleng);
                                        size_t separatorTokenPos = tmp.find(" ");
                                        std::string lineStr = tmp.substr(0,separatorTokenPos);

                                        yylval->tokensArr = new std::vector<preprocessor::cToken>();
                                        yylval->tokensArr->push_back(cToken(lineStr,tokenType::IDENT));

                                        BEGIN(code);

                                        return token::BUILTIN_LINE;
                                    }
    {INTEGER}{SPACES}{FILENAME}     {
                                        std::string tmp = std::string(yytext,yyleng);
                                        size_t separatorTokenPos[2] = {tmp.find_first_of(" "),tmp.find_last_of(" ")};
                                        std::string lineStr[2] = {tmp.substr(0,separatorTokenPos[0]),tmp.substr(separatorTokenPos[1])};

                                        yylval->tokensArr = new std::vector<preprocessor::cToken>();
                                        yylval->tokensArr->push_back(cToken(lineStr[0],tokenType::IDENT));
                                        yylval->tokensArr->push_back(cToken(lineStr[1],tokenType::IDENT));

                                        BEGIN(code);

                                        return token::BUILTIN_LINE;
                                    }
    {END_LINE}                      { BEGIN(code); incrCurrLine(); return token::END_LINE; }
}

<error>
{
    {IDENT}         { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::IDENT; }
    {NUMBER}        { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::NUMBER; }
    "\\"            { BEGIN(ident_error); }
    {END_LINE}      { BEGIN(code); incrCurrLine(); return token::END_LINE; }
    .               { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::SYMBOLS; }

    <ident_error>
    {
        {END_LINE}  { BEGIN(error); incrCurrLine(); }
        .           { };
    }
}

<pragma>
{
    {IDENT}         { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::IDENT; }
    {NUMBER}        { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::NUMBER; }
    {END_LINE}      { BEGIN(code); incrCurrLine(); return token::END_LINE; }
    .               { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::SYMBOLS; }
}

<include>
{
    {IDENT}                     { BEGIN(code); return token::IDENT; }
    "\""                        { BEGIN(include_filename); return token::INCLUDE_COMMA_DELIM; }
    "<"                         { BEGIN(include_filename); return token::INCLUDE_GL_DELIM; }

    <include_filename>
    {
        {FILENAME}                  { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::INCLUDE_FILENAME; }
        "\""                        { BEGIN(code); return token::INCLUDE_COMMA_DELIM; }
        ">"                         { BEGIN(code); return token::INCLUDE_GL_DELIM; }
    }
}

<compute>
{
    "defined"                          { yylval->unit_sym = yytext; return token::DEFINED; }
    {BINARY_OPERATION}                 { yylval->unit_sym = yytext; return token::BINARY_OP; }
    "?"                                { yylval->unit_sym = yytext; return token::TERNARY_LEFT_OP; }
    ":"                                { yylval->unit_sym = yytext; return token::TERNARY_RIGHT_OP; }
    "!"                                { yylval->unit_sym = yytext; return token::UNARY_OP; }
    "("                                { yylval->unit_sym = yytext; return token::TLPAREN; }
    ")"                                { yylval->unit_sym = yytext; return token::TRPAREN; }
    ","                                { yylval->unit_sym = yytext; return token::TCOMMA; }
    {IDENT}                            { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::IDENT; }
    {FLOAT}|{INTEGER}                  { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::NUMBER; };
    "\\"                               { BEGIN(ident_compute); }
    {SPACES}                           { }
    {END_LINE}                         { BEGIN(code); incrCurrLine(); return token::END_LINE; }

    <ident_compute>
    {
        {END_LINE}  { BEGIN(compute); incrCurrLine(); }
        .           { };
    }
}

<comment>
{
    "*/"                                { yy_pop_state(); numComments = 0; }
    {END_LINE}                          { incrCurrLine(); numComments++; }
    .                                   {  }
}

<comment_line>
{
    {END_LINE}"//"                       { incrCurrLine(); numComments++; }
    {END_LINE}                          { yy_pop_state(); incrCurrLine(); yylval->val= numComments; numComments = 0; return token::COMMENT; }
    .                                   { }
}


<literal>
{
    "\""[^\"]*"\""  { yy_pop_state(); yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::LITERAL; }
}

<define_macro>
{
    "("         { BEGIN(define_args); yylval->unit_sym = yytext; return token::TLPAREN; }
    {SPACES}    { BEGIN(define_definition); }
    {IDENT}     { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::IDENT; }
    {END_LINE}  { BEGIN(code); incrCurrLine(); return token::END_LINE; }

    <define_args>
    {
        ")"             { BEGIN(define_definition); yylval->unit_sym = yytext; return token::TRPAREN; }
        ","             { yylval->unit_sym = yytext; return token::TCOMMA; }
        {IDENT}         { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::IDENT; }
        "..."           { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::IDENT; }
        {IDENT}"..."    { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::IDENT; }
        .               { }
    }
}

<define_definition>
{
    {MACRO_SIGN}{IDENT}                         {
                                                    std::string tmp = std::string(yytext,yyleng);
                                                    //remove spaces
                                                    tmp.erase(std::remove_if(tmp.begin(),tmp.end(),[](const char& entry){return std::isspace(entry);}),tmp.end());
                                                    yylval->tokensArr = new std::vector<preprocessor::cToken>();
                                                    size_t separatorTokenPos = tmp.find("#");

                                                    //this one is for sure!
                                                    yylval->tokensArr->push_back(cToken(tmp.substr(separatorTokenPos+1),tokenType::IDENT));

                                                    return token::BUILTIN_STRINGIZED;
                                                }
    ",##__VA_ARGS__"                            {
                                                    yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng;
                                                    return token::BUILTIN_COLLAPSE_VARIADIC;
                                                }
    {TOKEN_PASTING_L}{CONCAT}{TOKEN_PASTING_R}  {
                                                    std::string tmp = std::string(yytext,yyleng);
                                                    //remove spaces
                                                    tmp.erase(std::remove_if(tmp.begin(),tmp.end(),[](const char& entry){return std::isspace(entry);}),tmp.end());
                                                    yylval->tokensArr = new std::vector<preprocessor::cToken>();

                                                    do
                                                    {
                                                        size_t separatorTokenPos1 = tmp.find("##");

                                                        if(separatorTokenPos1 != std::string::npos)
                                                        {
                                                            yylval->tokensArr->push_back(cToken(tmp.substr(0,separatorTokenPos1),tokenType::IDENT));
                                                            tmp = tmp.substr(separatorTokenPos1+2);
                                                        }
                                                        else
                                                        {
                                                            yylval->tokensArr->push_back(cToken(tmp,tokenType::IDENT));
                                                            tmp.clear();
                                                        }
                                                    }
                                                    while(!tmp.empty());

                                                    return token::BUILTIN_CONCAT;
                                                }
    "\\"{NO_ENDLINE}                            { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::SYMBOLS; }
    "\\"                                        { BEGIN(ident_macro); }
    {END_LINE}                                  { incrCurrLine(); BEGIN(code); return token::END_LINE; }

    <code>
    {
        {MACRO_SIGN}                            { BEGIN(macro); }
        {CHAR}.{CHAR}                           { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::SYMBOLS; }
        {LITERAL}                               { yyless(0); yy_push_state(literal); yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; }
        {IDENTCALL}                             {
                                                        yylval->sym.m_data = yytext;
                                                        int identSize = 0;
                                                        for(int count=0;count<yyleng;count++)
                                                        {
                                                            if(std::isspace(yytext[count]) || yytext[count] == '(')
                                                            {
                                                                identSize = count;
                                                                break;
                                                            }
                                                        }

                                                        yylval->sym.m_leng = identSize;
                                                        yyless(identSize);
                                                        return token::IDENT_CALL;
                                                }
        {IDENT}                                 { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::IDENT; }
        {FLOAT}|{INTEGER}                       { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::NUMBER; };
        .                                       { yylval->sym.m_data = yytext; yylval->sym.m_leng = yyleng; return token::SYMBOLS; }
    }

    <ident_macro>
    {
        {END_LINE}  { BEGIN(define_definition); incrCurrLine(); }
        .           { };
    }
}

{END_LINE}                          { incrCurrLine(); return token::END_LINE; }
{COMMENT}                           { yy_push_state(comment); }
{COMMENT_LINE}                      { yy_push_state(comment_line); }
.                                   {
                                        std::string msg = std::string("Receiving token ") + std::string(yytext,yyleng);
                                        LOG(msg.c_str())

                                        yyless(0);
                                        BEGIN(code);
                                    }
<<EOF>>                             {
                                        if(!empty())
                                        {
                                            const ProcessedFile& processor = m_filesToProcess.back();
                                            std::istream* str = processor.m_pStream;

                                            if(str)
                                            {
                                                char tmp[32];
                                                memset(tmp,0,sizeof(char)*32);
                                                sprintf(tmp,"Leaving with %d", (size_t)str->tellg());
                                                std::string msg = std::string(tmp,32);
                                                LOG(msg.c_str())
                                            }
                                        }
                                        if(finishedStream())
                                        {
                                            yyterminate();
                                        }
                                    }

%%

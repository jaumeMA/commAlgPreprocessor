/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */


/* Line 293 of lalr1.cc  */
#line 39 "./preprocessor/preProcessor.tab.cpp"


#include "preProcessor.tab.hpp"

/* User implementation prologue.  */


/* Line 299 of lalr1.cc  */
#line 48 "./preprocessor/preProcessor.tab.cpp"
/* Unqualified %code blocks.  */

/* Line 300 of lalr1.cc  */
#line 30 "./preprocessor/preProcessor.ypp"

#include <math.h>
#include <memory>
#include <cstring>
#include "cScanner.h"
#include "cTarget.h"

#define YYMAXDEPTH 200000

using namespace std;

static int yylex(preprocessor::cParser::semantic_type* yylval, preprocessor::cScanner& scanner, preprocessor::IPreprocessor* preproc);

template<typename T>
void releaseMem(T*& ptr);

int compute(int a, int b, const preprocessor::cToken& op);
int compute(int a, const preprocessor::cToken& op);



/* Line 300 of lalr1.cc  */
#line 75 "./preprocessor/preProcessor.tab.cpp"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                               \
 do                                                                    \
   if (N)                                                              \
     {                                                                 \
       (Current).begin = YYRHSLOC (Rhs, 1).begin;                      \
       (Current).end   = YYRHSLOC (Rhs, N).end;                        \
     }                                                                 \
   else                                                                \
     {                                                                 \
       (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;        \
     }                                                                 \
 while (false)
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 382 of lalr1.cc  */
#line 5 "./preprocessor/preProcessor.ypp"
namespace preprocessor {

/* Line 382 of lalr1.cc  */
#line 163 "./preprocessor/preProcessor.tab.cpp"

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  cParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  cParser::cParser (cScanner& scanner_yyarg, IPreprocessor* preproc_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      preproc (preproc_yyarg)
  {
  }

  cParser::~cParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  cParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  cParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  cParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  cParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  cParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  cParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  cParser::debug_level_type
  cParser::debug_level () const
  {
    return yydebug_;
  }

  void
  cParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  cParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  cParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  cParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, scanner, preproc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 690 of lalr1.cc  */
#line 80 "./preprocessor/preProcessor.ypp"
    {
    if(preproc)
    {
        preproc->endPreprocessing();
    }
}
    break;

  case 5:

/* Line 690 of lalr1.cc  */
#line 91 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = (yysemantic_stack_[(1) - (1)].sym);
}
    break;

  case 6:

/* Line 690 of lalr1.cc  */
#line 95 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = (yysemantic_stack_[(1) - (1)].sym);
}
    break;

  case 7:

/* Line 690 of lalr1.cc  */
#line 99 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = (yysemantic_stack_[(1) - (1)].sym);
}
    break;

  case 8:

/* Line 690 of lalr1.cc  */
#line 103 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = (yysemantic_stack_[(1) - (1)].sym);
}
    break;

  case 9:

/* Line 690 of lalr1.cc  */
#line 107 "./preprocessor/preProcessor.ypp"
    {
    scanner.setComputeValue((yysemantic_stack_[(1) - (1)].val));
    (yyval.sym) = dataStr();
}
    break;

  case 10:

/* Line 690 of lalr1.cc  */
#line 112 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = (yysemantic_stack_[(1) - (1)].sym);
}
    break;

  case 11:

/* Line 690 of lalr1.cc  */
#line 116 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = (yysemantic_stack_[(1) - (1)].sym);
}
    break;

  case 12:

/* Line 690 of lalr1.cc  */
#line 120 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = (yysemantic_stack_[(1) - (1)].sym);
}
    break;

  case 13:

/* Line 690 of lalr1.cc  */
#line 124 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = (yysemantic_stack_[(1) - (1)].sym);
}
    break;

  case 14:

/* Line 690 of lalr1.cc  */
#line 128 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = dataStr();

    if((yysemantic_stack_[(1) - (1)].val) > 5)
    {
        scanner.flushLocationInfo();
    }
    else
    {
        preproc->newLine((yysemantic_stack_[(1) - (1)].val));
    }
}
    break;

  case 15:

/* Line 690 of lalr1.cc  */
#line 141 "./preprocessor/preProcessor.ypp"
    {
    (yyval.sym) = dataStr();
    preproc->newLine(1);
}
    break;

  case 16:

/* Line 690 of lalr1.cc  */
#line 147 "./preprocessor/preProcessor.ypp"
    {
    preproc->newTokens(*(yysemantic_stack_[(2) - (1)].tokensArr));
    preproc->newLine((yysemantic_stack_[(2) - (2)].val));

    releaseMem((yysemantic_stack_[(2) - (1)].tokensArr));
}
    break;

  case 17:

/* Line 690 of lalr1.cc  */
#line 155 "./preprocessor/preProcessor.ypp"
    {
/*    if(preproc->hasMacro(*$2))
    {
        printf("EP, incloent fixter predefined\n");
        const preprocessor::IMacro& macro = preproc->getMacro(*$2);
        std::vector<preprocessor::cToken> expandedMacro = macro.expand();
        if(expandedMacro.size() == 1)
        {
            const preprocessor::cToken& _token = expandedMacro[0];
            preproc->newInclude(_token, _token.m_name[0]=='<' && _token.m_name[_token.m_name.size()-1]=='>', false);
        }
    }
*/
    releaseMem((yysemantic_stack_[(2) - (2)].token));
}
    break;

  case 18:

/* Line 690 of lalr1.cc  */
#line 171 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken _token = preprocessor::cToken(std::string((char *)(yysemantic_stack_[(4) - (3)].sym).m_data,(char *)(yysemantic_stack_[(4) - (3)].sym).m_data+(yysemantic_stack_[(4) - (3)].sym).m_leng),preprocessor::tokenType::IDENT);

    preproc->newInclude(_token, false, false);
}
    break;

  case 19:

/* Line 690 of lalr1.cc  */
#line 177 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken _token = preprocessor::cToken(std::string((char *)(yysemantic_stack_[(4) - (3)].sym).m_data,(char *)(yysemantic_stack_[(4) - (3)].sym).m_data+(yysemantic_stack_[(4) - (3)].sym).m_leng),preprocessor::tokenType::IDENT);

    preproc->newInclude(_token, true, false);
}
    break;

  case 20:

/* Line 690 of lalr1.cc  */
#line 183 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken _token = preprocessor::cToken(std::string((char *)(yysemantic_stack_[(4) - (3)].sym).m_data,(char *)(yysemantic_stack_[(4) - (3)].sym).m_data+(yysemantic_stack_[(4) - (3)].sym).m_leng),preprocessor::tokenType::IDENT);

    preproc->newInclude(_token, false, true);
}
    break;

  case 21:

/* Line 690 of lalr1.cc  */
#line 189 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken _token = preprocessor::cToken(std::string((char *)(yysemantic_stack_[(4) - (3)].sym).m_data,(char *)(yysemantic_stack_[(4) - (3)].sym).m_data+(yysemantic_stack_[(4) - (3)].sym).m_leng),preprocessor::tokenType::IDENT);

    preproc->newInclude(_token, true, true);
}
    break;

  case 22:

/* Line 690 of lalr1.cc  */
#line 196 "./preprocessor/preProcessor.ypp"
    {
    preproc->defineMacro(*(yysemantic_stack_[(5) - (2)].token),*(yysemantic_stack_[(5) - (3)].tokensArr),*(yysemantic_stack_[(5) - (4)].tokensArr),cMacroType::FUNCTION_LIKE);

    releaseMem((yysemantic_stack_[(5) - (2)].token));
    releaseMem((yysemantic_stack_[(5) - (3)].tokensArr));
    releaseMem((yysemantic_stack_[(5) - (4)].tokensArr));
}
    break;

  case 23:

/* Line 690 of lalr1.cc  */
#line 204 "./preprocessor/preProcessor.ypp"
    {
    preproc->defineMacro(*(yysemantic_stack_[(4) - (2)].token),tokenArray(),*(yysemantic_stack_[(4) - (3)].tokensArr),cMacroType::OBJECT_LIKE);
    releaseMem((yysemantic_stack_[(4) - (2)].token));
    releaseMem((yysemantic_stack_[(4) - (3)].tokensArr));
}
    break;

  case 24:

/* Line 690 of lalr1.cc  */
#line 210 "./preprocessor/preProcessor.ypp"
    {
    preproc->defineMacro(*(yysemantic_stack_[(4) - (2)].token),*(yysemantic_stack_[(4) - (3)].tokensArr),tokenArray(),cMacroType::FUNCTION_LIKE);
    releaseMem((yysemantic_stack_[(4) - (2)].token));
    releaseMem((yysemantic_stack_[(4) - (3)].tokensArr));
}
    break;

  case 25:

/* Line 690 of lalr1.cc  */
#line 216 "./preprocessor/preProcessor.ypp"
    {
    preproc->defineMacro(*(yysemantic_stack_[(3) - (2)].token),tokenArray(),tokenArray(),cMacroType::OBJECT_LIKE);
    releaseMem((yysemantic_stack_[(3) - (2)].token));
}
    break;

  case 26:

/* Line 690 of lalr1.cc  */
#line 222 "./preprocessor/preProcessor.ypp"
    {
    preproc->undefMacro(*(yysemantic_stack_[(3) - (2)].token));

    releaseMem((yysemantic_stack_[(3) - (2)].token));
}
    break;

  case 27:

/* Line 690 of lalr1.cc  */
#line 229 "./preprocessor/preProcessor.ypp"
    {
    preproc->newFailMsg(*(yysemantic_stack_[(3) - (2)].tokensArr), cFailMsgType::ERROR);

    releaseMem((yysemantic_stack_[(3) - (2)].tokensArr));
}
    break;

  case 28:

/* Line 690 of lalr1.cc  */
#line 235 "./preprocessor/preProcessor.ypp"
    {
    preproc->newFailMsg(std::vector<cToken>(), cFailMsgType::ERROR);
}
    break;

  case 29:

/* Line 690 of lalr1.cc  */
#line 240 "./preprocessor/preProcessor.ypp"
    {
    preproc->newFailMsg(*(yysemantic_stack_[(3) - (2)].tokensArr), cFailMsgType::WARNING);

    releaseMem((yysemantic_stack_[(3) - (2)].tokensArr));
}
    break;

  case 30:

/* Line 690 of lalr1.cc  */
#line 246 "./preprocessor/preProcessor.ypp"
    {
    preproc->newFailMsg(std::vector<cToken>(), cFailMsgType::WARNING);
}
    break;

  case 31:

/* Line 690 of lalr1.cc  */
#line 251 "./preprocessor/preProcessor.ypp"
    {
    preproc->newPragma(*(yysemantic_stack_[(3) - (2)].tokensArr));

    releaseMem((yysemantic_stack_[(3) - (2)].tokensArr));
}
    break;

  case 32:

/* Line 690 of lalr1.cc  */
#line 258 "./preprocessor/preProcessor.ypp"
    {
    bool cond = preprocessor::isBuiltIn(*(yysemantic_stack_[(3) - (2)].token)) || preproc->hasMacro(*(yysemantic_stack_[(3) - (2)].token));

    releaseMem((yysemantic_stack_[(3) - (2)].token));

    preproc->newIf(cond);

    (yyval.sym) = dataStr();
}
    break;

  case 33:

/* Line 690 of lalr1.cc  */
#line 268 "./preprocessor/preProcessor.ypp"
    {
    bool cond = preprocessor::isBuiltIn(*(yysemantic_stack_[(3) - (2)].token)) || preproc->hasMacro(*(yysemantic_stack_[(3) - (2)].token));

    releaseMem((yysemantic_stack_[(3) - (2)].token));

    preproc->newIf(!cond);

    (yyval.sym) = dataStr();
}
    break;

  case 34:

/* Line 690 of lalr1.cc  */
#line 278 "./preprocessor/preProcessor.ypp"
    {
    bool cond = (yysemantic_stack_[(3) - (2)].cond_expr);

    preproc->newIf(cond);

    (yyval.sym) = dataStr();
}
    break;

  case 35:

/* Line 690 of lalr1.cc  */
#line 286 "./preprocessor/preProcessor.ypp"
    {
    bool cond = (yysemantic_stack_[(3) - (2)].cond_expr);

    preproc->newElse(cond);

    (yyval.sym) = dataStr();
}
    break;

  case 36:

/* Line 690 of lalr1.cc  */
#line 294 "./preprocessor/preProcessor.ypp"
    {
    preproc->newElse(true);

    (yyval.sym) = dataStr();
}
    break;

  case 37:

/* Line 690 of lalr1.cc  */
#line 300 "./preprocessor/preProcessor.ypp"
    {
    preproc->newIfEnd();

    (yyval.sym) = dataStr();
}
    break;

  case 38:

/* Line 690 of lalr1.cc  */
#line 307 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = (yysemantic_stack_[(2) - (2)].val);
}
    break;

  case 39:

/* Line 690 of lalr1.cc  */
#line 312 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(1) - (1)].tokensArr);
}
    break;

  case 40:

/* Line 690 of lalr1.cc  */
#line 317 "./preprocessor/preProcessor.ypp"
    {
    (yyval.cond_expr) = (yysemantic_stack_[(1) - (1)].val) != 0;
}
    break;

  case 41:

/* Line 690 of lalr1.cc  */
#line 322 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = compute((yysemantic_stack_[(3) - (1)].val),(yysemantic_stack_[(3) - (3)].val),*(yysemantic_stack_[(3) - (2)].token));
}
    break;

  case 42:

/* Line 690 of lalr1.cc  */
#line 326 "./preprocessor/preProcessor.ypp"
    {
    bool cond = (yysemantic_stack_[(5) - (1)].val) != 0;

    if(cond)
    {
        (yyval.val) = (yysemantic_stack_[(5) - (3)].val);
    }
    else
    {
        (yyval.val) = (yysemantic_stack_[(5) - (5)].val);
    }
}
    break;

  case 43:

/* Line 690 of lalr1.cc  */
#line 339 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = (yysemantic_stack_[(1) - (1)].val);
}
    break;

  case 44:

/* Line 690 of lalr1.cc  */
#line 344 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = compute((yysemantic_stack_[(3) - (1)].val),(yysemantic_stack_[(3) - (3)].val),*(yysemantic_stack_[(3) - (2)].token)) != 0;
    releaseMem((yysemantic_stack_[(3) - (2)].token));
}
    break;

  case 45:

/* Line 690 of lalr1.cc  */
#line 349 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = compute((yysemantic_stack_[(2) - (2)].val),*(yysemantic_stack_[(2) - (1)].token));
}
    break;

  case 46:

/* Line 690 of lalr1.cc  */
#line 353 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = (yysemantic_stack_[(3) - (2)].val);
}
    break;

  case 47:

/* Line 690 of lalr1.cc  */
#line 357 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = (yysemantic_stack_[(1) - (1)].val);
}
    break;

  case 48:

/* Line 690 of lalr1.cc  */
#line 362 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = atoi((yysemantic_stack_[(1) - (1)].sym).m_data);
}
    break;

  case 49:

/* Line 690 of lalr1.cc  */
#line 366 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = preproc->macroEval(*(yysemantic_stack_[(1) - (1)].token), std::vector<preprocessor::cToken>());
    releaseMem((yysemantic_stack_[(1) - (1)].token));
}
    break;

  case 50:

/* Line 690 of lalr1.cc  */
#line 371 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = preproc->macroEval(*(yysemantic_stack_[(2) - (1)].token),*(yysemantic_stack_[(2) - (2)].tokensArr));
    releaseMem((yysemantic_stack_[(2) - (1)].token));
    releaseMem((yysemantic_stack_[(2) - (2)].tokensArr));
}
    break;

  case 51:

/* Line 690 of lalr1.cc  */
#line 377 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = preprocessor::isBuiltIn(*(yysemantic_stack_[(4) - (3)].token)) || preproc->hasMacro(*(yysemantic_stack_[(4) - (3)].token));

    releaseMem((yysemantic_stack_[(4) - (3)].token));
}
    break;

  case 52:

/* Line 690 of lalr1.cc  */
#line 383 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = preprocessor::isBuiltIn(*(yysemantic_stack_[(2) - (2)].token)) || preproc->hasMacro(*(yysemantic_stack_[(2) - (2)].token));

    releaseMem((yysemantic_stack_[(2) - (2)].token));
}
    break;

  case 53:

/* Line 690 of lalr1.cc  */
#line 390 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(3) - (3)].tokensArr);
}
    break;

  case 54:

/* Line 690 of lalr1.cc  */
#line 395 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(3) - (2)].tokensArr);
}
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 399 "./preprocessor/preProcessor.ypp"
    {
    tokenArray& arr = *(yysemantic_stack_[(2) - (-1)].tokensArr);
    (yyval.tokensArr) = &arr;
}
    break;

  case 56:

/* Line 690 of lalr1.cc  */
#line 405 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(3) - (1)].tokensArr);
}
    break;

  case 57:

/* Line 690 of lalr1.cc  */
#line 409 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(1) - (1)].tokensArr);
}
    break;

  case 58:

/* Line 690 of lalr1.cc  */
#line 414 "./preprocessor/preProcessor.ypp"
    {
    tokenArray& arr = *(yysemantic_stack_[(1) - (-1)].tokensArr);
    arr.push_back(*(yysemantic_stack_[(1) - (1)].token));
    releaseMem((yysemantic_stack_[(1) - (1)].token));
    (yyval.tokensArr) = &arr;
}
    break;

  case 59:

/* Line 690 of lalr1.cc  */
#line 421 "./preprocessor/preProcessor.ypp"
    {
    tokenArray& arr = *(yysemantic_stack_[(1) - (-1)].tokensArr);
    arr.push_back(*(yysemantic_stack_[(1) - (1)].token));
    releaseMem((yysemantic_stack_[(1) - (1)].token));
    (yyval.tokensArr) = &arr;
}
    break;

  case 60:

/* Line 690 of lalr1.cc  */
#line 429 "./preprocessor/preProcessor.ypp"
    {}
    break;

  case 61:

/* Line 690 of lalr1.cc  */
#line 432 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(2) - (2)].tokensArr);
}
    break;

  case 62:

/* Line 690 of lalr1.cc  */
#line 437 "./preprocessor/preProcessor.ypp"
    {
    tokenArray* res = new tokenArray();

    (yyval.tokensArr) = res;
}
    break;

  case 63:

/* Line 690 of lalr1.cc  */
#line 444 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken* res = new preprocessor::cToken();

    (yyval.token) = res;
}
    break;

  case 64:

/* Line 690 of lalr1.cc  */
#line 451 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(2) - (1)].tokensArr);
}
    break;

  case 65:

/* Line 690 of lalr1.cc  */
#line 455 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(1) - (1)].tokensArr);
}
    break;

  case 66:

/* Line 690 of lalr1.cc  */
#line 460 "./preprocessor/preProcessor.ypp"
    {
    (yyval.tokensArr) = (yysemantic_stack_[(1) - (1)].tokensArr);
}
    break;

  case 67:

/* Line 690 of lalr1.cc  */
#line 464 "./preprocessor/preProcessor.ypp"
    {
    tokenArray& arr = *(yysemantic_stack_[(1) - (0)].tokensArr);
    arr.push_back(*(yysemantic_stack_[(1) - (1)].token));
    releaseMem((yysemantic_stack_[(1) - (1)].token));
    (yyval.tokensArr) = &arr;
}
    break;

  case 68:

/* Line 690 of lalr1.cc  */
#line 471 "./preprocessor/preProcessor.ypp"
    {
    tokenArray& arr = *(yysemantic_stack_[(1) - (0)].tokensArr);
    preprocessor::cToken _token = preprocessor::cToken(std::string((char *)(yysemantic_stack_[(1) - (1)].sym).m_data,(char *)(yysemantic_stack_[(1) - (1)].sym).m_data+(yysemantic_stack_[(1) - (1)].sym).m_leng),preprocessor::tokenType::SYMBOL);
    arr.push_back(_token);
    (yyval.tokensArr) = &arr;
}
    break;

  case 69:

/* Line 690 of lalr1.cc  */
#line 478 "./preprocessor/preProcessor.ypp"
    {
    tokenArray& arr = *(yysemantic_stack_[(1) - (0)].tokensArr);
    preprocessor::cToken _token = preprocessor::cToken(std::string((char *)(yysemantic_stack_[(1) - (1)].sym).m_data,(char *)(yysemantic_stack_[(1) - (1)].sym).m_data+(yysemantic_stack_[(1) - (1)].sym).m_leng),preprocessor::tokenType::NUMBER);
    arr.push_back(_token);
    (yyval.tokensArr) = &arr;
}
    break;

  case 70:

/* Line 690 of lalr1.cc  */
#line 485 "./preprocessor/preProcessor.ypp"
    {
    tokenArray& arr = *(yysemantic_stack_[(1) - (0)].tokensArr);
    preprocessor::cToken _token = preprocessor::cToken(std::string((char *)(yysemantic_stack_[(1) - (1)].sym).m_data,(char *)(yysemantic_stack_[(1) - (1)].sym).m_data+(yysemantic_stack_[(1) - (1)].sym).m_leng),preprocessor::tokenType::LITERAL);
    arr.push_back(_token);
    (yyval.tokensArr) = &arr;
}
    break;

  case 71:

/* Line 690 of lalr1.cc  */
#line 493 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken _token;
    tokenArray& args = *(yysemantic_stack_[(1) - (1)].tokensArr);
    tokenArray& arr = *(yysemantic_stack_[(1) - (0)].tokensArr);

    //rewrite the related tokens for conforming a concat macro
    arr.push_back(cToken("__Concat__", tokenType::IDENT_CALL));
    arr.push_back(cToken("(", tokenType::SYMBOL));

    tokenArray::const_iterator itArg = args.begin();
    arr.push_back((*itArg));

    itArg++;
    for(;itArg!=args.end();itArg++)
    {
        arr.push_back(cToken(",", tokenType::IDENT));
        arr.push_back((*itArg));
    }

    arr.push_back(cToken(")", tokenType::SYMBOL));

    delete (yysemantic_stack_[(1) - (1)].tokensArr);

    (yyval.tokensArr) = &arr;
}
    break;

  case 72:

/* Line 690 of lalr1.cc  */
#line 519 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken _token;
    tokenArray& arr = *(yysemantic_stack_[(1) - (0)].tokensArr);

    //rewrite the related tokens for conforming a concat macro
    arr.push_back(cToken("__CollapseVariadic__", tokenType::IDENT_CALL));
    arr.push_back(cToken("(", tokenType::SYMBOL));
    arr.push_back(cToken("__VA_ARGS__",preprocessor::tokenType::IDENT));
    arr.push_back(cToken(")", tokenType::SYMBOL));

    (yyval.tokensArr) = &arr;
}
    break;

  case 73:

/* Line 690 of lalr1.cc  */
#line 532 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken _token;
    tokenArray& args = *(yysemantic_stack_[(1) - (1)].tokensArr);
    tokenArray& arr = *(yysemantic_stack_[(1) - (0)].tokensArr);

    //rewrite the related tokens for conforming a concat macro
    arr.push_back(cToken("# ",tokenType::IDENT));
    arr.push_back(args[0]);

    if(args.size() > 1)
    {
        arr.push_back(args[1]);
    }

    delete (yysemantic_stack_[(1) - (1)].tokensArr);

    (yyval.tokensArr) = &arr;
}
    break;

  case 74:

/* Line 690 of lalr1.cc  */
#line 551 "./preprocessor/preProcessor.ypp"
    {
    tokenArray& arr = *(yysemantic_stack_[(1) - (0)].tokensArr);
    tokenArray& args = *(yysemantic_stack_[(1) - (1)].tokensArr);

    //rewrite the related tokens for conforming a concat macro
    arr.push_back(cToken("__Stringized__",tokenType::IDENT_CALL));
    arr.push_back(cToken("(", tokenType::SYMBOL));
    arr.push_back(args[0]);
    arr.push_back(cToken(")", tokenType::SYMBOL));

    delete (yysemantic_stack_[(1) - (1)].tokensArr);

    (yyval.tokensArr) = &arr;
}
    break;

  case 75:

/* Line 690 of lalr1.cc  */
#line 567 "./preprocessor/preProcessor.ypp"
    {
    (yyval.token) = (yysemantic_stack_[(2) - (2)].token);
}
    break;

  case 76:

/* Line 690 of lalr1.cc  */
#line 572 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken& _token = *(yysemantic_stack_[(1) - (0)].token);
    _token = preprocessor::cToken((yysemantic_stack_[(1) - (1)].unit_sym),preprocessor::tokenType::SYMBOL);
    (yyval.token) = &_token;
}
    break;

  case 77:

/* Line 690 of lalr1.cc  */
#line 579 "./preprocessor/preProcessor.ypp"
    {
    (yyval.token) = (yysemantic_stack_[(2) - (2)].token);
}
    break;

  case 78:

/* Line 690 of lalr1.cc  */
#line 584 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken& _token = *(yysemantic_stack_[(1) - (0)].token);
    _token = preprocessor::cToken((yysemantic_stack_[(1) - (1)].unit_sym),preprocessor::tokenType::SYMBOL);
    (yyval.token) = &_token;
}
    break;

  case 79:

/* Line 690 of lalr1.cc  */
#line 591 "./preprocessor/preProcessor.ypp"
    {
    (yyval.token) = (yysemantic_stack_[(2) - (2)].token);
}
    break;

  case 80:

/* Line 690 of lalr1.cc  */
#line 596 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken& _token = *(yysemantic_stack_[(1) - (0)].token);
    _token = preprocessor::cToken(std::string((yysemantic_stack_[(1) - (1)].sym).m_data,(yysemantic_stack_[(1) - (1)].sym).m_data+(yysemantic_stack_[(1) - (1)].sym).m_leng),preprocessor::tokenType::IDENT);
    (yyval.token) = &_token;
}
    break;

  case 81:

/* Line 690 of lalr1.cc  */
#line 603 "./preprocessor/preProcessor.ypp"
    {
    (yyval.token) = (yysemantic_stack_[(2) - (2)].token);
}
    break;

  case 82:

/* Line 690 of lalr1.cc  */
#line 608 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken& _token = *(yysemantic_stack_[(1) - (0)].token);
    _token = preprocessor::expandBuiltinMacro((yysemantic_stack_[(1) - (1)].sym).m_data,scanner, tokenType::IDENT);
    (yyval.token) = &_token;
}
    break;

  case 83:

/* Line 690 of lalr1.cc  */
#line 614 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken& _token = *(yysemantic_stack_[(1) - (0)].token);
    _token = preprocessor::expandBuiltinMacro((yysemantic_stack_[(1) - (1)].sym).m_data,scanner, tokenType::IDENT_CALL);
    (yyval.token) = &_token;
}
    break;

  case 84:

/* Line 690 of lalr1.cc  */
#line 621 "./preprocessor/preProcessor.ypp"
    {
    (yyval.token) = (yysemantic_stack_[(2) - (2)].token);
}
    break;

  case 85:

/* Line 690 of lalr1.cc  */
#line 626 "./preprocessor/preProcessor.ypp"
    {
    preprocessor::cToken& _token = *(yysemantic_stack_[(1) - (0)].token);
    _token = preprocessor::cToken(std::string((char *)(yysemantic_stack_[(1) - (1)].sym).m_data,(char *)(yysemantic_stack_[(1) - (1)].sym).m_data+(yysemantic_stack_[(1) - (1)].sym).m_leng),preprocessor::tokenType::NUMBER);
    (yyval.token) = &_token;
}
    break;

  case 86:

/* Line 690 of lalr1.cc  */
#line 633 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = 1;
}
    break;

  case 87:

/* Line 690 of lalr1.cc  */
#line 637 "./preprocessor/preProcessor.ypp"
    {
    (yyval.val) = 1;
}
    break;



/* Line 690 of lalr1.cc  */
#line 1406 "./preprocessor/preProcessor.tab.cpp"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  cParser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = 0;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char cParser::yypact_ninf_ = -46;
  const short int
  cParser::yypact_[] =
  {
       134,   -46,   -46,   -46,    45,    12,     0,   -46,   -46,     0,
      -1,    -1,    -1,    -1,     0,   -46,   -46,    41,   -46,    99,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,    -1,
     158,    -1,     5,    -1,    -1,    33,    50,   -46,   -46,    55,
      57,    27,   -46,     0,    -1,   -46,     1,   -46,    -6,     0,
      31,    -1,    -1,    -1,   -46,   -46,   -46,   -46,    -1,   -46,
      -1,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,    51,   -46,   111,   -46,   -46,   -46,   -46,
      -1,    -1,   -46,    48,   -46,   -46,    61,    62,    65,    66,
     -46,   -46,    49,   -46,     0,    63,     0,    19,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,    -1,   -46,    52,   -46,   -46,   -46,   -46,
      59,   -46,    47,   -46,   -46,   -46,   -46,   -46,    64,   -46,
     -46,     0,   -46,    68,    72,    -3,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  cParser::yydefact_[] =
  {
        62,    62,    63,    63,     0,     0,    63,    63,    63,    63,
       0,     0,    62,    62,    63,    14,    15,     0,     2,    62,
      13,     5,     6,     7,    10,    11,    12,     8,     9,     0,
      63,     0,     0,    62,     0,     0,     0,    80,    17,     0,
       0,    63,    48,    63,     0,    40,    43,    47,     0,    63,
      49,     0,     0,     0,    87,    86,    36,    37,     0,    28,
       0,    30,    38,     1,     3,    16,    68,    70,    69,    72,
      71,    73,    74,     0,    61,    63,    66,    67,    31,    79,
       0,    62,    39,    63,    25,    26,     0,     0,     0,     0,
      63,    52,     0,    34,    63,     0,    63,    63,    82,    83,
      78,    77,    81,    45,    50,    60,    32,    33,    35,    27,
      29,    64,    23,     0,    24,     0,    18,    19,    20,    21,
       0,    46,     0,    76,    75,    41,    44,    22,    63,    53,
      51,    63,    55,     0,    57,     0,    58,    59,    42,    54,
      63,    85,    84,    56
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  cParser::yypgoto_[] =
  {
       -46,   -46,    75,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,    10,    93,   -11,   -45,     6,    56,   -46,
     -30,   -46,   -46,    17,   -16,    -2,    36,   -46,   -46,    81,
     -46,   -46,   -46,     7,    97,   -28,   -46,   -46,   -46,     9
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  cParser::yydefgoto_[] =
  {
        -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    80,    44,    45,    46,    47,    81,   129,
     133,   134,   115,    29,    30,    48,    74,    75,    76,    96,
     124,    49,   101,    33,    38,    50,   102,   137,   142,    56
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char cParser::yytable_ninf_ = -66;
  const short int
  cParser::yytable_[] =
  {
        32,    32,    77,    62,   103,    32,    32,    41,    98,    99,
      34,    98,    99,   141,    51,    52,    42,    83,    31,    37,
      57,    59,    61,    39,    40,   100,    41,    43,    73,    58,
      60,   -63,    92,    94,   105,    42,    54,    55,    65,    32,
      78,    63,    84,    85,    95,    95,    86,    77,    91,   122,
      82,    66,    67,    93,    90,    77,    35,    36,   -62,    37,
     106,   107,   108,    87,    68,    98,    99,   109,    88,   110,
      89,    69,   116,    73,   117,   -60,   118,   121,   119,   128,
     131,    73,    70,    71,    72,   125,   138,   130,    32,   112,
     114,   113,   132,   123,    64,    73,   139,   120,    82,    -4,
     136,   140,    53,   126,     1,     2,   104,     3,     4,     5,
     143,   111,   136,     0,    66,    67,     6,     7,     8,     9,
      10,    11,   127,    12,    13,    14,   135,    68,    97,    79,
       0,     0,     0,     0,    69,     0,    15,    16,   135,     1,
       2,     0,     3,     4,     5,    70,    71,    72,   -65,   -65,
       0,     6,     7,     8,     9,    10,    11,     0,    12,    13,
      14,    66,    67,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,     0,    68,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    71,    72
  };

  /* YYCHECK.  */
  const short int
  cParser::yycheck_[] =
  {
         2,     3,    30,    14,    49,     7,     8,     7,    14,    15,
       3,    14,    15,    16,     7,     8,    16,    33,     1,    14,
      11,    12,    13,    11,    12,    31,     7,    27,    30,    12,
      13,    30,    43,    32,    50,    16,    37,    38,    29,    41,
      31,     0,    33,    34,    46,    47,    13,    75,    41,    94,
      33,     3,     4,    44,    27,    83,    11,    12,    27,    14,
      51,    52,    53,    13,    16,    14,    15,    58,    13,    60,
      13,    23,    11,    75,    12,    27,    11,    28,    12,    27,
      33,    83,    34,    35,    36,    96,   131,    28,    90,    80,
      81,    81,    28,    30,    19,    97,    28,    90,    81,     0,
     128,    29,     9,    97,     5,     6,    50,     8,     9,    10,
     140,    75,   140,    -1,     3,     4,    17,    18,    19,    20,
      21,    22,   113,    24,    25,    26,   128,    16,    47,    32,
      -1,    -1,    -1,    -1,    23,    -1,    37,    38,   140,     5,
       6,    -1,     8,     9,    10,    34,    35,    36,    37,    38,
      -1,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  cParser::yystos_[] =
  {
         0,     5,     6,     8,     9,    10,    17,    18,    19,    20,
      21,    22,    24,    25,    26,    37,    38,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    62,
      63,    62,    64,    72,    72,    11,    12,    14,    73,    11,
      12,     7,    16,    27,    53,    54,    55,    56,    64,    70,
      74,    72,    72,    53,    37,    38,    78,    78,    62,    78,
      62,    78,    54,     0,    41,    78,     3,     4,    16,    23,
      34,    35,    36,    64,    65,    66,    67,    74,    78,    73,
      52,    57,    62,    63,    78,    78,    13,    13,    13,    13,
      27,    72,    54,    78,    32,    64,    68,    68,    14,    15,
      31,    71,    75,    55,    57,    63,    78,    78,    78,    78,
      78,    65,    78,    52,    78,    61,    11,    12,    11,    12,
      72,    28,    55,    30,    69,    54,    56,    78,    27,    58,
      28,    33,    28,    59,    60,    64,    74,    76,    55,    28,
      29,    16,    77,    59
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  cParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  cParser::yyr1_[] =
  {
         0,    39,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    43,    44,    44,    44,
      44,    44,    45,    45,    45,    45,    46,    47,    47,    48,
      48,    49,    50,    50,    50,    50,    50,    50,    51,    52,
      53,    54,    54,    54,    55,    55,    55,    55,    56,    56,
      56,    56,    56,    57,    58,    58,    59,    59,    60,    60,
      61,    62,    63,    64,    65,    65,    66,    66,    66,    66,
      66,    67,    67,    67,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    75,    76,    77,    78,    78
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  cParser::yyr2_[] =
  {
         0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     4,
       4,     4,     5,     4,     4,     3,     3,     3,     2,     3,
       2,     3,     3,     3,     3,     3,     2,     2,     2,     1,
       1,     3,     5,     1,     3,     2,     3,     1,     1,     1,
       2,     4,     2,     3,     3,     2,     3,     1,     1,     1,
       0,     2,     0,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     2,
       1,     2,     1,     1,     2,     1,     1,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const cParser::yytname_[] =
  {
    "$end", "error", "$undefined", "SYMBOLS", "LITERAL", "PRAGMA", "DEFINE",
  "DEFINED", "UNDEFINE", "INCLUDE", "INCLUDE_NEXT", "INCLUDE_COMMA_DELIM",
  "INCLUDE_GL_DELIM", "INCLUDE_FILENAME", "IDENT", "IDENT_CALL", "NUMBER",
  "IF", "IFDEF", "IFNDEF", "ELIF", "ELSE", "END",
  "BUILTIN_COLLAPSE_VARIADIC", "ERROR", "WARNING", "COMPUTE", "TLPAREN",
  "TRPAREN", "TCOMMA", "BINARY_OP", "UNARY_OP", "TERNARY_LEFT_OP",
  "TERNARY_RIGHT_OP", "BUILTIN_CONCAT", "BUILTIN_LINE",
  "BUILTIN_STRINGIZED", "COMMENT", "END_LINE", "$accept", "run",
  "compilation_unit", "stmnt", "newTokens", "include_token",
  "define_token", "undefine_token", "error_token", "warning_token",
  "pragma_token", "ifdef_token", "compute_token", "define_definition",
  "conditional_expr", "evaluate_expr", "evaluate_leave", "evaluate_factor",
  "args", "_args", "_arg", "_argsIdent", "foo", "tokens", "acquireArr",
  "acquireToken", "_tokens", "_tokensData", "builtin_macro", "binary_op",
  "_binary_op", "unary_op", "_unary_op", "ident_no_expand",
  "_ident_no_expand", "ident", "_ident", "number", "_number", "end_action", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const cParser::rhs_number_type
  cParser::yyrhs_[] =
  {
        40,     0,    -1,    41,    -1,    42,    41,    -1,    42,    -1,
      44,    -1,    45,    -1,    46,    -1,    50,    -1,    51,    -1,
      47,    -1,    48,    -1,    49,    -1,    43,    -1,    37,    -1,
      38,    -1,    62,    78,    -1,     9,    73,    -1,     9,    11,
      13,    11,    -1,     9,    12,    13,    12,    -1,    10,    11,
      13,    11,    -1,    10,    12,    13,    12,    -1,     6,    72,
      57,    52,    78,    -1,     6,    72,    52,    78,    -1,     6,
      72,    57,    78,    -1,     6,    72,    78,    -1,     8,    72,
      78,    -1,    24,    62,    78,    -1,    24,    78,    -1,    25,
      62,    78,    -1,    25,    78,    -1,     5,    62,    78,    -1,
      18,    72,    78,    -1,    19,    72,    78,    -1,    17,    53,
      78,    -1,    20,    53,    78,    -1,    21,    78,    -1,    22,
      78,    -1,    26,    54,    -1,    62,    -1,    54,    -1,    55,
      68,    54,    -1,    55,    32,    55,    33,    55,    -1,    55,
      -1,    56,    68,    56,    -1,    70,    55,    -1,    27,    54,
      28,    -1,    56,    -1,    16,    -1,    74,    -1,    74,    57,
      -1,     7,    27,    72,    28,    -1,     7,    72,    -1,    63,
      61,    58,    -1,    27,    59,    28,    -1,    27,    28,    -1,
      60,    29,    59,    -1,    60,    -1,    74,    -1,    76,    -1,
      -1,    63,    65,    -1,    -1,    -1,    66,    65,    -1,    66,
      -1,    67,    -1,    74,    -1,     3,    -1,    16,    -1,     4,
      -1,    34,    -1,    23,    -1,    35,    -1,    36,    -1,    64,
      69,    -1,    30,    -1,    64,    71,    -1,    31,    -1,    64,
      73,    -1,    14,    -1,    64,    75,    -1,    14,    -1,    15,
      -1,    64,    77,    -1,    16,    -1,    38,    -1,    37,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  cParser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    35,    38,    43,
      48,    53,    58,    64,    69,    74,    78,    82,    86,    89,
      93,    96,   100,   104,   108,   112,   116,   119,   122,   125,
     127,   129,   133,   139,   141,   145,   148,   152,   154,   156,
     158,   161,   166,   169,   173,   177,   180,   184,   186,   188,
     190,   191,   194,   195,   196,   199,   201,   203,   205,   207,
     209,   211,   213,   215,   217,   219,   222,   224,   227,   229,
     232,   234,   237,   239,   241,   244,   246,   248
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  cParser::yyrline_[] =
  {
         0,    79,    79,    87,    88,    90,    94,    98,   102,   106,
     111,   115,   119,   123,   127,   140,   146,   154,   170,   176,
     182,   188,   195,   203,   209,   215,   221,   228,   234,   239,
     245,   250,   257,   267,   277,   285,   293,   299,   306,   311,
     316,   321,   325,   338,   343,   348,   352,   356,   361,   365,
     370,   376,   382,   389,   394,   398,   404,   408,   413,   420,
     429,   431,   437,   444,   450,   454,   459,   463,   470,   477,
     484,   492,   518,   531,   550,   566,   571,   578,   583,   590,
     595,   602,   607,   613,   620,   625,   632,   636
  };

  // Print the state stack on the debug stream.
  void
  cParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  cParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  cParser::token_number_type
  cParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int cParser::yyeof_ = 0;
  const int cParser::yylast_ = 194;
  const int cParser::yynnts_ = 40;
  const int cParser::yyempty_ = -2;
  const int cParser::yyfinal_ = 63;
  const int cParser::yyterror_ = 1;
  const int cParser::yyerrcode_ = 256;
  const int cParser::yyntokens_ = 39;

  const unsigned int cParser::yyuser_token_number_max_ = 293;
  const cParser::token_number_type cParser::yyundef_token_ = 2;


/* Line 1136 of lalr1.cc  */
#line 5 "./preprocessor/preProcessor.ypp"
} // preprocessor

/* Line 1136 of lalr1.cc  */
#line 2044 "./preprocessor/preProcessor.tab.cpp"


/* Line 1138 of lalr1.cc  */
#line 641 "./preprocessor/preProcessor.ypp"

//-- FUNCTION DEFINITIONS ---------------------------------

template<typename T>
void releaseMem(T*& ptr)
{
    if(ptr)
    {
        delete ptr;
        ptr = NULL;
    }

    return;
}

int compute(int a, const preprocessor::cToken& op)
{
    int res = 0;

    if(op.m_name == "!")
    {
        res = (a == 0);
    }

    return res;
}

int compute(int a, int b, const preprocessor::cToken& op)
{
    int res = 0;

    if(op.m_name == "+")
    {
        res = a + b;
    }
    else if(op.m_name == "-")
    {
        res = a - b;
    }
    else if(op.m_name == "*")
    {
        res = a * b;
    }
    else if(op.m_name == "/")
    {
        res = a / b;
    }
    else if(op.m_name == "&&")
    {
        res = a && b;
    }
    else if(op.m_name == "||")
    {
        res = a || b;
    }
    else if(op.m_name == "==")
    {
        res = a == b;
    }
    else if(op.m_name == "!=")
    {
        res = a != b;
    }
    else if(op.m_name == ">")
    {
        res = a > b;
    }
    else if(op.m_name == ">=")
    {
        res = a >= b;
    }
    else if(op.m_name == "<")
    {
        res = a < b;
    }
    else if(op.m_name == "<=")
    {
        res = a <= b;
    }
    else if(op.m_name == "<<")
    {
        res = a << b;
    }
    else if(op.m_name == ">>")
    {
        res = a >> b;
    }
    else if(op.m_name == "&")
    {
        res = a & b;
    }
    else if(op.m_name == "|")
    {
        res = a | b;
    }

    return res;
}

void preprocessor::cParser::error( const preprocessor::cParser::location_type &l,
                           const std::string &err_message)
{
   std::cerr << "Error in file " << scanner.getCurrFile() << ", line " << scanner.getCurrLine() << ": " << err_message << "\n";
}

static int yylex(preprocessor::cParser::semantic_type* yylval, preprocessor::cScanner& scanner, preprocessor::IPreprocessor* preproc)
{
    int res = scanner.yylex(yylval);

    return res;
}


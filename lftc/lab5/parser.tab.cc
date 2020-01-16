// A Bison parser, made by GNU Bison 3.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 22 "parser.yy"

# include "driver.h"
# include <iostream>
using namespace std;

#line 51 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "parser.tab.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              else
                goto append;

            append:
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
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 33: // "number"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 32: // "identifier"
      case 34: // "string"
      case 35: // "char"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 33: // "number"
        value.move< int > (YY_MOVE (that.value));
        break;

      case 32: // "identifier"
      case 34: // "string"
      case 35: // "char"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 33: // "number"
        value.copy< int > (that.value);
        break;

      case 32: // "identifier"
      case 34: // "string"
      case 35: // "char"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 33: // "number"
        value.move< int > (that.value);
        break;

      case 32: // "identifier"
      case 34: // "string"
      case 35: // "char"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 32: // "identifier"
#line 67 "parser.yy"
                 { yyo << yysym.value.template as < std::string > (); }
#line 378 "parser.tab.cc"
        break;

      case 33: // "number"
#line 67 "parser.yy"
                 { yyo << yysym.value.template as < int > (); }
#line 384 "parser.tab.cc"
        break;

      case 34: // "string"
#line 67 "parser.yy"
                 { yyo << yysym.value.template as < std::string > (); }
#line 390 "parser.tab.cc"
        break;

      case 35: // "char"
#line 67 "parser.yy"
                 { yyo << yysym.value.template as < std::string > (); }
#line 396 "parser.tab.cc"
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", static_cast<state_type> (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 33: // "number"
        yylhs.value.emplace< int > ();
        break;

      case 32: // "identifier"
      case 34: // "string"
      case 35: // "char"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 71 "parser.yy"
                           { cout << "Parsed program through decllist." << endl; }
#line 647 "parser.tab.cc"
    break;

  case 3:
#line 72 "parser.yy"
                           { cout << "Parsed program trough cmpdstmt." << endl; }
#line 653 "parser.tab.cc"
    break;

  case 4:
#line 73 "parser.yy"
                           { cout << "Parsed program trough decllist & program." << endl; }
#line 659 "parser.tab.cc"
    break;

  case 5:
#line 74 "parser.yy"
                           { cout << "Parsed program trough cmpdstmt & program." << endl; }
#line 665 "parser.tab.cc"
    break;

  case 6:
#line 77 "parser.yy"
                       { cout << "Base case decllist." << endl; }
#line 671 "parser.tab.cc"
    break;

  case 7:
#line 78 "parser.yy"
                       { cout << "Recursive decllist." << endl; }
#line 677 "parser.tab.cc"
    break;

  case 8:
#line 80 "parser.yy"
                                                        { cout << "Type & identifier declaration." << endl; }
#line 683 "parser.tab.cc"
    break;

  case 9:
#line 81 "parser.yy"
                                                        { cout << "Type & identifier = constant." << endl; }
#line 689 "parser.tab.cc"
    break;

  case 10:
#line 82 "parser.yy"
                                                        { cout << "Type & identifier = identifierstruct." << endl; }
#line 695 "parser.tab.cc"
    break;

  case 11:
#line 83 "parser.yy"
                                                        { cout << "Type & structdecl." << endl; }
#line 701 "parser.tab.cc"
    break;

  case 12:
#line 85 "parser.yy"
                                      { cout << "Struct decl." << endl; }
#line 707 "parser.tab.cc"
    break;

  case 13:
#line 87 "parser.yy"
                                      { cout << "Assign statement." << endl; }
#line 713 "parser.tab.cc"
    break;

  case 14:
#line 89 "parser.yy"
                { cout << "Type: intt" << endl; }
#line 719 "parser.tab.cc"
    break;

  case 15:
#line 90 "parser.yy"
                { cout << "Type: chart" << endl; }
#line 725 "parser.tab.cc"
    break;

  case 16:
#line 91 "parser.yy"
                { cout << "Type: stringt" << endl; }
#line 731 "parser.tab.cc"
    break;

  case 17:
#line 93 "parser.yy"
                                                     { cout << "Identifier struct arrow." << endl; }
#line 737 "parser.tab.cc"
    break;

  case 18:
#line 94 "parser.yy"
                                                     { cout << "Identifier struct arrow." << endl; }
#line 743 "parser.tab.cc"
    break;

  case 19:
#line 96 "parser.yy"
                              { cout << "Condition expr." << endl; }
#line 749 "parser.tab.cc"
    break;

  case 20:
#line 98 "parser.yy"
               { cout << "Relation <." << endl; }
#line 755 "parser.tab.cc"
    break;

  case 21:
#line 99 "parser.yy"
               { cout << "Relation <=." << endl; }
#line 761 "parser.tab.cc"
    break;

  case 22:
#line 100 "parser.yy"
               { cout << "Relation ==." << endl; }
#line 767 "parser.tab.cc"
    break;

  case 23:
#line 101 "parser.yy"
               { cout << "Relation >=." << endl; }
#line 773 "parser.tab.cc"
    break;

  case 24:
#line 102 "parser.yy"
               { cout << "Relation >." << endl; }
#line 779 "parser.tab.cc"
    break;

  case 25:
#line 103 "parser.yy"
               { cout << "Relation !=." << endl; }
#line 785 "parser.tab.cc"
    break;

  case 26:
#line 105 "parser.yy"
                                    { cout << "IOStmt cin." << endl; }
#line 791 "parser.tab.cc"
    break;

  case 27:
#line 106 "parser.yy"
                                    { cout << "IOStmt cout." << endl; }
#line 797 "parser.tab.cc"
    break;

  case 28:
#line 108 "parser.yy"
                                                                        { cout << "Ifstmt." << endl; }
#line 803 "parser.tab.cc"
    break;

  case 29:
#line 109 "parser.yy"
                                                                        { cout << "Ifstmt else" << endl; }
#line 809 "parser.tab.cc"
    break;

  case 42:
#line 129 "parser.yy"
                   { cout << "Expr number." << endl; }
#line 815 "parser.tab.cc"
    break;

  case 43:
#line 130 "parser.yy"
                   { cout << "Expr string." << endl; }
#line 821 "parser.tab.cc"
    break;

  case 44:
#line 131 "parser.yy"
                   { cout << "Expr identifierstruct." << endl; }
#line 827 "parser.tab.cc"
    break;

  case 45:
#line 132 "parser.yy"
                   { cout << "Expr char." << endl; }
#line 833 "parser.tab.cc"
    break;

  case 46:
#line 133 "parser.yy"
                   { cout << "Expr sum." << endl; }
#line 839 "parser.tab.cc"
    break;

  case 47:
#line 134 "parser.yy"
                   { cout << "Expr diff." << endl; }
#line 845 "parser.tab.cc"
    break;

  case 48:
#line 135 "parser.yy"
                   { cout << "Expr prod." << endl; }
#line 851 "parser.tab.cc"
    break;

  case 49:
#line 136 "parser.yy"
                   { cout << "Expr div." << endl; }
#line 857 "parser.tab.cc"
    break;

  case 50:
#line 137 "parser.yy"
                   { cout << "Expr parens." << endl; }
#line 863 "parser.tab.cc"
    break;


#line 867 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = static_cast<state_type> (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
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

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
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


  const signed char parser::yypact_ninf_ = -81;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      53,    38,     5,    19,    73,    81,    51,   -81,   -81,   -81,
     -81,    95,    53,    93,    83,    85,    77,    37,    96,    98,
      41,   108,   109,    93,    78,     1,     1,     1,    93,   -81,
     -81,   -81,   -81,   -81,    35,     1,    94,   -81,   -81,    75,
     -81,   -81,   -81,     1,   111,     1,   -81,   -81,   -81,   111,
     115,   118,    -1,   119,   120,     1,   -81,   115,   -81,   -81,
     -81,   -81,   -81,   -81,   114,     9,     1,     1,     1,     1,
     122,   -81,   -81,   -81,   -81,   -81,   -81,     1,   123,   -81,
      72,    99,    75,   -81,    61,    61,   -81,   -81,    75,   115,
      75,   -81,   -81,    39,    68,    69,   124,   110,   -81,    75,
     125,    86,    75,   -81,    97,   -81
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    16,    14,    15,
      17,     0,     2,     6,     0,     0,     0,     0,     0,     0,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       4,     7,    11,    30,     0,     0,     0,    31,    32,     0,
       5,    33,    34,     0,    26,     0,    42,    43,    45,    44,
      27,     0,     0,     0,     0,     0,     8,    13,    18,    35,
      36,    37,    38,    39,     0,     0,     0,     0,     0,     0,
       0,    20,    24,    22,    21,    23,    25,     0,     0,    12,
      44,     0,     0,    50,    47,    46,    48,    49,     0,    19,
       0,    10,     9,     0,     0,     0,     0,    28,    40,     0,
       0,     0,     0,    41,     0,    29
  };

  const signed char
  parser::yypgoto_[] =
  {
     -81,    29,    24,   -81,   -81,   100,   -81,     0,   -20,   -81,
     101,   102,   -80,   103,   104,   -24
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    49,    51,    77,
      18,    19,    20,    21,    22,    52
  };

  const signed char
  parser::yytable_[] =
  {
      17,    50,    93,    66,    67,    68,    69,    53,    94,    45,
      95,    57,    17,    66,    67,    68,    69,    24,    83,   101,
      17,    65,   104,    64,    44,    71,    72,    73,    74,    75,
      76,    81,    25,    10,    46,    47,    48,    31,    55,    17,
      35,    30,    84,    85,    86,    87,    23,    43,    96,    40,
      56,    36,    54,    89,    39,    80,    39,     1,     2,     3,
       4,    28,     5,     6,     7,     8,     9,    68,    69,     1,
       2,     3,     4,    10,     5,     6,     7,     8,     9,    97,
      98,    26,    17,    39,    39,    10,    36,    91,    17,    27,
      17,     1,     2,     3,     4,    29,     5,   103,    32,    17,
      33,    39,    17,    66,    67,    68,    69,    10,   105,    34,
      10,    37,    39,    38,    92,     6,     7,     8,     9,    66,
      67,    68,    69,    41,    42,    36,    58,    70,    78,    82,
     100,    79,    88,    90,    99,   102,     0,     0,     0,    59,
      60,    61,    62,    63
  };

  const signed char
  parser::yycheck_[] =
  {
       0,    25,    82,     4,     5,     6,     7,    27,    88,     8,
      90,    35,    12,     4,     5,     6,     7,    12,     9,    99,
      20,    45,   102,    43,    24,    26,    27,    28,    29,    30,
      31,    55,    13,    32,    33,    34,    35,    13,     3,    39,
       3,    12,    66,    67,    68,    69,     8,    23,     9,    20,
      15,    14,    28,    77,    15,    55,    15,    16,    17,    18,
      19,    10,    21,    22,    23,    24,    25,     6,     7,    16,
      17,    18,    19,    32,    21,    22,    23,    24,    25,    11,
      11,     8,    82,    15,    15,    32,    14,    15,    88,     8,
      90,    16,    17,    18,    19,     0,    21,    11,    15,    99,
      15,    15,   102,     4,     5,     6,     7,    32,    11,    32,
      32,    15,    15,    15,    15,    22,    23,    24,    25,     4,
       5,     6,     7,    15,    15,    14,    32,     9,     9,    15,
      20,    11,    10,    10,    10,    10,    -1,    -1,    -1,    39,
      39,    39,    39,    39
  };

  const signed char
  parser::yystos_[] =
  {
       0,    16,    17,    18,    19,    21,    22,    23,    24,    25,
      32,    37,    38,    39,    40,    41,    42,    43,    46,    47,
      48,    49,    50,     8,    12,    13,     8,     8,    10,     0,
      37,    38,    15,    15,    32,     3,    14,    15,    15,    15,
      37,    15,    15,    38,    43,     8,    33,    34,    35,    43,
      51,    44,    51,    44,    38,     3,    15,    51,    32,    41,
      46,    47,    49,    50,    44,    51,     4,     5,     6,     7,
       9,    26,    27,    28,    29,    30,    31,    45,     9,    11,
      43,    51,    15,     9,    51,    51,    51,    51,    10,    51,
      10,    15,    15,    48,    48,    48,     9,    11,    11,    10,
      20,    48,    10,    11,    48,    11
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    36,    37,    37,    37,    37,    38,    38,    39,    39,
      39,    39,    40,    41,    42,    42,    42,    43,    43,    44,
      45,    45,    45,    45,    45,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      49,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      51
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     1,     2,     3,     5,
       5,     2,     4,     3,     1,     1,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     7,    11,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       7,    10,     1,     1,     1,     1,     3,     3,     3,     3,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"=\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"(\"", "\")\"", "\"{\"", "\"}\"", "\">>\"", "\"<<\"",
  "\"->\"", "\";\"", "\"for\"", "\"cin\"", "\"cout\"", "\"if\"",
  "\"else\"", "\"while\"", "\"struct\"", "\"stringt\"", "\"intt\"",
  "\"chart\"", "\"<\"", "\">\"", "\"==\"", "\"<=\"", "\">=\"", "\"!=\"",
  "\"identifier\"", "\"number\"", "\"string\"", "\"char\"", "$accept",
  "program", "decllist", "declaration", "structdecl", "assignstmt", "type",
  "identifierstruct", "condition", "relation", "iostmt", "ifstmt",
  "cmpdstmt", "whilestmt", "forstmt", "expr", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    71,    71,    72,    73,    74,    77,    78,    80,    81,
      82,    83,    85,    87,    89,    90,    91,    93,    94,    96,
      98,    99,   100,   101,   102,   103,   105,   106,   108,   109,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     122,   124,   129,   130,   131,   132,   133,   134,   135,   136,
     137
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1327 "parser.tab.cc"

#line 138 "parser.yy"


void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

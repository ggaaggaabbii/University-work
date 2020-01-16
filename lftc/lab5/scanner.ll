%{
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <cstring> // strerror
# include <string>
# include "driver.h"
# include "parser.hpp"
%}

%{
#if defined __GNUC__ && !defined __clang__ && 6 <= __GNUC__
# pragma GCC diagnostic ignored "-Wnull-dereference"
#endif

#if defined __clang__
# pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#elif defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
# pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif

#define FLEX_VERSION (YY_FLEX_MAJOR_VERSION * 100 + YY_FLEX_MINOR_VERSION)

#if FLEX_VERSION < 206 && defined __clang__
# pragma clang diagnostic ignored "-Wdocumentation"
#endif

#if FLEX_VERSION < 206
# if defined __clang__ && 6 <= __clang_major__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
# elif defined __GNUC__ && 7 <= __GNUC__
#  pragma GCC diagnostic ignored "-Wregister"
# endif
#endif

#if FLEX_VERSION < 206
# if defined __clang__
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wdocumentation"
#  pragma clang diagnostic ignored "-Wshorten-64-to-32"
#  pragma clang diagnostic ignored "-Wsign-conversion"
# elif defined __GNUC__
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wsign-conversion"
# endif
#endif
%}

%option noyywrap nounput noinput batch debug

%{
  yy::parser::symbol_type
  make_NUMBER (const std::string &s, const yy::parser::location_type& loc, int isNeg);
%}

id     [a-zA-Z][a-zA-Z_0-9]*
int    [0-9]+
string \"[^\"]*\"
char   '.'
blank  [ \t\r]

%{
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  yy::location& loc = drv.location;
  loc.step ();
%}

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"-"      return yy::parser::make_MINUS  (loc);
"+"      return yy::parser::make_PLUS   (loc);
"*"      return yy::parser::make_STAR   (loc);
"/"      return yy::parser::make_SLASH  (loc);
"("      return yy::parser::make_LPAREN (loc);
")"      return yy::parser::make_RPAREN (loc);
"{"      return yy::parser::make_LBRACKET (loc);
"}"      return yy::parser::make_RBRACKET (loc);
"="      return yy::parser::make_EQUALS (loc);
">>"     return yy::parser::make_RARR (loc);
"<<"     return yy::parser::make_LARR (loc);
";"      return yy::parser::make_SEMICOLON (loc);
"->"     return yy::parser::make_ARROW (loc);
"for"    return yy::parser::make_KWFOR (loc);
"cin"    return yy::parser::make_KWCIN (loc);
"if"     return yy::parser::make_KWIF (loc);
"else"   return yy::parser::make_KWELSE (loc);
"while"  return yy::parser::make_KWWHILE (loc);
"cout"   return yy::parser::make_KWCOUT (loc);
"struct" return yy::parser::make_KWSTRUCT (loc);
"int"    return yy::parser::make_KWINT (loc);
"char"   return yy::parser::make_KWCHAR (loc);
"string" return yy::parser::make_KWSTRING (loc);
"<"      return yy::parser::make_LT (loc);
">"      return yy::parser::make_GT (loc);
"=="     return yy::parser::make_EQ (loc);
"<="     return yy::parser::make_LE (loc);
">="     return yy::parser::make_GE (loc);
"!="     return yy::parser::make_NE (loc);

{char}   return yy::parser::make_CHAR (yytext, loc);
{string} return yy::parser::make_STRING (yytext, loc);
{int}    return make_NUMBER (yytext, loc, 0);
-{int}   return make_NUMBER (yytext, loc, 1);
{id}     return yy::parser::make_IDENTIFIER (yytext, loc);
.        {
           throw yy::parser::syntax_error
             (loc, "invalid character: " + std::string(yytext));
}
<<EOF>>  return yy::parser::make_END (loc);
%%

yy::parser::symbol_type
make_NUMBER (const std::string &s, const yy::parser::location_type& loc, int isNeg)
{
  errno = 0;
  long n = strtol (s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: " + s);

  if (isNeg) {
    return yy::parser::make_NUMBER (0 - ((int) n), loc);
  }

  return yy::parser::make_NUMBER((int) n, loc);
}

void
driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror(errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void
driver::scan_end ()
{
  fclose (yyin);
}

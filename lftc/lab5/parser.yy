%skeleton "lalr1.cc"
%require "3.4.1"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
  class driver;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.h"
# include <iostream>
using namespace std;
}

%define api.token.prefix {TOK_}
%token
  END  0     "end of file"
  EQUALS     "="
  MINUS      "-"
  PLUS       "+"
  STAR       "*"
  SLASH      "/"
  LPAREN     "("
  RPAREN     ")"
  LBRACKET   "{"
  RBRACKET   "}"
  RARR       ">>"
  LARR       "<<"
  ARROW      "->"
  SEMICOLON  ";"
  KWFOR      "for"
  KWCIN      "cin"
  KWCOUT     "cout"
  KWIF       "if"
  KWELSE     "else"
  KWWHILE    "while"
  KWSTRUCT   "struct"
  KWSTRING   "stringt"
  KWINT      "intt"
  KWCHAR     "chart"
  LT         "<"
  GT         ">"
  EQ         "=="
  LE         "<="
  GE         ">="
  NE         "!="
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%token <std::string> STRING "string"
%token <std::string> CHAR "char"

%printer { yyo << $$; } <*>;

%%
%start program;
program: decllist          { cout << "Parsed program through decllist." << endl; }
       | cmpdstmt          { cout << "Parsed program trough cmpdstmt." << endl; }
       | decllist program  { cout << "Parsed program trough decllist & program." << endl; }
       | cmpdstmt program  { cout << "Parsed program trough cmpdstmt & program." << endl; }

decllist:
  declaration          { cout << "Base case decllist." << endl; }

declaration: type "identifier"  ";"                     { cout << "Type & identifier declaration." << endl; }
           | type "identifier" "=" expr ";"             { cout << "Type & identifier = constant." << endl; }
           | type "identifier" "=" identifierstruct ";" { cout << "Type & identifier = identifierstruct." << endl; }
           | structdecl ";"                             { cout << "Type & structdecl." << endl; }

structdecl: "struct" "{" decllist "}" { cout << "Struct decl." << endl; }

assignstmt: identifierstruct "=" expr { cout << "Assign statement." << endl; }

type: "intt"    { cout << "Type: intt" << endl; }
    | "chart"   { cout << "Type: chart" << endl; }
    | "stringt" { cout << "Type: stringt" << endl; }

identifierstruct: "identifier"                       { cout << "Identifier." << endl; }
                | identifierstruct "->" "identifier" { cout << "Identifier struct arrow." << endl; }

condition: expr relation expr { cout << "Condition expr." << endl; }

relation: "<"  { cout << "Relation <." << endl; }
        | "<=" { cout << "Relation <=." << endl; }
        | "==" { cout << "Relation ==." << endl; }
        | ">=" { cout << "Relation >=." << endl; }
        | ">"  { cout << "Relation >." << endl; }
        | "!=" { cout << "Relation !=." << endl; }

iostmt: "cin" ">>" identifierstruct { cout << "IOStmt cin." << endl; }
      | "cout" "<<" expr            { cout << "IOStmt cout." << endl; }

ifstmt: "if" "(" condition ")" "{" cmpdstmt "}"                         { cout << "Ifstmt." << endl; }
      | "if" "(" condition ")" "{" cmpdstmt "}" "else" "{" cmpdstmt "}" { cout << "Ifstmt else" << endl; }

cmpdstmt: assignstmt ";"
        | iostmt ";"
        | ifstmt ";"
        | whilestmt ";"
        | forstmt ";"
        | cmpdstmt ";" assignstmt
        | cmpdstmt ";" iostmt
        | cmpdstmt ";" ifstmt
        | cmpdstmt ";" whilestmt
        | cmpdstmt ";" forstmt

whilestmt: "while" "(" condition ")" "{" cmpdstmt "}"

forstmt: "for" "(" decllist condition ";" cmpdstmt ")" "{" cmpdstmt "}"

%left "+" "-";
%left "*" "/";
expr:
  "number"         { cout << "Expr number." << endl; }
| "string"         { cout << "Expr string." << endl; }
| identifierstruct { cout << "Expr identifierstruct." << endl; }
| "char"           { cout << "Expr char." << endl; }
| expr "+" expr    { cout << "Expr sum." << endl; }
| expr "-" expr    { cout << "Expr diff." << endl; }
| expr "*" expr    { cout << "Expr prod." << endl; }
| expr "/" expr    { cout << "Expr div." << endl; }
| "(" expr ")"     { cout << "Expr parens." << endl; }
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

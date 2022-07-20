%{
#include "parser.tab.h"

int yylex();
%}

%%
"begin"                     { return BEGIN_KWD; }
"end"                       { return END; }
"int"                       { return TYPE; }
"arr"                       { return TYPE; }
"if"                        { return IF_COND; }
"then"                      { return IF_BLOCK; }
"while"                     { return LOOP_COND; }
"do"                        { return LOOP_BLOCK; }
"print"                     { return PRINT; }
";"                         { return SEMICOLON; }
"="                         { return ASSIGN; }
":"                         { return INDEX; }
","                         { return COMMA; }
"("                         { return PAR_BEGIN; }
")"                         { return PAR_END; }
"["                         { return CONST_ARR_BEGIN; }
"]"                         { return CONST_ARR_END; }
"+"                         { return OP; }
"-"                         { return OP; }
"*"                         { return OP; }
"/"                         { return OP; }
"@"                         { return DOT_OP; }
">"                         { return REL_OP; }
"<"                         { return REL_OP; }
">="                        { return REL_OP; }
"<="                        { return REL_OP; }
"!="                        { return REL_OP; }
"=="                        { return REL_OP; }
[_a-zA-Z][a-zA-Z0-9]*       { return IDENTIFIER; }
-?[0-9][0-9]*               { return INT_VAL; }
[ \t\n]                     { ; }
.                           { printf("unexpected character\n"); }
%%

int yywrap() {
    return 1;
}
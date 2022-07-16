%{
#include "parser.tab.h"
void yyerror (char *s);
int yylex();
%}

%%
"begin"                     { return BEGIN_KWD; }
"end"                       { return END; }
"int"                       { return INT; }
"arr"                       { return ARR; }
"<="                        { return LE; }
">="                        { return GE; }
"=="                        { return EQ; }
"!="                        { return NE; }
">"	                        { return GT; }
"<"	                        { return LT; }
[;=,]                       { return yytext[0]; }
[+\-\*/()]                  { return yytext[0]; }
[_a-zA-Z][_a-zA-Z0-9]*      { return IDENTIFIER; }
[-+1-9][0-9]*               { return NUMBER; }
[ \t\n]                     { ; }
.                           { printf("unexpected character\n"); }

%%
int yywrap() {
    return 1;
}
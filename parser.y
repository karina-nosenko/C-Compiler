%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdbool.h>

    #define VARNAME_LEN 20
    #define TYPE_LEN 10
    #define LABEL_LEN 200
    #define TABLE_SIZE 10000
    #define STACK_SIZE 1000

    void yyerror(char* s);
    int yylex();
    void setType();
    bool isVarDeclared(char variableName[VARNAME_LEN]);
    void assertVarDeclared();
    void declare();
    void push();

    extern char *yytext;
%}

%start program
%token BEGIN_KWD END INT ARR
%token NUMBER
%token IDENTIFIER

%%
program             : { printf("#include <stdio.h>\n#include <stdlib.h>\nint main() {\n"); }  block   { printf("}"); return 0; }

block               : BEGIN_KWD { printf("{\n"); } statement_list END { printf("}\n"); }

statement_list      : /* empty */                               
                    | statement_list statement                  
                    ;       

statement           : declarator ';'                                        
                    | assignment_list ';'                                       
                    ;       

declarator          : type { setType(); } IDENTIFIER { declare(); } variable_list

variable_list       : /* empty */  
                    | ',' IDENTIFIER { declare(); } variable_list
                    ;

assignment_list     : assignment                                
                    | assignment_list ',' assignment            
                    ;

assignment          : IDENTIFIER { push(); } '=' { push(); } expression
                    ;                

expression          : expression '+' { push(); } expression                       
                    | expression '-' { push(); } expression                       
                    | expression '*' { push(); } expression                       
                    | expression '/' { push(); } expression
                    | IDENTIFIER { assertVarDeclared(); push(); }
                    | NUMBER { push(); }
                    ;       

type                : INT                                       
                    | ARR
                    ;
%%
char temp[2]="t";
int label[LABEL_LEN];

struct Table
{
	char id[VARNAME_LEN];
	char type[TYPE_LEN];
} table[TABLE_SIZE];
int tableCurrentIndex = 0;
char type[TYPE_LEN];

char st[STACK_SIZE][10];
int top=0;

int main(void) {
    return yyparse();
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}

/* SYMBOL TABLE */

void setType() {
	strcpy(type,yytext);
}

bool isVarDeclared(char variableName[VARNAME_LEN]) {
    for(int i=0; i<tableCurrentIndex; i++) {
        if (strcmp(table[i].id, variableName) == 0) {
            return true;
        }
    }
    return false;
}

void assertVarDeclared() {
    char variableName[VARNAME_LEN];
    strcpy(variableName, yytext);

    if(!isVarDeclared(variableName)) {
        yyerror("Variable not declared.");
		exit(0);
    }
}

void declare() {
    char variableName[VARNAME_LEN];
    strcpy(variableName, yytext);

    if(isVarDeclared(variableName)) {
        yyerror("Multiple variable name declaration.");
        exit(0);
    }

    strcpy(table[tableCurrentIndex].id, variableName);
    strcpy(table[tableCurrentIndex].type, type);
    tableCurrentIndex++;
}

/* STACK */

void push() {
    strcpy(st[++top], yytext);
}
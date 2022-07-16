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
    void codegen_declare();
    void codegen_assign();
    void codegen_arithmetic();
    void codegen_relop();
    void codegen_free();

    extern char *yytext;
%}

%start program
%token BEGIN_KWD END INT ARR
%token NUMBER
%token IDENTIFIER
%token LE GE EQ NE GT LT
%right '=' 
%left EQ NE 
%left LE GE LT GT
%left '+' '-' 
%left '*' '/' '@'

%%
program             : { printf("#include <stdio.h>\n#include <stdlib.h>\n\nint main()\n"); }  block   { return 0; }

block               : BEGIN_KWD { printf("{\n"); } statement_list END { codegen_free(); printf("}\n"); }

statement_list      : /* empty */                               
                    | statement_list statement                  
                    ;       

statement           : declarator ';'                                        
                    | assignment_list ';'                                       
                    ;       

declarator          : type { setType(); } IDENTIFIER { declare(); push(); codegen_declare(); } variable_list

variable_list       : /* empty */  
                    | ',' IDENTIFIER { declare(); push(); codegen_declare(); } variable_list
                    ;

assignment_list     : assignment                                
                    | assignment_list ',' assignment            
                    ;

assignment          : IDENTIFIER { assertVarDeclared(); push(); } '=' { push(); } expression { codegen_assign(); }
                    ;                

expression          : expression '+' { push(); } expression { codegen_arithmetic(); }                        
                    | expression '-' { push(); } expression { codegen_arithmetic(); }                       
                    | expression '*' { push(); } expression { codegen_arithmetic(); }                       
                    | expression '/' { push(); } expression { codegen_arithmetic(); }
                    | expression LT { push(); } expression { codegen_relop(); }
                    | expression LE { push(); } expression { codegen_relop(); }
                    | expression GT { push(); } expression { codegen_relop(); }
                    | expression GE { push(); } expression { codegen_relop(); }
                    | expression NE { push(); } expression { codegen_relop(); }
                    | expression EQ { push(); } expression { codegen_relop(); }
                    | '(' expression ')'
                    | IDENTIFIER { assertVarDeclared(); push(); }
                    | NUMBER { push(); }
                    ;       

type                : INT                                       
                    | ARR
                    ;
%%
int label[LABEL_LEN];

struct Table
{
	char id[VARNAME_LEN];
	char type[TYPE_LEN];
    int arr_size;   // size of the array if the type is arr
} table[TABLE_SIZE];
int tableCurrentIndex = 0;
char type[TYPE_LEN];

char st[STACK_SIZE][10];
int top=0;

// for temporary variable names
char temp[2]="t";
int i = 0;

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
    if(!isVarDeclared(yytext)) {
        yyerror("Variable not declared");
		exit(0);
    }
}

void declare() {
    char variableName[VARNAME_LEN];
    strcpy(variableName, yytext);

    if (isVarDeclared(variableName)) {
        yyerror("Multiple variable name declarations");
        exit(0);
    }

    strcpy(table[tableCurrentIndex].id, variableName);
    strcpy(table[tableCurrentIndex].type, type);

    if (strcmp(type, "arr") == 0) {
        table[tableCurrentIndex].arr_size = 0;
    }

    tableCurrentIndex++;
}

/* STACK */

void push() {
    strcpy(st[++top], yytext);
}

/* CODE GENERATORS */

void codegen_declare() {
    if (strcmp(type, "arr") == 0) {
        printf("\tint* %s;\n", st[top--]);  // arr x;
    } else {
        printf("\tint %s;\n", st[top--]);  // int x;
    }
}

void codegen_assign() {
    printf("\t%s = %s;\n", st[top-2], st[top]);    // x = 5;
    top -= 3;
}

void codegen_arithmetic() {
    sprintf(temp, "t%d", i++);
    printf("\tint %s = %s %s %s;\n", temp, st[top-2], st[top-1], st[top]);   // t1 = 5 + 4
    top -=2;
    strcpy(st[top], temp);
}

void codegen_relop() {
    sprintf(temp, "t%d", i++);
    printf("\tint %s = %s %s %s;\n", temp, st[top-2], st[top-1], st[top]);   // t1 = 5 < 4
    top -=2;
    strcpy(st[top], temp);
}

void codegen_free() {
    for(int i=0; i<tableCurrentIndex; i++) {
        if (strcmp(table[i].type, "arr")==0 && table[i].arr_size > 0) {
            printf("\tfree(%s);\n", table[i].id);   // free(x)
        }
    }
}
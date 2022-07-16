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
    void codegen_expList();
    void codegen_exp();
    void codegen_print();
    void codegen_arithmetic();
    void codegen_cond();
    void codegen_free();
    void tab_print(int a);
    
    extern char *yytext;

    int expListCount = 0;
%}

%start program
%token BEGIN_KWD END
%token TYPE
%token IF_COND IF_BLOCK
%token LOOP_COND LOOP_BLOCK
%token PRINT
%token SEMICOLON ASSIGN INDEX COMMA
%token PAR_BEGIN PAR_END
%token CONST_ARR_BEGIN CONST_ARR_END
%token OP DOT_OP REL_OP
%token INT_VAL
%token IDENTIFIER

%%
program             : { printf("#include <stdio.h>\n\nint main()\n"); }  block   { return 0; }

block               : BEGIN_KWD { tab_print(1); printf("{\n"); } statement_list END { codegen_free(); tab_print(-1); printf("}\n"); }

statement_list      : statement                               
                    | statement statement_list
                    ;       

statement           : declarator SEMICOLON
                    | assignment SEMICOLON
                    | print SEMICOLON
                    | conditional
                    | loop
                    ;       

declarator          : TYPE { setType(); } variable_list

assignment          : variable_declared ASSIGN expression { codegen_assign(); }
                    ;

conditional         : IF_COND { tab_print(0); printf("if("); } cond IF_BLOCK { printf(")\n"); } block
                    ;

loop                : LOOP_COND { tab_print(0); printf("while("); } cond LOOP_BLOCK { printf(")\n"); } block
                    ;

print               : PRINT expression_list { tab_print(0); codegen_print(); }
                    ;

variable_list       : variable_declare 
                    | variable_declare COMMA variable_list
                    ;

expression_list     : expression { codegen_exp(); expListCount++; }
                    | expression COMMA { codegen_expList(); expListCount++; } expression_list
                    ;

variable_declare    : IDENTIFIER { declare(); push(); codegen_declare(); }
                    ;

variable_declared   : IDENTIFIER { assertVarDeclared(); push(); }
                    ;

expression          : expression OP { push(); } expression { codegen_arithmetic(); }
                    /*TODO| expression DOT_OP { push(); } expression { codegen_dotproduct(); }*/
                    | PAR_BEGIN { push(); } expression PAR_END { push(); codegen_arithmetic(); }
                    | variable_declared
                    | number
                    ;       

cond                : expression REL_OP { push(); } expression { codegen_cond(); }
                    ;
number              : INT_VAL { push(); }
                    | const_arr
                    ;
const_arr           : CONST_ARR_BEGIN CONST_ARR_END
                    | CONST_ARR_BEGIN expression_list CONST_ARR_END
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
		exit(1);
    }
}

void declare() {
    char variableName[VARNAME_LEN];
    strcpy(variableName, yytext);

    if (isVarDeclared(variableName)) {
        yyerror("Multiple variable name declarations");
        exit(1);
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
        printf("\tint* %s = NULL;\n", st[top--]);  // arr x;
    } else {
        printf("\tint %s;\n", st[top--]);  // int x;
    }
}

void codegen_assign() {
    tab_print(0);
    printf("%s = %s;\n", st[top-1], st[top]);    // x = 5;
    top -= 2;
}

void codegen_arithmetic() {
    char expVal[STACK_SIZE];
    sprintf(expVal, "%s %s %s", st[top-2], st[top-1], st[top]);
    top -= 2;
    strcpy(st[top], expVal);
}

void codegen_exp() {
    char expVal[STACK_SIZE];
    if(expListCount) {
        sprintf(expVal, "%s %s", st[top - 1], st[top]);
    } else {
        sprintf(expVal, "%s", st[top]);
    }
    strcpy(st[--top], expVal);
}

void codegen_expList() {
    char expVal[STACK_SIZE];
    if(expListCount) {
        sprintf(expVal, "%s %s,", st[top - 1], st[top]);
    } else {
        sprintf(expVal, "%s,", st[top]);
    }
    strcpy(st[--top], expVal);
}

void codegen_print() {
    if(expListCount == 0) {
        yyerror("cant print nothing");
    }
    printf("printf(\"%c%c", '%', 'd');
    for(int i = 1; i < expListCount; i++) {
        printf(", %c%c", '%', 'd');
    }
    printf("\", %s);\n", st[top--]);
    expListCount = 0;
}

void codegen_cond() {
    codegen_arithmetic();
    printf("%s", st[top--]);
}
void codegen_free() {
    for(int i=0; i<tableCurrentIndex; i++) {
        if (strcmp(table[i].type, "arr")==0 && table[i].arr_size > 0) {
            printf("\tfree(%s);\n", table[i].id);   // free(x)
        }
    }
}

void tab_print(int a) {
    static int tabCount = 0;
    if(a < 0)
        tabCount += a;
    for(int i = 0; i < tabCount; i++)
        printf("\t");
    if(a > 0)
        tabCount += a;
}
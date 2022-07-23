%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdbool.h>
    #include "symbol_table.h"
    #include "stack.h"

    #define TYPE_LEN 4
    #define LABEL_LEN 100
    #define TOKEN_LEN 100
    
    //#define dbg
    #ifdef dbg
    #define YYDEBUG 1
    #define YYERROR_VERBOSE
    int yydebug = 1;
    #endif

    extern int yylex();

    void yyerror(char (*type)[TYPE_LEN], char* s);
    TokenType assert_var_status(char var_name[TOKEN_LEN], bool required);
    
    void begin_program();
    void begin_block();
    void end_block();
    void end_program();
    void codegen_declare(char (*type)[TYPE_LEN], char var_name[TOKEN_LEN]);
    void codegen_assign();
    void codegen_expList();
    void codegen_print();
    void codegen_arithmetic();
    void codegen_if();
    void codegen_while();
    void codegen_free();
    void tab_print(int a);
    
    extern char *yytext;

    int expListCount = 0;
    int lts = 0;
%}

%start program
%token BEGIN_KWD END
%token TYPE
%token IF_COND IF_BLOCK
%token LOOP_COND LOOP_BLOCK
%token PRINT
%token SEMICOLON INDEX COMMA
%token PAR_BEGIN PAR_END
%token CONST_ARR_BEGIN CONST_ARR_END
%token INT_VAL
%token IDENTIFIER
%left OP DOT_OP REL_OP
%right ASSIGN
%parse-param {char (*type)[4]}

%%
program             : { begin_program(); }  block   { end_program(); return 0; }
                    ;

block               : BEGIN_KWD { begin_block(); } statement_list END { end_block(); }
                    ;

statement_list      : statement                               
                    | statement statement_list
                    ;       

statement           : declarator SEMICOLON
                    | assignment SEMICOLON
                    | print SEMICOLON
                    | conditional
                    | loop
                    ;       

declarator          : TYPE { strcpy(*type,yytext); } variable_list
                    ;

assignment          : variable_declared ASSIGN expression { codegen_assign(); }
                    ;

conditional         : IF_COND cond IF_BLOCK { codegen_if(); } block
                    ;

loop                : LOOP_COND cond LOOP_BLOCK { codegen_while(); } block
                    ;

print               : PRINT expression_list { codegen_print(); }
                    ;

variable_list       : variable_declare 
                    | variable_declare COMMA variable_list
                    ;

expression_list     : expression { codegen_expList(); }
                    | expression COMMA { codegen_expList(); } expression_list
                    ;

variable_declare    : IDENTIFIER { codegen_declare(type, yytext); }
                    ;

variable_declared   : IDENTIFIER { push(NULL, yytext, assert_var_status(yytext, true)); }
                    ;

expression          : expression OP { push(NULL, yytext, OPERATOR); } expression { codegen_arithmetic(); }
                    /*| expression DOT_OP { push(); } expression { codegen_dotproduct(); }*/
                    | PAR_BEGIN { push(NULL, yytext, OPERATOR); } expression PAR_END { push(NULL, yytext, OPERATOR); codegen_arithmetic(); }
                    | variable_declared {}
                    | number {}
                    ;      

cond                : expression REL_OP { push(NULL, yytext, REL_OPERATOR); } expression { codegen_arithmetic(); }
                    ;

number              : INT_VAL { push(NULL, yytext, INT); }
                    ;
%%

int main(void) {
    Table table;
    Stack stack;
    char type[TYPE_LEN];

    table.size = 0;
    insert(&table, (Variable){0});
    get(&table, NULL, NULL, 0);
    find(&table, NULL);
    size(&table);

    stack.top = -1;
    push(&stack, NULL, EXP_LIST);
    pop(&stack, NULL);

    return yyparse(&type);
}

void yyerror(char (*type)[TYPE_LEN], char* s) {
	fprintf(stderr, "error: %s\n", s);
}

void error(char* s) {
    yyerror(NULL, s);
}

/////////////

bool isInteger(char token[TOKEN_LEN]) {
    for(int i = (token[0] == '-'); i < TOKEN_LEN && token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

bool isConstArray(char token[TOKEN_LEN]) {
    return (token[0] == '[' && token[strnlen_s(token, TOKEN_LEN) - 1] == ']');
}

int getConstArrSize(char array[TOKEN_LEN]) {
    bool empty = true;
    int numOfCommas = 0;
    for(int i=1; i<TOKEN_LEN && array[i]!='\0' && array[i]!=']'; i++) {
        if (isdigit(array[i])) {
            empty = false;
        }
        if (array[i] == ',') {
            numOfCommas++;
        }
    }

    if (empty) {
        return 0;
    } else {
        return numOfCommas + 1;
    }
}

/*TokenType getType(char token[TOKEN_LEN]) {
    if (isInteger(token)) {
        return INTEGER;
    } else if (isConstArray(token)) {
        return ARRAY;
    } else {
        VariablePtr variable = findVar(table, token);
        if(variable) {
            return variable->type;
        } else {
            error("Variable wasn\'t found");
		    exit(1);
        }
    }
}*/

TokenType assert_var_status(char var_name[TOKEN_LEN], bool required) {
    if((find(NULL, var_name) >= 0) != required) {
        char errorMsg[TOKEN_LEN];
        sprintf(errorMsg, "Variable %s %s.\n", var_name, (required ? " not declared" : " already declared."));
        error(errorMsg);
        exit(1);
    } else if(!required) {
        return 0;
    }
    Variable var;
    get(NULL, &var, var_name, 0);
    return var.type;
}

void declare(char (*type)[4], char var_name[TOKEN_LEN]) {
    Variable var;
    bool isInt = strcmp(*type, "int") == 0;
    
    assert_var_status(var_name, false);

    strcpy(var.id, var_name);
    var.type = isInt;
    var.arr_size = isInt;

    // add var to table
    insert(NULL, var);
}

/* CODE GENERATORS */

void begin_program() {
    printf("#include <stdio.h>\n");
    printf("#include <malloc.h>\n");
    printf("\n");
    tab_print(1);
    printf("int main() {\n");
    tab_print(0);
    printf("int **ts = NULL;\n");
    tab_print(0);
    printf("int *ls = NULL;\n");
    tab_print(0);
    printf("int lts = 0;\n");
}

void begin_block() {
    tab_print(1);
    printf("{\n"); 
}

void end_block() {
    
    tab_print(-1);
    printf("}\n");
}

void end_program() {
    printf("\n");
    codegen_free();
    tab_print(-1);
    printf("}\n");
}

void codegen_declare(char (*type)[TYPE_LEN], char var_name[TOKEN_LEN]) {
    // add variable to variable table
    declare(type, var_name);

    // print variable to output
    tab_print(0);
    if (strcmp(*type, "arr") == 0) {
        printf("int* %s = NULL;\n", yytext);  // arr x;
    } else {
        printf("int %s;\n", yytext);  // int x;
    }
}

void codegen_assign() {
    StackMember var_name, exp;
    pop(NULL, &exp);
    pop(NULL, &var_name);
    if(var_name.type == INT) {
        tab_print(0);
        printf("%s = %s;\n", var_name.token, exp.token);    // x = 5;
    }/* else {
        tab_print(0);
        printf("%s = realloc(%s, sizeof(int) * %d);\n", var_name.token, var_name.token, );
        tab_print(1);
        
        printf("for(int i = 0; i < %d; i++) {\n", );
        tab_print(0);
        printf("%s[i] = ");
        tab_print(-1);
        printf("}\n");
    }*/
}

void codegen_arithmetic() {
    StackMember m1, m2, m3;
    char expVal[TOKEN_LEN];

    pop(NULL, &m3);
    pop(NULL, &m2);
    pop(NULL, &m1);
    
    if((m1.type != m3.type) || (m1.type == m3.type && m2.type == REL_OPERATOR && m1.type != INT)) {
        error("Type Mismatch.");
        exit(1);
    }
    
    switch(m1.type) {
    case INT:
        if(m2.type == REL_OPERATOR) {
            sprintf(expVal, "%s %s %s", m1.token, m2.token, m3.token);
        } else {
        tab_print(0);
        printf("lts++;\n");
        tab_print(0);
        printf("ts = realloc(ts, sizeof(int*) * lts);\n");
        tab_print(0);
        printf("ls = realloc(ls, sizeof(int) * lts);\n");
        tab_print(0);
        printf("ls[lts - 1] = 1;\n");
        tab_print(0);
        printf("ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);\n");
        tab_print(0);
        printf("ts[lts - 1][0] = %s %s %s;\n", m1.token, m2.token, m3.token);
        sprintf(expVal, "ts[%d][0]", lts++);
        }
        push(NULL, expVal, INT);
        break;
    case ARR:

        break;
    case OPERATOR:
        push(NULL, m2.token, m2.type);
        break;
    }
}

void codegen_expList() {
    char expVal[TOKEN_LEN];
    if(expListCount) {
        StackMember exp1, exp2;
        pop(NULL, &exp2);
        pop(NULL, &exp1);
        if(exp2.type == ARR) {
            error("can\'t print array like this, please use a loop.");
            exit(1);
        }
        sprintf(expVal, "%s, %s", exp1.token, exp2.token);
    } else {
        StackMember exp;
        pop(NULL, &exp);
        if(exp.type == ARR) {
            error("can\'t print array like this, please use a loop.");
            exit(1);
        }
        sprintf(expVal, "%s", exp.token);
    }
    push(NULL, expVal, EXP_LIST);
    expListCount++; 
}

void codegen_print() {
    if(expListCount == 0) {
        error("can\'t print nothing");
    }

    StackMember expList;
    pop(NULL, &expList);

    tab_print(0);
    printf("printf(\"%c%c", '%', 'd');
    for(int i = 1; i < expListCount; i++) {
        printf(", %c%c", '%', 'd');
    }

    printf("\\n\", %s);\n", expList.token);
    expListCount = 0;
}

void codegen_if() {
    StackMember cond;
    pop(NULL, &cond);
    tab_print(0);
    printf("if(%s)\n", cond.token);
}

void codegen_while() {
    StackMember cond;
    pop(NULL, &cond);
    tab_print(0);
    printf("while(%s)\n", cond.token);
}

void codegen_free() {
    int tSize = size(NULL);
    Variable var;
    for(int i=0; i < tSize; i++) {
        get(NULL, &var, NULL, i);
        if ((var.type == ARRAY) && var.arr_size > 0) {
            tab_print(0);
            printf("free(%s);\n", var.id);   // free(x)
        }
    }
    tab_print(1);
    printf("for(int i = 0; i < lts; i++) {\n");
    tab_print(0);
    printf("free(ts[i]);\n");
    tab_print(-1);
    printf("}\n");
    tab_print(0);
    printf("free(ls);\n");
    tab_print(0);
    printf("free(ts);\n");
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
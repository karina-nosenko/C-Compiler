%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdbool.h>

    #define TYPE_LEN 4
    #define LABEL_LEN 100
    #define TOKEN_LEN 100
    #define TABLE_SIZE 10000
    #define STACK_SIZE 1000

    typedef enum {
        INTEGER,
        ARRAY
    } TokenType;
    
    typedef struct {
        char id[TOKEN_LEN];
        char type[TYPE_LEN];
        int arr_size;   // size of the array if the type is arr
    } Variable, *VariablePtr;

    typedef struct {
        Variable table[TABLE_SIZE];
        int size;
    } VariableTable, *VariableTablePtr;

    typedef struct {
        char st[STACK_SIZE][TOKEN_LEN];
        int top;
    } Stack, *StackPtr;

    extern int yylex();

    void yyerror(VariableTablePtr table, StackPtr stack, char (*type)[TYPE_LEN], char* s);
    void assert_var_status(VariableTablePtr table, bool req_status);
    void push(StackPtr stack);
    void codegen_declare(VariableTablePtr table, StackPtr stack, char (*type)[TYPE_LEN]);
    void codegen_assign(StackPtr stack);
    void codegen_exp(StackPtr stack);
    void codegen_print(StackPtr stack);
    void codegen_arithmetic(StackPtr stack);
    void codegen_if(StackPtr stack);
    void codegen_while(StackPtr stack);
    void codegen_free(VariableTablePtr table);
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
%token SEMICOLON INDEX COMMA
%token PAR_BEGIN PAR_END
%token CONST_ARR_BEGIN CONST_ARR_END
%token INT_VAL
%token IDENTIFIER
%left OP DOT_OP REL_OP
%right ASSIGN
%parse-param {VariableTablePtr table}
%parse-param {StackPtr stack}
%parse-param {char (*type)[4]}

%%
program             : { printf("#include <stdio.h>\n#include <malloc.h>\n\nint main()\n"); }  block   { codegen_free(table); return 0; }

block               : BEGIN_KWD { tab_print(1); printf("{\n"); } statement_list END { tab_print(-1); printf("}\n"); }

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

assignment          : variable_declared ASSIGN expression { codegen_assign(stack); }
                    ;

conditional         : IF_COND cond IF_BLOCK { codegen_if(stack); } block
                    ;

loop                : LOOP_COND cond LOOP_BLOCK { codegen_while(stack); } block
                    ;

print               : PRINT expression_list { codegen_print(stack); }
                    ;

variable_list       : variable_declare 
                    | variable_declare COMMA variable_list
                    ;

expression_list     : expression { codegen_exp(stack); expListCount++; }
                    | expression COMMA { codegen_exp(stack); expListCount++; } expression_list
                    ;

variable_declare    : IDENTIFIER { codegen_declare(table, stack, type); }
                    ;

variable_declared   : IDENTIFIER { assert_var_status(table, true); push(stack); }
                    ;

expression          : expression OP { push(stack); } expression { codegen_arithmetic(stack); }
                    /*TODO| expression DOT_OP { push(); } expression { codegen_dotproduct(); }*/
                    | PAR_BEGIN { push(stack); } expression PAR_END { push(stack); codegen_arithmetic(stack); }
                    | variable_declared
                    | number
                    ;       

cond                : expression REL_OP { push(stack); } expression { codegen_arithmetic(stack); }
                    ;
number              : INT_VAL { push(stack); }
                    | const_arr
                    ;
const_arr           : CONST_ARR_BEGIN CONST_ARR_END
                    | CONST_ARR_BEGIN expression_list CONST_ARR_END
                    ;
%%

int main(void) {
    VariableTable table;
    Stack stack;
    char type[TYPE_LEN];

    table.size = 0;
    stack.top = 0;
    return yyparse(&table, &stack, &type);
}
void yyerror(VariableTablePtr table, StackPtr stack, char (*type)[TYPE_LEN], char* s) {
	fprintf(stderr, "error: %s\n", s);
}
void error(char* s) {
    yyerror(NULL, NULL, NULL, s);
}
/* SYMBOL TABLE */
//TODO
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
//TODO
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

VariablePtr findVar(VariableTablePtr table, char variableName[TOKEN_LEN]) {
    for(int i = 0; i < table->size; i++) {
        if (strcmp(table->table[i].id, variableName) == 0) {
            return &(table->table[i]);
        }
    }
    return NULL;
}
//TODO
TokenType getType(VariableTablePtr table, char token[TOKEN_LEN]) {
    if (isInteger(token)) {
        return INTEGER;
    } else if (isConstArray(token)) {
        return ARRAY;
    } else {
        VariablePtr variable = findVar(table, token);
        if(variable) {
            return strcmp(variable->type, "arr") == 0 ? ARRAY : INTEGER;
        } else {
            error("Variable wasn\'t found");
		    exit(1);
        }
    }
}

void assert_var_status(VariableTablePtr table, bool req_status) {
    if(!findVar(table, yytext) != !req_status) {
        char errorMsg[TOKEN_LEN] = "Variable ";
        error(strcat(strcat(errorMsg, yytext), (req_status ? " not declared" : " already declared.")));
		exit(1);
    }
}

void declare(VariableTablePtr table, char (*type)[4]) {
    assert_var_status(table, false);
    
    // add var to table
    strcpy(table->table[table->size].id, yytext);
    strcpy(table->table[table->size].type, *type);
    table->table[table->size].arr_size = 0;
    table->size++;
}

/* STACK */
//TODO
void push(StackPtr stack) {
    strcpy(stack->st[++stack->top], yytext);
}

/* CODE GENERATORS */
//TODO
void codegen_declare(VariableTablePtr table, StackPtr stack, char (*type)[TYPE_LEN]) {
    declare(table, type);
    tab_print(0);
    if (strcmp(*type, "arr") == 0) {
        printf("int* %s = NULL;\n", yytext);  // arr x;
    } else {
        printf("int %s;\n", yytext);  // int x;
    }
}
//TODO
void codegen_assign(StackPtr stack) {
    tab_print(0);
    printf("%s = %s;\n", stack->st[stack->top-1], stack->st[stack->top]);    // x = 5;
    stack->top -= 2;
}
//TODO
void codegen_arithmetic(StackPtr stack) {
    char expVal[TOKEN_LEN];
    sprintf(expVal, "%s %s %s", stack->st[stack->top-2], stack->st[stack->top-1], stack->st[stack->top]);
    stack->top -= 2;
    strcpy(stack->st[stack->top], expVal);
}
//TODO
void codegen_exp(StackPtr stack) {
    char expVal[TOKEN_LEN];
    if(expListCount) {
        sprintf(expVal, "%s, %s", stack->st[stack->top - 1], stack->st[stack->top]);
    } else {
        sprintf(expVal, "%s", stack->st[stack->top]);
    }
    strcpy(stack->st[--stack->top], expVal);
}
//TODO
void codegen_print(StackPtr stack) {
    if(expListCount == 0) {
        error("can\'t print nothing");
    }
    tab_print(0);
    printf("printf(\"%c%c", '%', 'd');
    for(int i = 1; i < expListCount; i++) {
        printf(", %c%c", '%', 'd');
    }
    printf("\", %s);\n", stack->st[stack->top--]);
    expListCount = 0;
}

void codegen_if(StackPtr stack) {
    tab_print(0);
    printf("if(%s)\n", stack->st[stack->top--]);
}

void codegen_while(StackPtr stack) {
    tab_print(0);
    printf("while(%s)\n", stack->st[stack->top--]);
}

void codegen_free(VariableTablePtr table) {
    for(int i=0; i<table->size; i++) {
        if (strcmp(table->table[i].type, "arr")==0 && table->table[i].arr_size > 0) {
            printf("\tfree(%s);\n", table->table[i].id);   // free(x)
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
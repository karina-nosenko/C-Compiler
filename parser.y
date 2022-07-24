%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdbool.h>
    #include "symbol_table.h"
    #include "stack.h"

    #define TYPE_LEN 4
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
    void combine_numbers();
    void gen_empty_arr();
    void gen_const_arr();
    void begin_program();
    void begin_block();
    void end_block();
    void end_program();
    void codegen_declare(char (*type)[TYPE_LEN], char var_name[TOKEN_LEN]);
    void codegen_assign();
    void codegen_expList();
    void codegen_print();
    void codegen_arithmetic();
    void codegen_dotproduct();
    void codegen_const_arr();
    void codegen_if();
    void codegen_while();
    void codegen_index();
    void codegen_free();
    void tab_print(int a);
    
    extern char *yytext;

    int expListCount = 0;
    int lts = 0;
    int ls_last = 0;
    FILE *fp;
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
program             : BEGIN_KWD { begin_program(); } statement_list END { end_program(); return 0; }
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

conditional         : IF_COND PAR_BEGIN cond PAR_END IF_BLOCK { codegen_if(); } block
                    ;

loop                : LOOP_COND PAR_BEGIN cond PAR_END LOOP_BLOCK { codegen_while(); } block
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
                    | expression DOT_OP expression { codegen_dotproduct(); }
                    | PAR_BEGIN { push(NULL, yytext, OPERATOR); } expression PAR_END { push(NULL, yytext, OPERATOR); codegen_arithmetic(); }
                    | variable_declared
                    | const_arr { codegen_const_arr(); }
                    | number
                    | variable_declared INDEX number { codegen_index(); }
                    ;      

cond                : expression REL_OP { push(NULL, yytext, REL_OPERATOR); } expression { codegen_arithmetic(); }
                    ;

number              : INT_VAL { push(NULL, yytext, INT); }
                    ;
numbers             : number
                    | number COMMA numbers { combine_numbers(); }
                    ;

const_arr           : CONST_ARR_BEGIN CONST_ARR_END { gen_empty_arr(); }
                    | CONST_ARR_BEGIN numbers CONST_ARR_END { gen_const_arr(); }
                    ;
%%

int main(void) {
    Table table;
    Stack stack;
    char type[TYPE_LEN];

    fp = fopen("output.c", "w");

    table.size = 0;
    insert(&table, (Variable){0});
    get(&table, NULL, NULL, 0);
    update(&table, NULL, 0);
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
    int elementCount = 0;
    bool began = false;
    while(strtok(((!began) ? array : NULL), ", []{}")) {
        began = true;
        elementCount++;
    }
    return elementCount;
}

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

void combine_numbers() {
    char expVal[TOKEN_LEN];
    StackMember m1, m2;
    pop(NULL, &m2);
    pop(NULL, &m1);
    sprintf(expVal, "%s, %s", m1.token, m2.token);
    push(NULL, expVal, INT);
}

void gen_empty_arr() {
    char expVal[TOKEN_LEN];
    sprintf(expVal, "[]");
    push(NULL, expVal, ARR);
}

void gen_const_arr() {
    char expVal[TOKEN_LEN];
    StackMember m;
    pop(NULL, &m);
    sprintf(expVal, "[%s]", m.token);
    push(NULL, expVal, ARR);
}

void declare(char (*type)[4], char var_name[TOKEN_LEN]) {
    Variable var;
    bool isInt = strcmp(*type, "int") == 0;
    
    assert_var_status(var_name, false);

    strcpy(var.id, var_name);
    var.type = isInt;
    var.arr_size = isInt;

    insert(NULL, var);
}

/* CODE GENERATORS */

void begin_program() {
    fprintf(fp, "#include <stdio.h>\n");
    fprintf(fp, "#include <malloc.h>\n");
    fprintf(fp, "#include <string.h>\n\n");
    
    tab_print(1);
    fprintf(fp, "int add_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {\n");
    tab_print(0);
    fprintf(fp, "int i, min, max;\n");
    tab_print(0);
    fprintf(fp, "min = (len1 < len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "max = (len1 > len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "*total = malloc(sizeof(int) * max);\n");
    tab_print(1);
    fprintf(fp, "for(i = 0; i < min; i++) {\n");  
    tab_print(0);
    fprintf(fp, "(*total)[i] = arr1[i] + arr2[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = pMax[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
    fprintf(fp, "return max;\n");
    tab_print(-1);
    fprintf(fp, "}\n\n");

    tab_print(1);
    fprintf(fp, "int sub_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {\n");
    tab_print(0);
    fprintf(fp, "int i, min, max;\n");
    tab_print(0);
    fprintf(fp, "min = (len1 < len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "max = (len1 > len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "*total = malloc(sizeof(int) * max);\n");
    tab_print(1);
    fprintf(fp, "for(i = 0; i < min; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = arr1[i] - arr2[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = pMax[i] * ((len1 > len2) ? 1 : -1);\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
    fprintf(fp, "return max;\n");
    tab_print(-1);
    fprintf(fp, "}\n\n");

    tab_print(1);
    fprintf(fp, "int mul_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {\n");
    tab_print(0);
    fprintf(fp, "int i, min, max;\n");
    tab_print(0);
    fprintf(fp, "min = (len1 < len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "max = (len1 > len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "*total = malloc(sizeof(int) * max);\n");
    tab_print(1);
    fprintf(fp, "for(i = 0; i < min; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = arr1[i] * arr2[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "for(;i < max; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = 0;\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
    fprintf(fp, "return max;\n");
    tab_print(-1);
    fprintf(fp, "}\n\n");

    tab_print(1);
    fprintf(fp, "int div_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {\n");
    tab_print(0);
    fprintf(fp, "int i, min, max;\n");
    tab_print(0);
    fprintf(fp, "min = (len1 < len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "max = (len1 > len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "*total = malloc(sizeof(int) * max);\n");
    tab_print(1);
    fprintf(fp, "for(i = 0; i < min; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = arr1[i] / arr2[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {\n");
    tab_print(1);
    fprintf(fp, "if(len1 > len2) {\n");
    tab_print(0);
    fprintf(fp, "fprintf(stderr, \"Division by zero: longer array divided by a shorter\\n\");\n");
    tab_print(0);
    fprintf(fp, "exit(1);\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "else {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = 0 / pMax[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
    fprintf(fp, "return max;\n");
    tab_print(-1);
    fprintf(fp, "}\n\n");
    
    tab_print(1);
    fprintf(fp, "int dot_product_arrays(int *arr1, int len1, int *arr2, int len2) {\n");
	tab_print(0);
    fprintf(fp, "int sum = 0;\n");
	tab_print(1);
    fprintf(fp, "for(int i = 0; i < ((len1 < len2) ? len1 : len2); i++) {\n");
	tab_print(0);
    fprintf(fp, "sum += arr1[i] * arr2[i];\n");
	tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
	fprintf(fp, "return sum;\n");
    tab_print(-1);
    fprintf(fp, "}\n");

    fprintf(fp, "\n");
    tab_print(1);
    fprintf(fp, "int main() {\n");
    tab_print(0);
    fprintf(fp, "int **ts = NULL;\n");
    tab_print(0);
    fprintf(fp, "int *ls = NULL;\n");
    tab_print(0);
    fprintf(fp, "int lts = 0;\n\n");
}

void begin_block() {
    tab_print(1);
    fprintf(fp, "{\n"); 
}

void end_block() {
    
    tab_print(-1);
    fprintf(fp, "}\n");
}

void end_program() {
    fprintf(fp, "\n");
    codegen_free();
    tab_print(-1);
    fprintf(fp, "}\n");
}

void codegen_declare(char (*type)[TYPE_LEN], char var_name[TOKEN_LEN]) {
    // add variable to variable table
    declare(type, var_name);

    // print variable to output
    tab_print(0);
    if (strcmp(*type, "arr") == 0) {
        fprintf(fp, "int* %s = NULL;\n", yytext);
    } else {
        fprintf(fp, "int %s;\n", yytext);
    }
}

void codegen_assign() {
    StackMember var_name, exp;
    pop(NULL, &exp);
    pop(NULL, &var_name);
    if(var_name.type == INT) {
        tab_print(0);
        fprintf(fp, "%s = %s;\n", var_name.token, exp.token);
    } else {
        tab_print(0);
        fprintf(fp, "%s = realloc(%s, sizeof(int) * ls[lts - 1]);\n", var_name.token, var_name.token);
        tab_print(1);
        fprintf(fp, "for(int i = 0; i < ls[lts - 1]; i++) {\n");
        tab_print(0);
        fprintf(fp, "%s[i] = ts[lts - 1][i];\n", var_name.token);
        tab_print(-1);
        fprintf(fp, "}\n");
        update(NULL, var_name.token, ls_last);
    }
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
            fprintf(fp, "lts++;\n");
            tab_print(0);
            fprintf(fp, "ts = realloc(ts, sizeof(int*) * lts);\n");
            tab_print(0);
            fprintf(fp, "ls = realloc(ls, sizeof(int) * lts);\n");
            tab_print(0);
            fprintf(fp, "ls[lts - 1] = 1;\n");
            tab_print(0);
            fprintf(fp, "ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);\n");
            tab_print(0);
            fprintf(fp, "ts[lts - 1][0] = %s %s %s;\n", m1.token, m2.token, m3.token);
            sprintf(expVal, "ts[lts - 1][0]");
            lts++;
        }
        push(NULL, expVal, INT);
        break;
    case ARR:
        int l1, l3;
        switch(m2.token[0]) {
            case '+':
                strcpy(m2.token, "add");
                break;
            case '-':
                strcpy(m2.token, "sub");
                break;
            case '*':
                strcpy(m2.token, "mul");
                break;
            case '/':
                strcpy(m2.token, "div");
                break;
        }
        if(isConstArray(m1.token)) {
            l1 = getConstArrSize(m1.token);
            push(NULL, m1.token, m1.type);
            codegen_const_arr();
            pop(NULL, &m1);
        } else {
            Variable var;
            get(NULL, &var, m1.token, 0);
            l1 = var.arr_size;
        }
        if(isConstArray(m3.token)) {
            l3 = getConstArrSize(m3.token);
            push(NULL, m3.token, m3.type);
            codegen_const_arr();
            pop(NULL, &m3);
        } else {
            Variable var;
            get(NULL, &var, m3.token, 0);
            l3 = var.arr_size;
        }
        tab_print(0);
        fprintf(fp, "lts++;\n");
        tab_print(0);
        fprintf(fp, "ts = realloc(ts, sizeof(int*) * lts);\n");
        tab_print(0);
        fprintf(fp, "ls = realloc(ls, sizeof(int) * lts);\n");
        tab_print(0);
        fprintf(fp, "ls[lts - 1] = %s_arrays(%s, %d, %s, %d, &(ts[lts - 1]));", m2.token, m1.token, l1, m3.token, l3);
        ls_last = ((l1 > l3) ? l1 : l3);
        Variable var;
        sprintf(var.id, "ts[%d]", lts);
        var.type = ARRAY;
        var.arr_size = ls_last;
        insert(NULL, var);
        sprintf(expVal, "ts[%d]", lts++);
        push(NULL, expVal, INT);
        break;
    case OPERATOR:
        push(NULL, m2.token, m2.type);
        break;
    }
}

void codegen_dotproduct() {
    StackMember m1, m3;
    int l1 = 0, l3 = 0;
    char expVal[TOKEN_LEN];

    pop(NULL, &m3);
    pop(NULL, &m1);
    
    if((m1.type != m3.type) || (m1.type != ARR)) {
        error("Type Mismatch.");
        exit(1);
    }
    if(isConstArray(m1.token)) {
        l1 = getConstArrSize(m1.token);
        push(NULL, m1.token, m1.type);
        codegen_const_arr();
        pop(NULL, &m1);
    } else {
        Variable var;
        get(NULL, &var, m1.token, 0);
        l1 = var.arr_size;
    }
    if(isConstArray(m3.token)) {
        fprintf(stderr, "m3 const\n");
        l3 = getConstArrSize(m3.token);
        push(NULL, m3.token, m3.type);
        codegen_const_arr();
        pop(NULL, &m3);
    } else {
        Variable var;
        get(NULL, &var, m3.token, 0);
        l3 = var.arr_size;
    }
    tab_print(0);
    fprintf(fp, "lts++;\n");
    tab_print(0);
    fprintf(fp, "ts = realloc(ts, sizeof(int*) * lts);\n");
    tab_print(0);
    fprintf(fp, "ls = realloc(ls, sizeof(int) * lts);\n");
    tab_print(0);
    fprintf(fp, "ls[lts - 1] = 1;\n");
    tab_print(0);
    fprintf(fp, "ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);\n");
    tab_print(0);
    fprintf(fp, "*ts[lts - 1] = dot_product_arrays(%s, %d, %s, %d);\n", m1.token, l1, m3.token, l3);
    Variable var;
    sprintf(var.id, "ts[%d]", lts);
    var.type = INTEGER;
    ls_last = var.arr_size = 1;
    insert(NULL, var);
    sprintf(expVal, "*ts[%d]", lts++);
    push(NULL, expVal, INT);
}

void codegen_const_arr() {
    StackMember m;
    Variable var;
    pop(NULL, &m);

    char temp[TOKEN_LEN] = {0};
    strncpy(temp, m.token + 1, strlen(m.token) - 2);
    
    sprintf(var.id, "ts[%d]", lts);
    var.type = ARRAY;
    ls_last = var.arr_size = getConstArrSize(m.token);
    insert(NULL, var);

    tab_print(0);
    fprintf(fp, "lts++;\n");
    tab_print(0);
    fprintf(fp, "ts = realloc(ts, sizeof(int*) * lts);\n");
    tab_print(0);
    fprintf(fp, "ls = realloc(ls, sizeof(int) * lts);\n");
    tab_print(0);
    fprintf(fp, "ls[lts - 1] = %d;\n", var.arr_size);
    tab_print(0);
    fprintf(fp, "ts[lts - 1] = malloc(sizeof(int)*ls[lts-1]);\n");
    tab_print(0);
    fprintf(fp, "memcpy(ts[lts - 1], (int[]){%s}, sizeof(int) * ls[lts - 1]);\n", temp);
    sprintf(m.token, "ts[%d]", lts++);

    push(NULL, m.token, m.type);
}

void codegen_expList() {
    char expVal[TOKEN_LEN];
    if(expListCount) {
        StackMember exp1, exp2;
        pop(NULL, &exp2);
        pop(NULL, &exp1);
        // if(exp2.type == ARR) {
        //     error("can\'t print array like this, please use a loop.");
        //     exit(1);
        // }
        sprintf(expVal, "%s, %s", exp1.token, exp2.token);
    } else {
        StackMember exp;
        pop(NULL, &exp);
        // if(exp.type == ARR) {
        //     error("can\'t print array like this, please use a loop.");
        //     exit(1);
        // }
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
    fprintf(fp, "printf(\"%c%c", '%', 'd');
    for(int i = 1; i < expListCount; i++) {
        fprintf(fp, ", %c%c", '%', 'd');
    }

    fprintf(fp, "\\n\", %s);\n", expList.token);
    expListCount = 0;
}

void codegen_if() {
    StackMember cond;
    pop(NULL, &cond);
    tab_print(0);
    fprintf(fp, "if(%s)\n", cond.token);
}

void codegen_while() {
    StackMember cond;
    pop(NULL, &cond);
    tab_print(0);
    fprintf(fp, "while(%s)\n", cond.token);
}

void codegen_index() {
    StackMember index;
    StackMember var;
    pop(NULL, &index);
    pop(NULL, &var);

    fprintf(stderr, "index: %s\n", index.token);
    fprintf(stderr, "var: %s\n", index.token);

}

void codegen_free() {
    int tSize = size(NULL);
    Variable var;
    for(int i=0; i < tSize; i++) {
        get(NULL, &var, NULL, i);
        if ((var.type == ARRAY) && var.arr_size > 0) {
            tab_print(0);
            fprintf(fp, "free(%s);\n", var.id);   // free(x)
        }
    }
    tab_print(0);
    fprintf(fp, "free(ls);\n");
    tab_print(0);
    fprintf(fp, "free(ts);\n");
}

void tab_print(int a) {
    static int tabCount = 0;
    if(a < 0)
        tabCount += a;
    for(int i = 0; i < tabCount; i++)
        fprintf(fp, "\t");
    if(a > 0)
        tabCount += a;
}
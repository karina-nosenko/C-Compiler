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
    enum token_type { INTEGER, ARRAY };

    void yyerror(char* s);
    int yylex();
    void addSymbolToTable(char id[TOKEN_LEN], char type[TYPE_LEN], int arr_size);
    void setType();
    bool isInteger(char token[TOKEN_LEN]);
    bool isConstArray(char token[TOKEN_LEN]);
    int getConstArrSize(char array[TOKEN_LEN]);
    enum token_type getType(char token[TOKEN_LEN]);
    struct Table* findVar(char variableName[TOKEN_LEN]);
    bool isVarDeclared(char variableName[TOKEN_LEN]);
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
%token CONST_ARR
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
                    | CONST_ARR { push(); }
                    ;       

type                : INT                                       
                    | ARR
                    ;
%%
int label[LABEL_LEN];

struct Table
{
	char id[TOKEN_LEN];
	char type[TYPE_LEN];
    int arr_size;   // size of the array if the type is arr
} table[TABLE_SIZE];
int tableCurrentIndex = 0;
char type[TYPE_LEN];

char st[STACK_SIZE][TOKEN_LEN];
int top=0;

// for temporary variable names
char temp[TOKEN_LEN]="t";
int token_index = 0;

int main(void) {
    return yyparse();
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}

/* SYMBOL TABLE */

void addSymbolToTable(char id[TOKEN_LEN], char type[TYPE_LEN], int arr_size) {
    strcpy(table[tableCurrentIndex].id, id);
    strcpy(table[tableCurrentIndex].type, type);
    table[tableCurrentIndex].arr_size = arr_size;
    tableCurrentIndex++;
}

void setType() {
	strcpy(type,yytext);
}

bool isInteger(char token[TOKEN_LEN]) {
    for(int i=0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

bool isConstArray(char token[TOKEN_LEN]) {
    int size = 0;
    for(int i=0; i<TOKEN_LEN && token[i] != '\0'; i++) {
        size++;
    }

    if (token[0] == '[' && token[size-1] == ']') {
        return true;
    }
    return false;
}

int getConstArrSize(char array[TOKEN_LEN]) {
    bool empty = true;
    bool oneElement = true;
    int numOfCommas = 0;
    for(int i=1; i<TOKEN_LEN && array[i]!='\0' && array[i]!=']'; i++) {
        if (isdigit(array[i])) {
            empty = false;
        }
        if (array[i] == ',') {
            oneElement = false;
            numOfCommas++;
        }
    }

    if (empty) {
        return 0;
    } else if (oneElement) {
        return 1;
    } else {
        return numOfCommas + 1;
    }
}

enum token_type getType(char token[TOKEN_LEN]) {
    if (isInteger(token)) {
        return INTEGER;
    } else if (isConstArray(token)) {
        return ARRAY;
    } else {
        struct Table* variable = findVar(token);
        if(variable) {
            return strcmp(variable->type, "arr") == 0 ? ARRAY : INTEGER;
        } else {
            yyerror("Unknown type.");
		    exit(0);
        }
    }
}

struct Table* findVar(char variableName[TOKEN_LEN]) {
    for(int i=0; i<tableCurrentIndex; i++) {
        if (strcmp(table[i].id, variableName) == 0) {
            return &table[i];
        }
    }
    return NULL;
}

bool isVarDeclared(char variableName[TOKEN_LEN]) {
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
    char variableName[TOKEN_LEN];
    strcpy(variableName, yytext);

    if (isVarDeclared(variableName)) {
        yyerror("Multiple variable name declarations");
        exit(0);
    }

    addSymbolToTable(variableName, type, 0);
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
    sprintf(temp, "t%d", token_index++);

    char left[TOKEN_LEN];
    char right[TOKEN_LEN];
    char operator[5];
    strcpy(left, st[top-2]);
    strcpy(right, st[top]);
    strcpy(operator, st[top-1]);

    enum token_type leftType = getType(left);
    enum token_type rightType = getType(right);

    if (leftType == rightType == INTEGER) {
        addSymbolToTable(temp, "int", 0);
        printf("\tint %s = %s %s %s;\n", temp, left, operator, right);   // int t1 = 5 + 4
    } else if (leftType == rightType == ARRAY) { 
        int resultSize = 0;
        int leftSize = 0, rightSize = 0;

        leftSize = isConstArray(left) ? getConstArrSize(left) : findVar(left)->arr_size;
        rightSize = isConstArray(right) ? getConstArrSize(right) : findVar(right)->arr_size;
        resultSize = leftSize > rightSize ? leftSize : rightSize;

        addSymbolToTable(temp, "arr", resultSize);

        // i need to add here assignments of the t to things...
        if (leftSize > rightSize) {
            printf("\t%s = (int*)calloc(%d, sizeof(int));\n", right, resultSize);
        } else if (leftSize < rightSize) {
            printf("\t%s = (int*)calloc(%d, sizeof(int));\n", left, resultSize);
        }

        printf("\tint* %s = (int*)malloc(sizeof(int) * %d);\n", temp, resultSize);
        printf("\tfor(int i=0; i<%d; i++) {\n", resultSize);
        printf("\t\t%s[i] = %s[i] %s %s[i];\n\t}\n", temp, left, operator, right);
    } else {
        yyerror("Incompatible data types.");
        exit(0);
    }
 
    top -=2;
    strcpy(st[top], temp);
}

void codegen_relop() {
    sprintf(temp, "t%d", token_index++);
    enum token_type leftType = getType(st[top-2]);
    enum token_type rightType = getType(st[top]);

    if (leftType == rightType == INTEGER) {
        strcpy(table[tableCurrentIndex].id, temp);
        strcpy(table[tableCurrentIndex].type, "int");

        printf("\tint %s = %s %s %s;\n", temp, st[top-2], st[top-1], st[top]);   // int t1 = 5 < 4
    } else {
        yyerror("Incompatible data types.");
        exit(0);
    }

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
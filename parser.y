%{
    void yyerror(char* s);
    int yylex();

    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>

    int tcounter = 0, ecounter = 0;
%}

%union { int num; char id; }
%start program
%token BEGIN_KWD END INT ARR
%token <num> NUMBER
%token <id> IDENTIFIER
%type <id> block
%type <num> statement_list statement declarator expression term
%type <num> int_assignment_list arr_assignment_list int_assignment arr_assignment


%%
program             : { printf("#include <stdio.h>\n#include <stdlib.h>\nint main() {\n"); }  block   { printf("}"); return 0; }

block               : BEGIN_KWD { printf("{\n"); } statement_list END { ecounter = tcounter = 0; printf("}\n"); }

statement_list      : /* empty */                               { }
                    | statement_list statement                  { }
                    ;       

statement           : declarator ';'                            { }                 
                    | int_assignment ';'                        { }   
                    | arr_assignment ';'                        { }               
                    ;       

declarator          : INT int_assignment_list                   { }
                    | ARR arr_assignment_list                   { }
                    ;

int_assignment_list : int_assignment                            { }
                    | int_assignment_list ',' int_assignment    { }
                    ;

arr_assignment_list : arr_assignment                            { }
                    | arr_assignment_list ',' arr_assignment    { }
                    ;

int_assignment      : IDENTIFIER '=' expression                 { printf("int %c = e%d;\n", $1, $3); }
                    | IDENTIFIER                                { printf("int %c;\n", $1); }
                    ;           

arr_assignment      : IDENTIFIER '=' expression                 { printf("int* %c = (int*)malloc(sizeof(int)*256);\n%c[0] = e%d;\n", $1, $1, $3); }
                    | IDENTIFIER                                { printf("int* %c;\n", $1); }
                    ;       

expression          : term                                      { $$ = ++ecounter; printf("int e%d = t%d;\n", ecounter, $1); }
                    | expression '+' term                       { $$ = ++ecounter; printf("int e%d = e%d + t%d;\n", ecounter, $1, $3); }
                    | expression '-' term                       { $$ = ++ecounter; printf("int e%d = e%d - t%d;\n", ecounter, $1, $3); }
                    | expression '*' term                       { $$ = ++ecounter; printf("int e%d = e%d - t%d;\n", ecounter, $1, $3); }
                    | expression '/' term                       { $$ = ++ecounter; printf("int e%d = e%d - t%d;\n", ecounter, $1, $3); }
                    ;       

term                : NUMBER                                    { $$ = ++tcounter; printf("int t%d = %d;\n", tcounter, $1); }
                    | IDENTIFIER                                { $$ = ++tcounter; printf("int e%d = %d;\n", tcounter, $1); }
                    ;

%%
char st[1000][10];
int top=0;
int i=0;
char temp[2]="t";
int label[200];

struct Table
{
	char id[20];
	char type[10];
} table[10000];


int main(void) {
    return yyparse();
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}
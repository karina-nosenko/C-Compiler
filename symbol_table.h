#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define TOKEN_LEN 100
#define TABLE_SIZE 10000

typedef enum token_type{
    ARRAY = 0,
    INTEGER = 1
} TokenType;

typedef struct variable{
    char id[TOKEN_LEN];
    TokenType type;
    int arr_size;   // size of the array if the type is arr
} Variable, *VariablePtr;

typedef struct {
    Variable data[TABLE_SIZE];
    int size;
} Table, *TablePtr;

void insert(TablePtr table, Variable var);
void get(TablePtr table, VariablePtr var, char id[TOKEN_LEN], int inx);
int find(TablePtr table, char id[TOKEN_LEN]);
int size(TablePtr table);
#endif // SYMBOL_TABLE_H
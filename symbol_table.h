#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define TOKEN_LEN 100000
#define TABLE_SIZE 10000

typedef enum token_type{
    ARRAY = 0,
    INTEGER = 1
} TokenType;

typedef struct variable{
    char id[TOKEN_LEN];
    TokenType type;
    char arr_size[TOKEN_LEN];   // size of the array if the type is arr
} Variable, *VariablePtr;

typedef struct {
    Variable data[TABLE_SIZE];
    int size;
} Table, *TablePtr;

void insert(TablePtr table, Variable var);
void get(TablePtr table, VariablePtr var, char id[TOKEN_LEN], int inx);
void update(TablePtr table, char id[TOKEN_LEN], char new_size[TOKEN_LEN]);
int find(TablePtr table, char id[TOKEN_LEN]);
int size(TablePtr table);
#endif // SYMBOL_TABLE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol_table.h"

void error(char* s);

int find(TablePtr table, char id[TOKEN_LEN]) {
    static TablePtr tablePtr = NULL;

    if(table) {
        tablePtr = table;
    } else {
        for(int i = 0; i < tablePtr->size; i++) {
            if(!strcmp(tablePtr->data[i].id, id)) {
                return i;
            }
        }
    }
    return -1;
}

int size(TablePtr table) {
    static TablePtr tablePtr = NULL;

    if(table) {
        tablePtr = table;
    }
    return tablePtr->size;
}

void insert(TablePtr table, Variable var) {
    // static TablePtr tablePtr = NULL;

    // if(table) {
    //     tablePtr = table;
    // } else {
    //     if(find(NULL, var.id) >= 0) {
    //         char errorMsg[TOKEN_LEN];
    //         sprintf(errorMsg, "Variable %s already declared.\n", var.id);
    //         error(errorMsg);
    //         exit(1);
    //     }
    //     if(tablePtr->size == TABLE_SIZE) {
    //         error("table full.");
    //         exit(1);
    //     }
    //     strcpy(tablePtr->data[tablePtr->size].id, var.id);
    //     tablePtr->data[tablePtr->size].type = var.type;
    //     strcpy(tablePtr->data[tablePtr->size].arr_size, var.arr_size);
    //     tablePtr->size++;
    // }
}

void get(TablePtr table, VariablePtr var, char id[TOKEN_LEN], int inx) {
    // static TablePtr tablePtr = NULL;

    // if(table) {
    //     tablePtr = table;
    // } else if(!id) {
    //     if(inx > tablePtr->size) {
    //         char errorMsg[TOKEN_LEN];
    //         sprintf(errorMsg, "index %d out of bounds", inx);
    //         error(errorMsg);
    //         exit(1);
    //     }
    //     strcpy(var->id, tablePtr->data[inx].id);
    //     var->type = tablePtr->data[inx].type;
    //     strcpy(var->arr_size, tablePtr->data[inx].arr_size);
    // } else {
    //     int index = find(NULL, id);
    //     if(index < 0) {
    //         char errorMsg[TOKEN_LEN];
    //         sprintf(errorMsg, "Variable %s not declared.\n", id);
    //         error(errorMsg);
    //         exit(1);
    //     }
    //     strcpy(var->id, tablePtr->data[index].id);
    //     var->type = tablePtr->data[index].type;
    //     strcpy(var->arr_size, tablePtr->data[index].arr_size);
    // }
}

void update(TablePtr table, char id[TOKEN_LEN], char new_size[TOKEN_LEN]) {
    static TablePtr tablePtr = NULL;

    if(table) {
        tablePtr = table;
    } else {
        int inx = find(NULL, id);
        if(inx < 0) {
            char errorMsg[TOKEN_LEN];
            sprintf(errorMsg, "Variable %s not declared.\n", id);
            error(errorMsg);
            exit(1);
        }
        strcpy(tablePtr->data[inx].arr_size, new_size);
    }
}
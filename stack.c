#include <string.h>
#include <stdlib.h>
#include "stack.h"

void error(char* s);

void push(StackPtr stack, char token[TOKEN_LEN], StackMemberType type) {
    static StackPtr stackPtr = NULL;
    
    if(stack) {
        stackPtr = stack;
    } else {
        if (stackPtr->top == STACK_SIZE) {
            error("stack full.");
            exit(1);
        }
        stackPtr->top++;
        strcpy(stackPtr->st[stackPtr->top].token, token);
        stackPtr->st[stackPtr->top].type = type;
    }
}

void pop(StackPtr stack, StackMemberPtr member) {
    static StackPtr stackPtr = NULL;
    
    if(stack) {
        stackPtr = stack;
    } else {
        if (stackPtr->top < 0) {
            error("stack empty.");
            exit(1);
        }
        strcpy(member->token, stackPtr->st[stackPtr->top].token);
        member->type = stackPtr->st[stackPtr->top].type;
        stackPtr->top--;
    }
}
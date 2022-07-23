#ifndef STACK_H
#define STACK_H

#define TOKEN_LEN 100
#define STACK_SIZE 1000
typedef enum stack_member_type{
    ARR = 0,
    INT = 1,
    OPERATOR = 2,
    REL_OPERATOR = 3,
    EXP_LIST = 4
} StackMemberType;

typedef struct stack_member{
    char token[TOKEN_LEN];
    StackMemberType type;
} StackMember, *StackMemberPtr;

typedef struct stack{
    StackMember st[STACK_SIZE];
    int top;
} Stack, *StackPtr;

void push(StackPtr stack, char token[TOKEN_LEN], StackMemberType type);
void pop(StackPtr stack, StackMemberPtr member);
#endif //STACK_H
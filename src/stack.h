#ifndef STACK_H
#define STACK_H

#include "token.h"

typedef struct {
    Token* data;
    int top;
    int n_max;
} TokenStack;

TokenStack* create_stack(int n_max);
int is_stack_empty(TokenStack* stack);
void free_stack(TokenStack* stack);
int push_in_stack(TokenStack* stack, Token t);
Token unpush_from_stack(TokenStack* stack);
Token pick_from_stack(TokenStack* stack);

#endif

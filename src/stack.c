#include "stack.h"

#include <stdlib.h>

TokenStack* create_stack(int n_max) {
    TokenStack* result = NULL;
    TokenStack* stack = malloc(sizeof(TokenStack));

    if (stack == NULL) {
        return result;
    }

    stack->data = malloc(sizeof(Token) * n_max);

    if (stack->data == NULL) {
        free(stack);
        return result;
    }

    stack->top = -1;
    stack->n_max = n_max;
    result = stack;

    return result;
}

int is_stack_empty(TokenStack* stack) {
    int result = 0;

    if (stack == NULL || stack->top == -1) {
        result = 1;
    }

    return result;
}

void free_stack(TokenStack* stack) {
    if (stack != NULL) {
        if (stack->data != NULL) {
            free(stack->data);
        }

        free(stack);
    }
}

int push_in_stack(TokenStack* stack, Token t) {
    int result = 0;

    if (stack == NULL) {
        result = 1;
    } else {
        if (stack->top + 1 >= stack->n_max) {
            int new_n_max = stack->n_max * 2;
            Token* new_data = realloc(stack->data, new_n_max * sizeof(Token));

            if (new_data == NULL) {
                result = 1;
            } else {
                stack->data = new_data;
                stack->n_max = new_n_max;
            }
        }

        if (result == 0) {
            stack->top++;
            stack->data[stack->top] = t;
        }
    }

    return result;
}

Token unpush_from_stack(TokenStack* stack) {
    Token result;

    if (stack == NULL || stack->top == -1) {
        result.type = TOKEN_INVALID;
        result.value.op = 0;
    } else {
        result = stack->data[stack->top];
        stack->top--;
    }

    return result;
}

Token pick_from_stack(TokenStack* stack) {
    Token result;

    if (stack == NULL || stack->top == -1) {
        result.type = TOKEN_INVALID;
        result.value.op = 0;
    } else {
        result = stack->data[stack->top];
    }

    return result;
}

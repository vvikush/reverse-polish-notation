#include "shunting_yard.h"

#include "stack.h"

int is_operator(Token t) {
    int result = 0;

    if (t.type == TOKEN_OP) {
        if (t.value.op == '+' || t.value.op == '-' || t.value.op == '*' || t.value.op == '/' ||
            t.value.op == '^') {
            result = 1;
        }
    } else if (t.type == TOKEN_FUNC) {
        result = 1;
    }

    return result;
}

int op_priority(Token t) {
    int result = -1;

    if (t.type == TOKEN_OP) {
        if (t.value.op == '+' || t.value.op == '-') {
            result = 0;
        } else if (t.value.op == '*' || t.value.op == '/') {
            result = 1;
        } else if (t.value.op == '^') {
            result = 3;
        } else if (t.value.op == '(' || t.value.op == ')') {
            result = 4;
        }
    } else if (t.type == TOKEN_FUNC) {
        if (t.value.function == FUNC_SQRT) {
            result = 3;
        } else {
            result = 2;
        }
    }

    return result;
}

int is_open_bracket(Token t) {
    int result = 0;

    if (t.type == TOKEN_OP && t.value.op == '(') {
        result = 1;
    }

    return result;
}

int is_close_bracket(Token t) {
    int result = 0;

    if (t.type == TOKEN_OP && t.value.op == ')') {
        result = 1;
    }

    return result;
}

static int process_operators(TokenStack* stack, Token t, Token* output, int* output_position) {
    int can_pop = 1;

    while (is_stack_empty(stack) == 0 && can_pop) {
        Token top = pick_from_stack(stack);

        if (is_operator(top) == 1 && op_priority(top) >= op_priority(t)) {
            output[*output_position] = unpush_from_stack(stack);
            (*output_position)++;
        } else {
            can_pop = 0;
        }
    }

    return push_in_stack(stack, t);
}

static int process_close_bracket(TokenStack* stack, Token* output, int* output_position) {
    int found_open = 0;
    int continue_loop = 1;

    while (is_stack_empty(stack) == 0 && continue_loop) {
        Token top = pick_from_stack(stack);

        if (is_open_bracket(top) == 1) {
            unpush_from_stack(stack);
            found_open = 1;
            continue_loop = 0;
        } else {
            output[*output_position] = unpush_from_stack(stack);
            (*output_position)++;
        }
    }

    return found_open == 0;
}

int shunting_yard(const Token* input, int input_length, Token* output, int* output_length) {
    int result = 0;
    int output_position = 0;
    int i = 0;

    TokenStack* stack = create_stack(20);

    if (stack == NULL) {
        result = 1;
    }

    while (result == 0 && i < input_length) {
        Token t = input[i++];

        if (t.type == TOKEN_NUMBER) {
            output[output_position] = t;
            output_position++;
        } else if (is_operator(t) == 1) {
            result = process_operators(stack, t, output, &output_position);
        } else if (is_open_bracket(t) == 1) {
            result = push_in_stack(stack, t);
        } else if (is_close_bracket(t) == 1) {
            result = process_close_bracket(stack, output, &output_position);
        } else {
            result = 1;
        }
    }

    while (is_stack_empty(stack) == 0 && result == 0) {
        Token top = pick_from_stack(stack);

        if (is_open_bracket(top) == 1 || is_close_bracket(top) == 1) {
            result = 1;
            unpush_from_stack(stack);
        } else {
            output[output_position] = unpush_from_stack(stack);
            output_position++;
        }
    }

    free_stack(stack);
    *output_length = output_position;

    return result;
}

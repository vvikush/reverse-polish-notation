#include <math.h>
#include <stdlib.h>

#include "rpn.h"
#include "token.h"

static double handle_operation(char op, double a, double b) {
    double result = NAN;
    int valid = 1;

    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0.0) {
                valid = 0;
            } else {
                result = a / b;
            }
            break;
        case '^':
            result = pow(a, b);
            break;
        default:
            valid = 0;
    }

    return valid ? result : NAN;
}

static double handle_function(FuncType func, double x) {
    double result = NAN;
    int valid = 1;

    switch (func) {
        case FUNC_SIN:
            result = sin(x);
            break;
        case FUNC_COS:
            result = cos(x);
            break;
        case FUNC_TAN:
            result = tan(x);
            break;
        case FUNC_SQRT:
            if (x < 0) {
                valid = 0;
            } else {
                result = sqrt(x);
            }
            break;
        case FUNC_LN:
            if (x <= 0) {
                valid = 0;
            } else {
                result = log(x);
            }
            break;
        case FUNC_EXP:
            result = exp(x);
            break;
        case FUNC_FABS:
            result = fabs(x);
            break;
        default:
            valid = 0;
    }

    return valid ? result : NAN;
}

static int process_token(const Token t, double* stack, int* top) {
    int success = 1;

    switch (t.type) {
        case TOKEN_NUMBER:
            stack[++(*top)] = t.value.number;
            break;
        case TOKEN_OP:
            if (*top < 1) {
                success = 0;
            } else {
                double b = stack[(*top)--];
                double a = stack[(*top)--];
                double result = handle_operation(t.value.op, a, b);

                if (isnan(result)) {
                    success = 0;
                } else {
                    stack[++(*top)] = result;
                }
            }
            break;
        case TOKEN_FUNC:
            if (*top < 0) {
                success = 0;
            } else {
                double x = stack[(*top)--];
                double result = handle_function(t.value.function, x);

                if (isnan(result)) {
                    success = 0;
                } else {
                    stack[++(*top)] = result;
                }
            }
            break;
        default:
            success = 0;
    }

    return success;
}

double eval_rpn(const Token* tokens, int n) {
    int flag = 1;
    double result = 0.0;

    if (n == 0) {
        flag = 0;
    }

    if (flag) {
        double* stack = malloc(n * sizeof(double));

        if (!stack) {
            flag = 0;
        } else {
            int top = -1;
            int success = 1;

            for (int i = 0; i < n && success; i++) {
                success = process_token(tokens[i], stack, &top);
            }

            result = (success && top == 0) ? stack[top] : NAN;

            free(stack);
        }
    }

    if (flag) {
        return result;
    }

    return NAN;
}

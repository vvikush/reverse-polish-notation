#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer_and_check.h"
#include "rpn.h"
#include "shunting_yard.h"
#include "token.h"

#define WIDTH 80
#define HEIGHT 25
#define CENTER_Y 12

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Token* convert_to_token_array(char* tokens[], int num_tokens, int* token_array_length);

char* input_function() {
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    char* function = malloc(strlen(buffer) + 1);
    if (function == NULL) {
        return NULL;
    }

    strcpy(function, buffer);

    return function;
}

double result(double x, const char* expr) {
    char* tokens[50] = {NULL};
    int num_tokens = 0;
    double end = -20;

    for (int i = 0; i < 50; i++) {
        tokens[i] = NULL;
    }

    int result = lexer((char*)expr, tokens, &num_tokens, x);

    if (result) {
        int token_array_length = 0;
        Token* token_array = convert_to_token_array(tokens, num_tokens, &token_array_length);

        if (token_array) {
            Token output[100] = {0};
            int output_length = 0;

            int err = shunting_yard(token_array, token_array_length, output, &output_length);

            if (!err) {
                double eval_result = eval_rpn(output, output_length);
                if (!isnan(eval_result)) {
                    end = eval_result;
                }
            }

            free(token_array);
        }
    }

    for (int i = 0; i < num_tokens; i++) {
        if (tokens[i] != NULL) {
            free(tokens[i]);
        }
    }

    return end;
}

void draw_graph(const char* expr) {
    char field[HEIGHT][WIDTH];
    int row = 0, col;

    while (row < HEIGHT) {
        col = 0;
        while (col < WIDTH) {
            field[row][col++] = '.';
        }
        row++;
    }

    col = 0;
    int flag_2 = 0;

    while (col < WIDTH) {
        double x, y;

        x = (4.0 * M_PI * col) / (WIDTH - 1);
        y = result(x, expr);

        if (!(y < -1.0 || y > 1.0)) {
            row = CENTER_Y - (int)(round(y * (HEIGHT / 2.0 - 1)));

            if (row >= 0 && row < HEIGHT) {
                field[row][col] = '*';
                flag_2 = 1;
            }
        }

        col++;
    }

    row = 0;

    if (flag_2) {
        while (row < HEIGHT) {
            col = 0;
            while (col < WIDTH) {
                putchar(field[row][col++]);
            }
            putchar('\n');
            row++;
        }
    } else {
        printf("n/a");
    }
}

Token* convert_to_token_array(char* tokens[], int num_tokens, int* token_array_length) {
    Token* token_array = malloc(num_tokens * sizeof(Token));

    if (!token_array) {
        return NULL;
    }

    *token_array_length = num_tokens;

    for (int i = 0; i < num_tokens; i++) {
        if (is_digit(tokens[i][0]) || (tokens[i][0] == '-' && is_digit(tokens[i][1])) ||
            (tokens[i][0] == '.' && is_digit(tokens[i][1]))) {
            token_array[i].type = TOKEN_NUMBER;
            token_array[i].value.number = atof(tokens[i]);
        } else if (is_operator_1(tokens[i][0])) {
            token_array[i].type = TOKEN_OP;
            token_array[i].value.op = tokens[i][0];
        } else if (strcmp(tokens[i], "(") == 0 || strcmp(tokens[i], ")") == 0) {
            token_array[i].type = TOKEN_OP;
            token_array[i].value.op = tokens[i][0];
        } else if (is_func_or_x(tokens[i])) {
            if (strcmp(tokens[i], "x") != 0) {
                token_array[i].type = TOKEN_FUNC;

                if (strcmp(tokens[i], "sin") == 0) {
                    token_array[i].value.function = FUNC_SIN;
                } else if (strcmp(tokens[i], "cos") == 0) {
                    token_array[i].value.function = FUNC_COS;
                } else if (strcmp(tokens[i], "tan") == 0) {
                    token_array[i].value.function = FUNC_TAN;
                } else if (strcmp(tokens[i], "sqrt") == 0) {
                    token_array[i].value.function = FUNC_SQRT;
                } else if (strcmp(tokens[i], "ln") == 0) {
                    token_array[i].value.function = FUNC_LN;
                } else if (strcmp(tokens[i], "exp") == 0) {
                    token_array[i].value.function = FUNC_EXP;
                } else if (strcmp(tokens[i], "fabs") == 0) {
                    token_array[i].value.function = FUNC_FABS;
                }
            }
        }
    }

    return token_array;
}

int main() {
    char* expr = input_function();

    if (expr == NULL) {
        printf("n/a");
        return 1;
    }

    draw_graph(expr);
    free(expr);

    return 0;
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shunting_yard.h"
#include "token.h"

#define LEN_NUM 15

int is_operator_or_bracket(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')');
}

int is_operator_1(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }

int is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

int is_digit(char c) { return c >= '0' && c <= '9'; }

int is_func_or_x(const char* s) {
    return strcmp(s, "sin") == 0 || strcmp(s, "cos") == 0 || strcmp(s, "tan") == 0 ||
           strcmp(s, "sqrt") == 0 || strcmp(s, "ln") == 0 || strcmp(s, "exp") == 0 ||
           strcmp(s, "fabs") == 0 || strcmp(s, "x") == 0;
}

int process_number(char* string, int* pos, char* tokens[], int* token, char* prev) {
    char num[LEN_NUM] = {0};
    int has_point = 0, digits_after_point = 0, i = 0, flag = 1;

    while ((is_digit(string[*pos]) || (string[*pos] == '.' && is_digit(string[*pos + 1]) && flag))) {
        if (i >= LEN_NUM - 1) {
            flag = 0;
        }

        if (flag && string[*pos] == '.') {
            if (has_point) {
                flag = 0;
            }
            has_point = 1;
        } else if (flag && has_point) {
            digits_after_point++;
            if (digits_after_point > 6) {
                flag = 0;
            }
        }

        if (flag) {
            num[i++] = string[(*pos)++];
        }
    }

    if (flag && i > 0) {
        if (num[i - 1] == '.') {
            flag = 0;
        } else {
            tokens[*token] = malloc(i + 1);
            if (tokens[*token] == NULL) {
                flag = 0;
            } else {
                strcpy(tokens[(*token)++], num);
                strcpy(prev, num);
            }
        }
    }

    return flag;
}

int process_alpha(char* string, int* pos, char* tokens[], int* token, char* prev, double x) {
    char name[LEN_NUM] = {0};
    int i = 0;
    int flag = 1;

    while (is_alpha(string[*pos]) && i < LEN_NUM - 1) {
        name[i++] = string[(*pos)++];
    }

    if (is_func_or_x(name)) {
        if (strcmp(name, "x") == 0) {
            char x_value[LEN_NUM];

            snprintf(x_value, LEN_NUM, "%.6f", x);

            char* p = x_value + strlen(x_value) - 1;
            while (*p == '0' && p > x_value) {
                *p-- = '\0';
            }

            if (*p == '.') {
                *p = '\0';
            }

            tokens[*token] = malloc(strlen(x_value) + 1);
            if (tokens[*token] == NULL) {
                flag = 0;
            } else {
                strcpy(tokens[(*token)++], x_value);
                strcpy(prev, x_value);
            }
        } else {
            tokens[*token] = malloc(strlen(name) + 1);
            if (tokens[*token] == NULL) {
                flag = 0;
            } else {
                strcpy(tokens[(*token)++], name);
                strcpy(prev, name);
            }
        }
    } else {
        flag = 0;
    }

    return flag;
}

int process_operator(const char* string, int* pos, char* tokens[], int* token, char* prev, int* balance) {
    int flag = 1;
    char curr = string[*pos];

    if ((curr == ')' && strcmp(prev, "(") == 0) || (is_operator_1(curr) && is_operator_1(prev[0]))) {
        flag = 0;
    }

    if (curr == '(') {
        (*balance)++;
    }

    if (curr == ')') {
        (*balance)--;
    }

    if (*balance < 0) {
        flag = 0;
    }

    if (flag) {
        tokens[*token] = malloc(2);
        if (tokens[*token] == NULL) {
            flag = 0;
        } else {
            tokens[*token][0] = curr;
            tokens[(*token)++][1] = '\0';
            prev[0] = curr;
            prev[1] = '\0';
            (*pos)++;
        }
    }

    return flag;
}

int lexer(char* string, char* tokens[], int* n, double x) {
    int len = strlen(string), token = 0, pos = 0, balance = 0, ok = 1;
    char prev[LEN_NUM] = {0};

    while (pos < len && ok == 1) {
        if (string[pos] == ' ') {
            pos++;
        } else if (is_digit(string[pos]) || (string[pos] == '.' && is_digit(string[pos + 1]))) {
            ok = process_number(string, &pos, tokens, &token, prev);
        } else if (is_alpha(string[pos])) {
            ok = process_alpha(string, &pos, tokens, &token, prev, x);
        } else if (is_operator_or_bracket(string[pos])) {
            ok = process_operator(string, &pos, tokens, &token, prev, &balance);
        } else {
            ok = 0;
        }
    }

    if (balance != 0 || (token > 0 && is_operator_1(prev[0]))) {
        ok = 0;
    }

    *n = token;

    return ok;
}

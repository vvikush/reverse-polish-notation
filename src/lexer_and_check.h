#ifndef LEXER_AND_CHECK_H
#define LEXER_AND_CHECK_H

int is_operator_or_bracket(char c);
int is_operator_1(char c);
int is_alpha(char c);
int is_digit(char c);
int is_func_or_x(const char* s);
int process_number(char* string, int* pos, char* tokens[], int* token, char* prev);
int process_alpha(char* string, int* pos, char* tokens[], int* token, char* prev, double x);
int process_operator(const char* string, int* pos, char* tokens[], int* token, char* prev, int* balance);
int lexer(char* string, char* tokens[], int* n, double x);

#endif

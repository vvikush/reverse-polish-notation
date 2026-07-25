#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "token.h"

int is_operator(Token t);
int op_priority(Token t);
int is_open_bracket(Token t);
int is_close_bracket(Token t);
int shunting_yard(const Token* input, int input_length, Token* output, int* output_length);

#endif

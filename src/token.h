#ifndef TOKEN_H
#define TOKEN_H

typedef enum { TOKEN_INVALID = 0, TOKEN_NUMBER, TOKEN_OP, TOKEN_FUNC } TokenType;

typedef enum { FUNC_FABS, FUNC_EXP, FUNC_LN, FUNC_TAN, FUNC_COS, FUNC_SIN, FUNC_SQRT } FuncType;

typedef struct {
    TokenType type;
    union {
        double number;
        char op;
        FuncType function;
    } value;
} Token;

#endif

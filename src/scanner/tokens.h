#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    EOF_TOKEN,
    NAME,
    LAMBDA,
    DOT,
    L_PAREN,
    R_PAREN,
    ERROR
} token;

#endif
#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    EOF_TOKEN,
    NAME,
    LAMBDA,
    DOT,
    APPLICATION,
    L_PAREN,
    R_PAREN,
    ERROR
} token;

#endif
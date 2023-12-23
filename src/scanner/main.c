#include <stdio.h>
#include "tokens.h"
#include "status.h"

extern FILE* yyin;
extern char* yytext;
extern int yylex();

const char* token_names[] = {"EOF_TOKEN", "NAME", "LAMBDA", "DOT", "L_PAREN", "R_PAREN", "ERROR"};

int main() {
    int res = SUCCESS;

    if((yyin = fopen("./src/scanner/test.txt", "r")) == NULL) {
        res = -EIO;
        goto out;
    };

    token cur_token = yylex();
    while(cur_token != EOF_TOKEN) {
        printf("%s: %s\n", token_names[cur_token], yytext);
        cur_token = yylex();
    }

out:
    if(res == -EIO) printf("Error reading file!\n");
    return res;
}
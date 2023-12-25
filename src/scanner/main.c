#include <stdio.h>
#include "tokens.h"
#include "status.h"

extern FILE* yyin;
extern char* yytext;
extern int yylex();

const char* token_names[] = {"EOF_TOKEN", "NAME", "LAMBDA", "DOT", "L_PAREN", "R_PAREN", "ERROR"};

int main() {
    int res = SUCCESS;

    if((yyin = fopen("./data/test.txt", "r")) == NULL) {
        res = -EI;
        goto out;
    };

    FILE* scanner_output;
    if((scanner_output = fopen("./data/scanner_output.txt", "w")) == NULL) {
        res = -EO;
        goto out;
    }

    token cur_token = yylex();
    while(cur_token != EOF_TOKEN) {
        fprintf(scanner_output, "%d ", cur_token);
        cur_token = yylex();
    }

out:
    if(res == -EI) printf("Error reading file!\n");
    if(res == -EO) printf("Error writing to file!\n");
    fclose(yyin);
    fclose(scanner_output);
    return res;
}
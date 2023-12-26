#include <stdio.h>
#include <stdbool.h>
#include "../scanner/tokens.h"
#include "status.h"


int match(FILE* scanner_output, token expected_token);
int parse_E(FILE* scanner_output);

int main() {
    int res = SUCCESS;

    FILE* scanner_output;
    if((scanner_output = fopen("./data/scanner_output.txt", "r")) == NULL) {
        res = EI;
        goto out;
    }

    if(parse_E(scanner_output) && match(scanner_output, EOF_TOKEN)) {
        printf("Parse successful!\n");
    } else {
        printf("Parse failed!\n");
    }
    
out:
    if(res == EI) printf("Error reading file!\n");
    fclose(scanner_output);
    return res;
}

void look_ahead_one(FILE* scanner_output, token* cur_token) {
    int cur_token_num;
    if(fscanf(scanner_output, "%d", &cur_token_num) == EOF) {
        *cur_token = EOF_TOKEN;
    } else {
        *cur_token = (token)cur_token_num;
    }
}

int backtrack(FILE* scanner_output, long file_position) {
    int res = 0;

    if(fseek(scanner_output, file_position, SEEK_SET) != 0) {
        res = EFSEEK;
    }

    return res;
}

int match(FILE* scanner_output, token expected_token) {
    int res = 0;

    long file_position;
    if((file_position = ftell(scanner_output)) == -1) {
        res = EFSEEK;
        goto out;
    }

    token cur_token;
    look_ahead_one(scanner_output, &cur_token);

    if(cur_token == expected_token) {
        res = 1; 
    } else {
        if(backtrack(scanner_output, file_position) == EFSEEK) {
            res = EFSEEK;
            goto out;
        }
        res = 0; 
    }

out:
    if(res == EFSEEK) printf("Error while seeking file!");
    return res;
} 

int parse_E(FILE* scanner_output) {

    // E := S
    if(match(scanner_output, NAME)) {
        return 1;
    // E := ?S.E
    } else if(match(scanner_output, LAMBDA)) {
        return match(scanner_output, NAME)
               && match(scanner_output, DOT)
               && parse_E(scanner_output);
    // E := (E\E)
    } else if(match(scanner_output, L_PAREN)) {
        return parse_E(scanner_output) 
               && match(scanner_output, APPLICATION) 
               && parse_E(scanner_output)
               && match(scanner_output, R_PAREN);
    }

    return 0;
}
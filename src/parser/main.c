#include <stdio.h>
#include <stdbool.h>
#include "../scanner/tokens.h"
#include "status.h"


int match(FILE* scanner_output, token expected_token, bool* matched);

int main() {
    int res = SUCCESS;

    FILE* scanner_output;
    if((scanner_output = fopen("./data/scanner_output.txt", "r")) == NULL) {
        res = EI;
        goto out;
    }

    bool matched;

    match(scanner_output, (token)3, &matched);
    printf("matched %d: %s\n", 3, matched? "true" : "false");
    match(scanner_output, (token)4, &matched);
    printf("matched %d: %s\n", 4, matched? "true" : "false");
    match(scanner_output, (token)1, &matched);
    printf("matched %d: %s\n", 1, matched? "true" : "false");
    match(scanner_output, (token)2, &matched);
    printf("matched %d: %s\n", 2, matched? "true" : "false");

out:
    if(res == EI) printf("Error reading file!\n");
    fclose(scanner_output);
    return res;
}

void look_ahead_one(FILE* scanner_output, token* cur_token) {
    int cur_token_num;
    if(fscanf(scanner_output, "%d", &cur_token_num) == EOF) {
        *cur_token = EOF_TOKEN;
    }

    *cur_token = (token)cur_token_num;
}

int backtrack(FILE* scanner_output, long file_position) {
    int res = 0;

    if(fseek(scanner_output, file_position, SEEK_SET) != 0) {
        res = EFSEEK;
    }

    return res;
}

int match(FILE* scanner_output, token expected_token, bool* matched) {
    int res = 0;

    long file_position;
    if((file_position = ftell(scanner_output)) == -1) {
        res = EFSEEK;
        goto out;
    }
    printf("expected_token: %d, file_position: %ld \\\\ ", (int) expected_token, file_position);

    token cur_token;
    look_ahead_one(scanner_output, &cur_token);

    if(cur_token == expected_token) {
        *matched = true; 
    } else {
        if(backtrack(scanner_output, file_position) == EFSEEK) {
            res = EFSEEK;
            goto out;
        }
        *matched = false; 
    }

out:
    if(res == EFSEEK) printf("Error while seeking file!");
    return res;
}

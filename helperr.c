#include <stdio.h>

#include "life.h"

void print_error(char *error) {
    fprintf(stderr, "\e[1;31mErr: %s\e[0m\n\n", error);
}

void help() {
    FILE *f = fopen("./HELP", "r");

    while (!feof(f)) {
        char c = 0;
        fread(&c, sizeof(c), 1, f);
        printf("%c", c);
    }

    printf("\n");

    fclose(f);
}
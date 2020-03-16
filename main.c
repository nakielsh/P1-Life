#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "life.h"

// ./build/life -file owo -n 5 [ -out out ]
// ./build/life -file test.life -n 10

int main( int argc, char **argv) {
    int n_gen = -1;
    char *in_file = NULL;
    char *out_dir = ".";

    plife state;

    if (argc < 2) {
        // help();
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        char *current = argv[i];

        if (!strcmp(current, "-n") && i != argc - 1) {
            n_gen = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(current, "-file") && i != argc - 1) {
            in_file = argv[i + 1];
            i++;
        } else if (!strcmp(current, "-out") && i != argc - 1) {
            out_dir = argv[i + 1];
            i++;
        }
        // owo pętla
    }

    if (n_gen < 0) {
        // N < 0!
        printf("n < 0!\n");
        return 1;
    } else if (in_file == NULL) { 
        // no input file
        printf("podaj plik!\n");
        return 1;
    }

    state = load_life(in_file);

    if (state == NULL) {
        printf("NIE MOGE ZALADOWAC PLIKU, POMOCY!\n");
        return 2;
    }

    for (int n = 0; n < n_gen; n++) {
        plife new_state = generate_life(state);

        // zapis

        free_life(state);
        state = new_state;
    }

    return 0;
}

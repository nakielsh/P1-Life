#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "life.h"

int main( int argc, char **argv) {
    int n_gen = -1;
    char *in_file = NULL;
    char *out_dir = ".";

    char *out_file_name = NULL;

    int wrap_edges = 0;

    plifepng png_info = create_life_png_info(
        32, NULL
    );

    plife state;

    if (argc < 2) {
        print_error("No arguments provided.");
        help();
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        char *current = argv[i];

        if (!strcmp(current, "-n") && i != argc - 1) {
            n_gen = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(current, "-wrap")) {
            wrap_edges = 1;

        } else if (!strcmp(current, "-file") && i != argc - 1) {
            in_file = argv[i + 1];
            i++;
        } else if (!strcmp(current, "-out") && i != argc - 1) {
            out_dir = argv[i + 1];
            i++;

        } else if (!strcmp(current, "-png-circles")) {
            png_info->coloring_func = pixel_circles;
        } else if (!strcmp(current, "-png-size") && i != argc - 1) {
            int size = atoi(argv[i + 1]);
            if (size <= 0) {
                print_error("Provided value for -png-size is not valid.");
                help();
                return 1;
            }

            png_info->scale = size;
            i++;
        }
       
    }

    if (n_gen < 0) {
        // N < 0!
        print_error("Provided value for -n is not valid.");
        help();
        return 1;
    } else if (in_file == NULL) { 
        // no input file
        print_error("No input file provided.");
        printf("podaj plik!\n");
        return 1;
    }

    state = load_life(in_file);

    if (state == NULL) {
        print_error("Could not load input file.");
        return 1;
    }

    save_png(out_dir, state, 0, png_info);

    for (int n = 0; n < n_gen; n++) {
        plife new_state = generate_life(state, wrap_edges);

        save_png(out_dir, new_state, n + 1, png_info);

        free_life(state);
        state = new_state;
    }

    if (n_gen) {
        out_file_name = create_file_name(out_dir, "final.life");

        if (save_life(out_file_name, state)) {
            printf("Couldn't final snapshot file to %s.\n", out_file_name);
        } else {
            printf("Saved final snapshot file to %s.\n", out_file_name);
        }

        free(out_file_name);
    }

    // Bye bye pointer
    free_life(state);
    free(png_info);

    return 0;
}

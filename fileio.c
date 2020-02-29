#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "life.h"

#define IDX_TO_X(idx, width) ((idx) % width)
#define IDX_TO_Y(idx, width) ((idx) / width)

plife create_life(unsigned int w, unsigned int h) {
    plife gol = malloc(sizeof(life));
    char **board = malloc(w * sizeof(char*));

    for (int x = 0; x < w; x++) {
        board[x] = malloc(h * sizeof(char));
    }

    gol->width = w;
    gol->height = h;
    gol->data = board;

    return gol;
}

void free_life(plife gol) {
    for (int x = 0; x < gol->width; x++) {
        free(gol->data[x]);
    }
    free(gol->data);
    free(gol);
}

plife load_life(char *file_name) {
    plife gol;

    unsigned int w, h;
    char **board;

    char magic[5];
    char item;
    unsigned int ccount;

    FILE *f = fopen(file_name, "r");

    // Check whether the Certified Magic Prefix™ is present
    fread(magic, sizeof(char), 4, f);
    if (strcmp(magic, "LIFE")) {
        fclose(f);
        return NULL;
    }

    // Read the board dimensions
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);

    // Create the life structure
    gol = create_life(w, h);

    // Read the board data
    if ((w * h) % 8) {
        ccount = (w * h) / 8 + 1;
    } else {
        ccount = (w * h) / 8;
    }
    for (int i = 0; i < ccount; i++) {
        fread(&item, sizeof(char), 1, f);

        for (int j = 0; j < 8; j++) {
            int x = IDX_TO_X(8 * i + j, w);
            int y = IDX_TO_Y(8 * i + j, w);

            if (x >= w || y >= h) break;
            gol->data[x][y] = ((item >> j) & 1) ? 1 : 0;
        }
    }

    fclose(f);

    return gol;
}

int save_life(char *file_name, plife gol) {
    FILE *f = fopen(file_name, "w");

    char current = 0, counter = 0;

    // Write the Certified Magic Prefix™
    fwrite("LIFE", sizeof(char), strlen("LIFE"), f);

    // Write the board dimensions
    fwrite(&(gol->width), sizeof(unsigned int), 1, f);
    fwrite(&(gol->height), sizeof(unsigned int), 1, f);

    // Write the board
    for (int y = 0; y < gol->height; y++) {
        for (int x = 0; x < gol->width; x++) {
            current |= gol->data[x][y] << counter;

            counter++;

            if (counter == 8) {
                fwrite(&current, sizeof(char), 1, f);

                current = 0;
                counter = 0;
            }
        }
    }

    if (counter != 0) {
        fwrite(&(current), sizeof(char), 1, f);
    }

    fclose(f);

    return 0;
}
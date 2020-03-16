#include <stdlib.h>

#include "life.h"

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
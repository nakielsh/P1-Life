#include <stdlib.h>
#include <stdio.h>

#include "../life.h"

void print_life_board(plife life) {
    printf("%i, %i\n", life->width, life->height);
    for (int y = 0; y < life->height; y++) {
        for (int x = 0; x < life->width; x++) {
            printf("%i ", life->data[x][y]);
        }
        printf("\n");
    }
}

int main() {
    plife gol = create_life(10, 10);
    plife loaded;

    for (int x = 0; x < gol->width; x++) {
        for (int y = 0; y < gol->height; y++) {
            gol->data[x][y] = rand() % 2;
        }
    }

    print_life_board(gol);
    save_life("./test.life", gol);
    free_life(gol);

    loaded = load_life("./test.life");

    if (!loaded) {
        printf("err\n");
    } else {
        print_life_board(loaded);
        free_life(loaded);
    }

    return 0;
}
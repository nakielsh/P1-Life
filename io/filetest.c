#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../life.h"

void print_life_board(plife life) {
    printf("%i, %i\n", life->width, life->height);
    for (int y = 0; y < life->height; y++) {
        for (int x = 0; x < life->width; x++) {
            printf("%c ", life->data[x][y] ? '#' : ' ');
        }
        printf("\n");
    }
}

float pixel_circles(int x, int y, plife gol, plifepng info, int channel) {
    float pixel_x = (float)(x % info->scale) / info->scale - 0.5;
    float pixel_y = (float)(y % info->scale) / info->scale - 0.5;
    float in_circle = sqrtf(pixel_x * pixel_x + pixel_y * pixel_y) <= 0.5;

    in_circle *= gol->data[x / info->scale][y / info->scale];

    if (channel == 2) return in_circle; // Blue
    if (channel == 1) return 0.0; // Green

    return in_circle * ((float)x / (float)(gol->width * info->scale));
}

int main() {
    plife gol = create_life(10, 10);
    plife loaded;

    plifepng png_info = create_life_png_info(32, pixel_circles);

    for (int x = 0; x < gol->width; x++) {
        for (int y = 0; y < gol->height; y++) {
            gol->data[x][y] = (x + y) % 2;
        }
    }

    printf("Saved to test.life:\n");
    print_life_board(gol);
    save_life("./test.life", gol);
    save_life_png("./test.png", gol, png_info);
    free_life(gol);

    loaded = load_life("./test.life");

    if (!loaded) {
        printf("err\n");
    } else {
        printf("Loaded from test.life:\n");
        print_life_board(loaded);
        free_life(loaded);
    }

    return 0;
}
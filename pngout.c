#include <png.h>
#include <stdlib.h>

#include "life.h"

float default_coloring_func(
    int x, int y, plife gol, plifepng info, int channel
) {
    int life_x = x / info->scale;
    int life_y = y / info->scale;

    int life_state = gol->data[life_x][life_y];

    return (float)life_state;
}

plifepng create_life_png_info(unsigned int scale, png_coloring_func f) {
    plifepng out = malloc(sizeof(lifepng));

    out->scale = scale;
    out->coloring_func = f;

    if (f == NULL) out->coloring_func = default_coloring_func;

    return out;
}

int save_life_png(char *file_name, plife gol, plifepng info) {
    FILE *f = fopen(file_name, "wb");
    png_structp png_data;
    png_infop png_info;
    png_bytep png_row;

    int p_width = gol->width * info->scale;
    int p_height = gol->height * info->scale;

    if (f == NULL) return 1; // like if you cry every time

    // Writing time i guess
    png_data = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,
        NULL, NULL, NULL
    );
    if (png_data == NULL) return 2;

    // Info-chan is here with us
    png_info = png_create_info_struct(png_data);
    if (png_info == NULL) return 3;
    
    png_init_io(png_data, f);

    // Header time!
    png_set_IHDR(
        png_data, png_info,
        p_width, p_height,
        8, PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE,
        PNG_FILTER_TYPE_BASE
    );
    png_write_info(png_data, png_info);

    // Write stuff
    png_row = (png_bytep)malloc(
        3 * p_width * sizeof(png_byte)
    );

    for (int y = 0; y < p_height; y++) {
        for (int x = 0; x < p_width; x++) {
            png_row[x * 3] = (int)(info->coloring_func(x, y, gol, info, 0) * 255);
            png_row[x * 3 + 1] = (int)(info->coloring_func(x, y, gol, info, 1) * 255);
            png_row[x * 3 + 2] = (int)(info->coloring_func(x, y, gol, info, 2) * 255);
        }
        png_write_row(png_data, png_row);
    }

    png_write_end(png_data, NULL);

    // Free The Garbage
    fclose(f);
    png_free_data(
        png_data, png_info, PNG_FREE_ALL, -1
    );
    png_destroy_write_struct(
        &png_data, (png_infopp)NULL
    );
    if (png_row != NULL) free(png_row);

    return 0;
}
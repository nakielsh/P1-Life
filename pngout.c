#include <png.h>
#include <stdlib.h>
#include <math.h>

#include "life.h"
#include "overkill/overkill.h"

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

int save_life_png(char *file_name, plife gol, plifepng info, char *ovk_shader_file) {
    FILE *f = fopen(file_name, "wb");
    png_structp png_data;
    png_infop png_info;
    png_bytep png_row;

    ovk_context_pt ovk_ctx;
    ovk_program_pt ovk_prog;

    int p_width = gol->width * info->scale;
    int p_height = gol->height * info->scale;

    if (f == NULL) return 1; // like if you cry every time

#ifdef BUILD_OVERKILL
    if (ovk_shader_file != NULL) {
        // Load an Overkill shader
        if (ovk_load_program(ovk_shader_file, &ovk_prog)) {
            print_error("Overkill error - couldn't load shader.");
            exit(1);
        }
        if (ovk_create_context(1024, &ovk_ctx)) {
            print_error("Overkill error - couldn't create context.");
            exit(1);
        }
    }
#endif

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
#ifdef BUILD_OVERKILL
            if (ovk_shader_file != NULL) {
                // Let Overkill shaders do their thing
                ovk_reset_context(ovk_ctx);
                ovk_uni1_init_variants(
                    ovk_ctx,
                    (float)x / (float)p_width,
                    (float)y / (float)p_height
                );
                ovk_set_variant(ovk_ctx, 0x20, (float)(x % info->scale) / info->scale, OVK_VARIANT_READONLY); // cell_coords_x
                ovk_set_variant(ovk_ctx, 0x21, (float)(y % info->scale) / info->scale, OVK_VARIANT_READONLY); // cell_coords_y
                ovk_set_variant(ovk_ctx, 0x22, (float)gol->data[x / info->scale][y / info->scale], OVK_VARIANT_READONLY); // cell_state
                ovk_run(ovk_ctx, ovk_prog, ovk_uni1_process_opcode);

                png_row[x * 3] = (char)(255.0 * ovk_get_variant(ovk_ctx, OVK_UNI1_V_OUT_PIXEL_RED));
                png_row[x * 3 + 1] = (char)(255.0 * ovk_get_variant(ovk_ctx, OVK_UNI1_V_OUT_PIXEL_GREEN));
                png_row[x * 3 + 2] = (char)(255.0 * ovk_get_variant(ovk_ctx, OVK_UNI1_V_OUT_PIXEL_BLUE));
            } else {
#endif
                // Use the built-in coloring func
                png_row[x * 3] = (int)(info->coloring_func(x, y, gol, info, 0) * 255);
                png_row[x * 3 + 1] = (int)(info->coloring_func(x, y, gol, info, 1) * 255);
                png_row[x * 3 + 2] = (int)(info->coloring_func(x, y, gol, info, 2) * 255);
#ifdef BUILD_OVERKILL
            }
#endif
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
    free(png_info);
    if (png_row != NULL) free(png_row);

#ifdef BUILD_OVERKILL
    if (ovk_shader_file != NULL) {
        ovk_free_context(ovk_ctx);
        ovk_free_program(ovk_prog);
    }
#endif

    return 0;
}

float pixel_circles(int x, int y, plife gol, plifepng info, int channel) {
    float pixel_x = (float)(x % info->scale) / info->scale - 0.5;
    float pixel_y = (float)(y % info->scale) / info->scale - 0.5;
    float distance = sqrtf(pixel_x * pixel_x + pixel_y * pixel_y);
    float small_distance = 1.0 / (float)info->scale;

    float in_circle = 0;

    if (distance < 0.5 - small_distance) {
        in_circle = 1;
    } else if (distance < 0.5) {
        in_circle = 1.0 - (distance - 0.5 + small_distance) / small_distance;
    }

    in_circle *= gol->data[x / info->scale][y / info->scale];

    return in_circle;
}

void save_png(char *out_dir, plife state, int n, plifepng png_info, char *ovk_shader_file) {
    char *file_name = create_gen_name(out_dir, "pngout", n, "png");

    int err = save_life_png(file_name, state, png_info, ovk_shader_file);
    if (err) {
        printf("Couldn't save generation #%d to %s.\n", n, file_name);
    } else {
        printf("Saved generation #%d to %s.\n", n, file_name);
    }

    free(file_name);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "life.h"

#define IDX_TO_X(idx, width) ((idx) % width)
#define IDX_TO_Y(idx, width) ((idx) / width)

char *convert_to_char_table(plife gol, unsigned int *out_count) {
    char *ct = NULL;
    unsigned int ct_pos = 0;
    char current = 0, counter = 0;

    unsigned int ct_count = gol->width * gol->height / 8;
    if ((gol->width * gol->height) % 8 != 0) ct_count++;

    *out_count = ct_count;

    ct = (char*)malloc(ct_count * sizeof(char));

    for (int y = 0; y < gol->height; y++) {
        for (int x = 0; x < gol->width; x++) {
            current |= gol->data[x][y] << counter;

            counter++;

            if (counter == 8) {
                ct[ct_pos] = current;

                current = 0;
                counter = 0;
                ct_pos++;
            }
        }
    }

    if (counter != 8 && ct_pos < ct_count) {
        ct[ct_pos] = current;
    }

    return ct;
}

void convert_from_char_table(plife gol, char *ct) {
    char item;

    unsigned int ct_count = gol->width * gol->height / 8;
    if ((gol->width * gol->height) % 8 != 0) ct_count++;

    for (int i = 0; i < ct_count; i++) {
        item = ct[i];

        for (int j = 0; j < 8; j++) {
            int x = IDX_TO_X(8 * i + j, gol->width);
            int y = IDX_TO_Y(8 * i + j, gol->width);

            if (x >= gol->width || y >= gol->height) break;
            gol->data[x][y] = ((item >> j) & 1) ? 1 : 0;
        }
    }
}

plife load_life(char *file_name) {
    plife gol;

    unsigned int w, h;
    char **board;

    char magic[4] = "NOPE";
    char item;
    unsigned int ccount;

    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        return NULL;
    }

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

    // Prep the char table
    unsigned int ct_count = gol->width * gol->height / 8;
    if ((gol->width * gol->height) % 8 != 0) ct_count++;

    char *ct = (char*)malloc(ct_count * sizeof(char));
    unsigned int ct_pos = 0;
    char rle_chain_length = 0, rle_chain_body = 0;

    // Unwrap RLE data
    while(!feof(f) && ct_pos < ct_count) {
        fread(&rle_chain_length, sizeof(char), 1, f);
        fread(&rle_chain_body, sizeof(char), 1, f);

        for (int i = 0; i < rle_chain_length; i++) {
            ct[ct_pos] = rle_chain_body;
            ct_pos++;
        }
    }

    // Put the char data back
    convert_from_char_table(gol, ct);

    free(ct);
    fclose(f);

    return gol;
}

int save_life(char *file_name, plife gol) {
    FILE *f = fopen(file_name, "w");
    if (f == NULL) return 1; // Summertime Sadness

    char current = 0, counter = 0;

    // Write the Certified Magic Prefix™
    fwrite("LIFE", sizeof(char), strlen("LIFE"), f);

    // Write the board dimensions
    fwrite(&(gol->width), sizeof(unsigned int), 1, f);
    fwrite(&(gol->height), sizeof(unsigned int), 1, f);

    // Prep the char table
    unsigned int ct_count = 0;
    char *ct = convert_to_char_table(gol, &ct_count);
    if (ct == NULL) return 1;

    // Do RLE to it
    char rle_chain_length = 0, rle_chain_body = 0;

    for (int i = 0; i < ct_count; i++) {
        if (
            (rle_chain_length && rle_chain_body != ct[i]) ||
            rle_chain_length == 255
        ) {
            fwrite(&rle_chain_length, sizeof(char), 1, f);
            fwrite(&rle_chain_body, sizeof(char), 1, f);

            rle_chain_length = 0;
        }

        if (!rle_chain_length) {
            rle_chain_length = 1;
            rle_chain_body = ct[i];
        } else if (rle_chain_length && rle_chain_body == ct[i]) {
            rle_chain_length++;
        }
    }

    free(ct);

    if (rle_chain_length) {
        fwrite(&rle_chain_length, sizeof(char), 1, f);
        fwrite(&rle_chain_body, sizeof(char), 1, f);
    }

    fclose(f);

    return 0;
}
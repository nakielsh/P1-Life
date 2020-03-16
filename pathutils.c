#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "life.h"

char *create_file_name(char *out_dir, char *file_name) {
    char *new_str = malloc(sizeof(char) * (strlen(out_dir) + strlen(file_name) + 2));

    sprintf(new_str, "%s/%s", out_dir, file_name);

    return new_str;
}

char *create_gen_name(char *out_dir, char *file_name, int n, char *ext) {
    char *new_str = malloc(sizeof(char) * (strlen(out_dir) + strlen(file_name) + 7 + strlen(ext)));

    sprintf(new_str, "%s/%s_%03d.%s", out_dir, file_name, n, ext);

    return new_str;
}

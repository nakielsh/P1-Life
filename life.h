#ifndef __LIFE_H__
#define __LIFE_H__

typedef struct life_struct {
    unsigned int width;
    unsigned int height;
    char **data;
} life, *plife;

struct life_png_struct;

typedef float (*png_coloring_func)(
    int x, int y, plife gol, struct life_png_struct* info, int channel
);

typedef struct life_png_struct {
    unsigned int scale;
    png_coloring_func coloring_func;
} lifepng, *plifepng;

plife create_life(unsigned int w, unsigned int h);
void free_life(plife gol);

plife generate_life(plife previous);

plife load_life(char *file_name);
int save_life(char *file_name, plife gol);


float default_coloring_func(int x, int y, plife gol, plifepng info, int channel);
plifepng create_life_png_info(unsigned int scale, png_coloring_func f);
int save_life_png(char *file_name, plife gol, plifepng info);

#endif
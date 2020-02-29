#ifndef __LIFE_H__
#define __LIFE_H__

typedef struct {
    unsigned int width;
    unsigned int height;
    char **data;
} life, *plife;

plife create_life(unsigned int w, unsigned int h);
void free_life(plife gol);

plife generate_life(plife previous);

plife load_life(char *file_name);
int save_life(char *file_name, plife gol);

int save_life_png(char *file_name, plife gol);

#endif
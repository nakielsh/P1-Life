#ifndef __LIFE_H__
#define __LIFE_H__

typedef struct {
    unsigned int width;
    unsigned int height;
    char **data;
} life, *plife;

plife generate_life(plife previous);

plife load_life(char *file_name);
int save_life(char *file_name, plife life);

int save_life_png(char *file_name, plife life);

#endif
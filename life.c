#include "life.h"

#define UP_LEFT previous->data[x-1][y-1]
#define UP previous->data[x][y-1]
#define UP_RIGTH previous->data[x+1][y-1]
#define LEFT previous->data[x-1][y]
#define RIGHT previous->data[x+1][y]
#define DOWN_LEFT previous->data[x-1][y+1]
#define DOWN previous->data[x][y+1]
#define DOWN_RIGHT previous->data[x+1][y+1]
#define MY_CELL current->data[x][y]
#define PREVIOUS_CELL previous->data[x][y]

// Handle problematic coordinates with grace™
char get_value_at_coord(plife gol, int x, int y, int wrap_edges, int *did_modify_coords) {
    int _x = x, _y = y;

    *did_modify_coords = 0;

    if (wrap_edges) {
        if (_x < 0) _x += gol->width;
        else if (_x >= gol->width) _x -= gol->width;
        if (_y < 0) _y += gol->height;
        else if (_y >= gol->height) _y -= gol->height;
    } else {
        if (_x < 0) _x = 0;
        else if (_x >= gol->width) _x = gol->width - 1;
        if (_y < 0) _y = 0;
        else if (_y >= gol->height) _y = gol->height - 1;
    }

    if (x != _x || y != _y) *did_modify_coords = 1;

    return gol->data[_x][_y];
}

int count_friends(plife gol, int x, int y) {
    int friends = 0;

    for (int _x = -1; _x < 2; _x++) {
        for (int _y = -1; _y < 2; _y++) {
            if (!_x && !_y) continue;

            int new_x = x + _x, new_y = y + _y;
            int did_modify_coords = 0;

            char value = get_value_at_coord(gol, new_x, new_y, 0, &did_modify_coords);
            
            if (!did_modify_coords) {
                friends += value;
            }
        }
    }

    return friends;
}


plife generate_life(plife previous){

    plife current = create_life(previous->width, previous->height);

    for( int x = 0; x < previous->width; x++){
        for(int y = 0; y < previous->height; y++){
            int friends = count_friends(previous, x, y);

            if (
                PREVIOUS_CELL == 1 &&
                (friends < 2 || friends > 3)
            )
                MY_CELL = 0;
            else
                MY_CELL = 1;

            if (
                PREVIOUS_CELL == 0 && friends == 3
            )
                MY_CELL = 1;
            else
                MY_CELL = 0;

        }
    }

    return current; 
}

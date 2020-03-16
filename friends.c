#include "life.h"

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

int count_friends(plife gol, int x, int y, int wrap_edges) {
    int friends = 0;

    for (int _x = -1; _x < 2; _x++) {
        for (int _y = -1; _y < 2; _y++) {
            if (!_x && !_y) continue;

            int new_x = x + _x, new_y = y + _y;
            int did_modify_coords = 0;

            char value = get_value_at_coord(gol, new_x, new_y, wrap_edges, &did_modify_coords);
            
            if (!did_modify_coords || wrap_edges) {
                friends += value;
            }
        }
    }

    return friends;
}

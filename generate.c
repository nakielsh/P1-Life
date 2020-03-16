#include "life.h"

plife generate_life(plife previous, int wrap_edges){
    plife current = create_life(previous->width, previous->height);

    for( int x = 0; x < previous->width; x++){
        for(int y = 0; y < previous->height; y++){
            int friends = count_friends(previous, x, y, wrap_edges);

            if (previous->data[x][y]) { // alive
                if (friends == 2 || friends == 3) {
                    current->data[x][y] = 1;
                } else {
                    current->data[x][y] = 0;
                }
            } else { // effin dead
                if (friends == 3) {
                    current->data[x][y] = 1;
                } else {
                    current->data[x][y] = 0;
                }
            }
        }
    }

    return current; 
}

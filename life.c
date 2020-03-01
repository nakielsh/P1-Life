#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


plife generate_life(plife previous){

    plife current;

    for( int x = 0; x < previous->width; x++){
        for(int y = 0; y < previous->height; y++){

            //conditions for a cell to stay alive OR die
            if(PREVIOUS_CELL == 1){ 
                if(x==0 && y==0){ //up-left corner
                    if(RIGHT+DOWN_RIGHT+DOWN>=2 && RIGHT+DOWN_RIGHT+DOWN<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==previous->width && y==0){ //up-right corner
                    if(LEFT+DOWN_LEFT+DOWN>=2 && LEFT+DOWN_LEFT+DOWN<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==0 && y==previous->height){ //down-left corner
                    if(RIGHT+UP_RIGTH+UP>=2 && RIGHT+UP_RIGTH+UP<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==previous->width && y==previous->height){ //down-right corner
                    if(LEFT+UP_LEFT+UP>=2 && LEFT+UP_LEFT+UP<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==0 && y!=0 && y!=previous->height){ //left border
                    if(UP+UP_RIGTH+RIGHT+DOWN_RIGHT+DOWN>=2 && UP+UP_RIGTH+RIGHT+DOWN_RIGHT+DOWN<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==previous->width && y!=0 && y!=previous->height){ //right border
                    if(UP+UP_LEFT+LEFT+DOWN_LEFT+DOWN>=2 && UP+UP_LEFT+LEFT+DOWN_LEFT+DOWN<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x!=0 && x!=previous->width && y==0){ //up border
                     if(LEFT+DOWN_LEFT+DOWN+DOWN_RIGHT+RIGHT>=2 && LEFT+DOWN_LEFT+DOWN+DOWN_RIGHT+RIGHT<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x!=0 && x!=previous->width && y==previous->height){ //down border
                    if(LEFT+UP_LEFT+UP+UP_RIGTH+RIGHT>=2 && LEFT+UP_LEFT+UP+UP_RIGTH+RIGHT<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                else{ //mid
                    if(LEFT+UP_LEFT+UP+UP_RIGTH+RIGHT+DOWN_RIGHT+DOWN+DOWN_LEFT>=2 && LEFT+UP_LEFT+UP+UP_RIGTH+RIGHT+DOWN_RIGHT+DOWN+DOWN_LEFT<=3) MY_CELL=1;
                    else MY_CELL=0;
                }
            }

            //conditions for a cell to stay death OR be born
            if(PREVIOUS_CELL == 0){ 
                if(x==0 && y==0){ //up-left corner
                    if(RIGHT+DOWN_RIGHT+DOWN=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==previous->width && y==0){ //up-right corner
                    if(LEFT+DOWN_LEFT+DOWN=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==0 && y==previous->height){ //down-left corner
                    if(RIGHT+UP_RIGTH+UP=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==previous->width && y==previous->height){ //down-right corner
                    if(LEFT+UP_LEFT+UP=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==0 && y!=0 && y!=previous->height){ //left border
                    if(UP+UP_RIGTH+RIGHT+DOWN_RIGHT+DOWN=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x==previous->width && y!=0 && y!=previous->height){ //right border
                    if(UP+UP_LEFT+LEFT+DOWN_LEFT+DOWN=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x!=0 && x!=previous->width && y==0){ //up border
                     if(LEFT+DOWN_LEFT+DOWN+DOWN_RIGHT+RIGHT=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                if(x!=0 && x!=previous->width && y==previous->height){ //down border
                    if(LEFT+UP_LEFT+UP+UP_RIGTH+RIGHT=3) MY_CELL=1;
                    else MY_CELL=0;
                }
                else{ //mid
                    if(LEFT+UP_LEFT+UP+UP_RIGTH+RIGHT+DOWN_RIGHT+DOWN+DOWN_LEFT=3) MY_CELL=1;
                    else MY_CELL=0;
                }
            }
        }
    }
    return current; 
}



int main( int argc, char **argv){

    return 0;
}
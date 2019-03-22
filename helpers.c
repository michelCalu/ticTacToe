#ifdef linux
#define clear "clear"
#endif
#ifdef _WIN32
#define clear "cls"
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "helpers.h"


int readStringFromUser(char *input, int length){
    char *c = NULL;
    if (fgets(input, length, stdin) != NULL){
        c = strchr(input, '\n');
        if (c != NULL){
            *c = '\0';
        }else{
            flush_stdin();
        }
        return 1;
    }
    else{
        return 0;
    }
}

int flush_stdin(){
    while (getchar()!='\n');
    return 1;
}

bool validCoordinates (int ligne, int colonne){
    bool coord_valide=false;
    if((ligne>=0)&&(ligne<=9)&&(colonne>=0)&&(colonne<=9)){
       coord_valide=true;
    }
    return coord_valide;
}

void clearConsole(){
    system(clear);
}

void randomAtoB(int *x, int *y, int A, int B){
    time_t t;
    srand((unsigned) time(&t));
    *x=rand()%(B-A);
    *y=rand()%(B-A);
}

void randomAdjacentCell(int *x, int *y){

    *x=-2+(rand()%(4-0));

    *y=-2+(rand()%(4-0));
}

void waitSeconds(float seconds){
    clock_t end=clock()+(seconds*CLOCKS_PER_SEC);

    while(clock()<end);
}

char *drawBoard (int *length){

    char drawing[]="\
    A : B : C : D : E : F : G : H : I : J\n\
  +===+===+===+===+===+===+===+===+===+===+\n\
1 | * | * | * | * | * | * | * | * | * | * | 1\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
2 | * | * | * | * | * | * | * | * | * | * | 2\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
3 | * | * | * | * | * | * | * | * | * | * | 3\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
4 | * | * | * | * | * | * | * | * | * | * | 4\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
5 | * | * | * | * | * | * | * | * | * | * | 5\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
6 | * | * | * | * | * | * | * | * | * | * | 6\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
7 | * | * | * | * | * | * | * | * | * | * | 7\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
8 | * | * | * | * | * | * | * | * | * | * | 8\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
9 | * | * | * | * | * | * | * | * | * | * | 9\n\
- +---+---+---+---+---+---+---+---+---+---+ -\n\
10| * | * | * | * | * | * | * | * | * | * | 10\n\
  +===+===+===+===+===+===+===+===+===+===+\n\
    A : B : C : D : E : F : G : H : I : J";

*length=strlen(drawing);

char *drawingPtr = malloc(*length*sizeof(char));

strcpy(drawingPtr,drawing);

return drawingPtr;

}

char getOpponentSymbol (char mySymbol){
    if (mySymbol == 'X')
        return 'O';
    else
        return 'X';
}



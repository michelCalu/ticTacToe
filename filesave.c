#include <stdio.h>
#include <stdbool.h>
#include "gamestate.h"
#include "players.h"

const char * FILENAME = "gamesave.bin";

    FILE *f;

void createFile (){

	f = fopen(FILENAME, "wb");

    fclose(f);
}

void WritePlayerToFile(struct player *playerToSave, int id) {

	f = fopen(FILENAME, "rb+");

    fseek( f, (id-1)*(sizeof(struct player)), SEEK_SET );

    fwrite(playerToSave,sizeof(struct player),1,f);

    fclose(f);
}

void WriteGamestateToFile(struct Game *gamestateToSave) {

	f = fopen(FILENAME, "rb+");

    fseek( f, 2*sizeof(struct player), SEEK_SET );

    fwrite(gamestateToSave,sizeof(struct Game),1,f);

    fclose(f);
}

struct player *ReadPlayerFromFile(struct player *savedPlayer,int playerNb){


    f = fopen(FILENAME, "rb");

    fseek( f, (playerNb-1)*sizeof(struct player), SEEK_SET );

    fread(savedPlayer,sizeof(struct player),1,f);

    fclose(f);

    return savedPlayer;
}

gamestate readGamestateFromFile(gamestate oxo){

    f = fopen(FILENAME, "rb");

    fseek( f, 2*sizeof(struct player), SEEK_SET );

    fread(oxo,sizeof(struct Game),1,f);

    fclose(f);

    return oxo;

};

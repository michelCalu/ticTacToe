# makefile Michel Caluwaerts - 07/05/2015
# projet de programmation 2015


CC=gcc
CFLAGS=-W -Wall
LFLAGS=-std=c99 -lm
EXEC=a
all: $(EXEC)

a: main.o gamestate.o players.o game.o helpers.o filesave.o
    $(CC) -o $@ $^ $(LDFLAGS) $(LFLAGS)

main.o: gamestate.h players.h game.h helpers.h filesave.h

gamestate.o: helpers.h filesave.h

players.o: gamestate.h players.h helpers.h filesave.h

game.o: gamestate.h players.h

helpers.o: helpers.h

filesave.o: gamestate.h players.h

%.o: %.c
    $(CC) -o $@ -c $< $(CFLAGS) $(LFLAGS)


clean:
    rm -rf *.o
mrproper: clean
    rm -rf $(EXEC)
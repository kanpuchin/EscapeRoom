.PHONY: clean

RM = rm -f

escape: game.o room.o room2.o room3.o chat.o
	gcc -o escape game.o room.o room2.o room3.o chat.o -lcurses -lpthread

game.o: game.c
	gcc -Wall -g -c game.c

room.o: room.c room.h
	gcc -Wall -g -c room.c

room2.o: room2.c room.h
	gcc -Wall -g -c room2.c

room3.o: room3.c room.h
	gcc -Wall -g -c room3.c

chat.o: chat.c chat.h
	gcc -Wall -g -c chat.c

clean:
	$(RM) *.o

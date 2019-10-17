
CC	= gcc
CFLAGS	= -ansi -Wall -c
LFLAGS	= -ansi -Wall 


gameboard.o: gameboard.c gameboard.h pieces.h player.h	
	$(CC) $(CFLAGS) gameboard.c -o gameboard.o

pieces.o: pieces.c pieces.h 
	$(CC) $(CFLAGS) pieces.c -o pieces.o

player.o: player.c player.h 
	$(CC) $(CFLAGS) player.c -o player.o

main.o: main.c gameboard.h pieces.h player.h
	$(CC) $(CFLAGS) main.c -o main.o

chess:	main.o gameboard.o pieces.o player.o
	$(CC) $(LFLAGS) gameboard.o pieces.o player.o main.o -o chess 

clean:
	rm -f *.o

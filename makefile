jeu: main.o library.o game.o pile.o
		gcc main.o library.o game.o pile.o -o jeu

main.o: main.c library.h
		gcc -c main.c

library.o: library.c library.h pile.h
		gcc -c library.c

pile.o: pile.c pile.h
	gcc -c pile.c

game.o: game.c library.h
		gcc -c game.c

jeu: main.o library.o game.o
		gcc main.o library.o game.o -o jeu

main.o: main.c library.h
		gcc -c main.c

library.o: library.c library.h
		gcc -c library.c

game.o: game.c library.h
		gcc -c game.c

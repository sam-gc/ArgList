compile: arglist.c arglist.h
	gcc -o arglist.o -c arglist.c

example: arglist.c arglist.h main.c
	gcc -o arglist arglist.c main.c
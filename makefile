compile: arglist.c arglist.h
	gcc -o arglist.o -c arglist.c

example_C: arglist.c arglist.h main.c
	gcc -o arglist arglist.c main.c

example_C++: arglist.c arglist.h main.cpp
	g++ -o arglist++ arglist.c main.cpp -std=c++11

clean:
	rm arglist arglist++ arglist.o

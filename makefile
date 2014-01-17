compile: arglist.c arglist.h
	gcc -o arglist.o -c arglist.c

basic: arglist.c arglist.h examples/basic.c
	gcc -o exBasic arglist.c examples/basic.c

basic++: arglist.c arglist.h examples/basic.cpp
	g++ -o exBasic++ arglist.c examples/basic.cpp -std=c++11

constrained: arglist.c arglist.h examples/constrained.c
	gcc -o exConstrained arglist.c examples/constrained.c

constrained++: arglist.c arglist.h examples/constrained.cpp
	g++ -o exConstrained++ arglist.c examples/constrained.cpp -std=c++11

clean:
	rm exBasic exBasic++ exConstrained exConstrained++ arglist.o

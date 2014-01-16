compile: arglist.c arglist.h
	gcc -o arglist.o -c arglist.c

exBasic_C: arglist.c arglist.h examples/basic.c
	gcc -o exBasic arglist.c examples/basic.c

exBasic_C++: arglist.c arglist.h examples/basic.cpp
	g++ -o exBasic++ arglist.c examples/basic.cpp -std=c++11

exConstrained_C: arglist.c arglist.h examples/constrained.c
	gcc -o exConstrained arglist.c examples/constrained.c

exConstrained_C++: arglist.c arglist.h examples/constrained.cpp
	g++ -o exConstrained++ arglist.c examples/constrained.cpp -std=c++11

clean:
	rm exBasic exBasic++ exConstrained exConstrained++ arglist.o

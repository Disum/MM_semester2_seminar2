program: main.o fun.o
	gcc -o program -Wall main.o fun.o
main.o: main.c fun.h
	gcc -o main.o -Wall -c main.c
fun.o: fun.c fun.h
	gcc -o fun.o -Wall -c fun.c

program_debug: main_debug.o fun_debug.o
	gcc -o program_debug -Wall -g main_debug.o fun_debug.o
main_debug.o: main.c fun.h
	gcc -o main_debug.o -Wall -g -c main.c
fun_debug.o: fun.c fun.h
	gcc -o fun_debug.o -Wall -g -c fun.c

program_optimize: main_optimize.o fun_optimize.o
	gcc -o program_optimize -Wall -O3 main_optimize.o fun_optimize.o
main_optimize.o: main.c fun.h
	gcc -o main_optimize.o -Wall -O3 -c main.c
fun_optimize.o: fun.c fun.h
	gcc -o fun_optimize.o -Wall -O3 -c fun.c

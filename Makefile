#
test : main.o parse.o dictionary.o
	gcc -o test main.o parse.o dictionary.o
main.o : main.c parse.h dictionary.h
	gcc -c main.c
parse.o : parse.c parse.h dictionary.h
	gcc -c parse.c
dictionary.o : dictionary.c dictionary.h
	cc -c dictionary.c

clean :
	rm test main.o parse.o dictionary.o

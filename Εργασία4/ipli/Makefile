ipl: main.o modes.o functions.o vars.o list_line.o 
	gcc -o ipl main.o vars.o functions.o list_line.o modes.o

main.o: main.c
	gcc -c main.c

vars.o: vars.c
	gcc -c vars.c

functions.o: functions.c
	gcc -c functions.c

list_line.o: list_line.c
	gcc -c list_line.c

modes.o: modes.c
	gcc -c modes.c

run: ipl
	./ipl primes.ipl

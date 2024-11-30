OPT = -g -Wall -Wextra -pthread
OBJ = main.o event.o manager.o resource.o system.o

p2: $(OBJ)
	gcc $(OPT) -o p2 $(OBJ)

main.o: main.c defs.h
	gcc $(OPT) -c main.c

event.o: event.c defs.h
	gcc $(OPT) -c event.c

manager.o: manager.c defs.h
	gcc $(OPT) -c manager.c

resource.o: resource.c defs.h
	gcc $(OPT) -c resource.c

system.o: system.c defs.h
	gcc $(OPT) -c system.c

clean:
	rm -f $(OBJ) p2

run: p2
	./p2
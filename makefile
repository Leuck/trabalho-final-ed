CC=gcc
CFLAGS=-Wall -g
DEPS = wowlib.h
OBJ = wowlib.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
wow: TRAB.o $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
run: wow
	./wow
check: wow
	valgrind ./wow < inputs.txt
clean:
	rm -f wow data.wow *.o
love:
	make clean
	make

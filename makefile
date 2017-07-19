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
	cat inputs.txt | ./wow
tests: tests.o $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
clean:
	rm -f wow tests *.o

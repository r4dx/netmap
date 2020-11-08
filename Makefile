CC=gcc
DEPS = *.h
CFLAGS= -Wall -I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o
	$(CC) -o $@ $^ $(CFLAGS)

test: main_test.o
	$(CC) -o $@ $^ $(CFLAGS)
	./test

.PHONY: clean
clean:
	rm -f *.o test

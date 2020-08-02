CC=gcc
DEPS = btree.h
CFLAGS= -Wall -I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

btree: btree.o
	$(CC) -o $@ $^ $(CFLAGS)

test: btree_test.o
	$(CC) -o $@ $^ $(CFLAGS)
	./test

.PHONY: clean
clean:
	rm -f *.o test

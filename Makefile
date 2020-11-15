CC=gcc
DEPS = *.h
CFLAGS= -Wall -I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o async_socket.o fail.o 
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o main

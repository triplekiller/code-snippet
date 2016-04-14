CC = gcc
CFLAGS = -O0 -W -Wall -Wextra -g
OBJ_WRAPPER = wrapper.o

all: malloc.so wrapper

malloc.so: malloc.c
	$(CC) $^ $(CFLAGS) -o $@ -shared -fPIC

wrapper: $(OBJ_WRAPPER)
	$(CC) $^ $(CFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

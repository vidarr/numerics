LN=gcc
CC=gcc
CFLAGS=-std=c11 -g
CFLAGS+=-D_POSIC_C_SOURCE=200809
#CFLAGS+=$(shell pkg-config --cflags libpulse)

LIBS+=-lm

all: bin bin/numerics_test

bin/numerics_test: bin/numerics_test.o bin/numerics.o
	$(LN) -o $@  $^ $(LIBS)

bin/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?


bin:
	mkdir bin

.PHONY: clean

clean:
	rm -rf bin

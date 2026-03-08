CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

BIN := bin/nsort

.PHONY:  all clean

all: $(BIN)

$(BIN): $(OBJ) | bin
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

obj:
	mkdir -p obj

clean:
	rm -rf obj/* bin/*
	touch bin/.keep obj/.keep


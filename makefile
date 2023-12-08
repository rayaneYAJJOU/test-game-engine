SRC_DIR := src
SUB_DIRS := $(wildcard $(SRC_DIR)/*/)
SRC_FILES := $(wildcard $(addsuffix *.c,$(SUB_DIRS))) src/game.c main.c

all: main

main: $(SRC_FILES)
	gcc -o $@ $^ -lmingw32 -lSDL2main -lSDL2

clean:
	rm -f main
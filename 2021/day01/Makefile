CC=gcc
LIB_INC_DIR=/home/avery/misc/advent_of_code/2021/lib/inc
LIB_SRC_DIR=/home/avery/misc/advent_of_code/2021/lib/src
CFLAGS=-I$(LIB_INC_DIR)


part1: src/part1.c
	$(CC) -o bin/part1 src/part1.c $(LIB_SRC_DIR)/*

part2: src/part2.c
	$(CC) -o bin/part2 src/part2.c $(LIB_SRC_DIR)/*

all: part1 part2
	@echo "Done"

clean: bin
	@rm bin/*

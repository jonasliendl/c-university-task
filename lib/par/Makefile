COMPILER = gcc
CFLAGS = -Wall -Wextra -std=c11
BUILD_DIR = bin$(SEP)objects

ifeq ($(OS), WINDOWS_NT)
	SEP = \
	DEL_DIR = rmdir /s /q
else
	SEP = /
	DEL_DIR = rm -rf
endif

.PHONY: run
run:
	mkdir bin
	mkdir bin$(SEP)objects
	gcc -c seq.c -o $(BUILD_DIR)
	gcc -o bin$(SEP)seq $(shell find $(BUILD_DIR) -type f -name '*.o')
	./seq

.PHONY: clean
clean:
	$(DEL_DIR) bin


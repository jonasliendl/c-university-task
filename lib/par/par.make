CFLAGS := -Wall -Wextra -std=c11 -g

SEP := /

SRC_DIRS := ../com ../com/utils

C_FILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

.PHONY: run
run:
	mkdir bin
	gcc -o bin$(SEP)par ./par.c $(C_FILES) $(CFLAGS)
	.$(SEP)bin$(SEP)par

.PHONY: clean
clean:
	rm -rf bin

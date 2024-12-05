CFLAGS := -Wall -Wextra -std=c11 -g

SEP := /

SRC_DIRS := ./com

C_FILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

.PHONY: run
run:
	mkdir bin
	gcc -o bin$(SEP)par ./par/par.c $(C_FILES) $(CFLAGS)
	.$(SEP)bin$(SEP)par

.PHONY: clean
clean:
	rm -rf bin

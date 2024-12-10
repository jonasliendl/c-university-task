CFLAGS := -Wall -Wextra -std=c11 -g

flag := -rf
remove := rm
ifeq ($(OS),Windows_NT)
	remove := rmdir 
	flag := /s /q
endif 

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
	$(remove) $(flag) bin


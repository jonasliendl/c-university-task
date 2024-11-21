CFLAGS := -Wall -Wextra -std=c11 -g

ifeq ($(OS), WINDOWS_NT)
	SEP := \
	DEL_DIR := rmdir /s /q
else
	SEP := /
	DEL_DIR := rm -rf
endif

.DELETE_ON_ERROR:
.PHONY: run
run:
	mkdir bin
	gcc -o bin$(SEP)seq $(shell find ..$(SEP)com -type f -name '*.c') seq.c $(CFLAGS)
	.$(SEP)bin$(SEP)seq

.PHONY: clean
clean:
	$(DEL_DIR) bin

.PHONY: compile
compile:
	mkdir bin
	gcc -o bin$(SEP)seq.out $(shell find ..$(SEP)com -type f -name '*.c') seq.c $(CFLAGS)

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
	mkdir log
	gcc par.c $(shell find ..$(SEP)com -type f -name '*.c') -o bin$(SEP)par $(CFLAGS)
	.$(SEP)bin$(SEP)par

.PHONY: clean
clean:
	$(DEL_DIR) bin
	$(DEL_DIR) log

.PHONY: compile
compile:
	mkdir bin
	gcc par.c $(shell find ..$(SEP)com -type f -name '*.c') -o bin$(SEP)par.out $(CFLAGS)


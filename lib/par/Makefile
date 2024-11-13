CFLAGS := -Wall -Wextra -std=c11

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
	mkdir bin$(SEP)objects
	gcc par.c $(shell find ..$(SEP)com -type f -name '*.c') -o bin$(SEP)par $(CFLAGS)
	.$(SEP)bin$(SEP)par

.PHONY: clean
clean:
	$(DEL_DIR) bin


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
	mkdir log
	gcc -o bin$(SEP)seq $(shell find ..$(SEP)com -type f -name '*.c') seq.c $(CFLAGS)
	.$(SEP)bin$(SEP)seq

.PHONY: clean
clean:
	$(DEL_DIR) bin
	$(DEL_DIR) log


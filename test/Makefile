FUNC_DIR := ..$(SEP)lib$(SEP)com

ifeq ($(OS), WINDOWS_NT)
	SEP := \
	DEL_DIR := rmdir /s /q
else
	SEP := /
	DEL_DIR := rm -rf
endif

.DELETE_ON_ERROR:
.PHONY: test
test:
	mkdir bin
	mkdir bin$(SEP)objects
	gcc -c $(shell find .$(SEP) -type f -name '*.c') $(shell find $(FUNC_DIR) -type f -name '*.c') -o bin$(SEP)objects
	gcc -o bin$(SEP)test $(shell find bin$(SEP)objects -type f -name '*.o')
	.$(SEP)bin$(SEP)test

.PHONY: clean
clean:
	$(DEL_DIR) bin

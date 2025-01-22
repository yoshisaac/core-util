CC=cc
ASM=as
LD=ld

MAKEFLAGS := --jobs=$(shell nproc)

# TODO: Add more warning flags like -Wall and -Wextra
CFLAGS=-O3 -g -static -m32
LDFLAGS=-g -m32

BINARIES=ls cat sh

.PHONY: all clean

#-------------------------------------------------------------------------------

all:	$(BINARIES)

clean:
	rm -f bin/ls
	rm -f bin/cat
	rm -f bin/sh

#-------------------------------------------------------------------------------

$(BINARIES):
	$(CC) $(CFLAGS) -o bin/$@ $@.c $(LDFLAGS)

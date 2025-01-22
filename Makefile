CC=cc
ASM=as
LD=ld

MAKEFLAGS := --jobs=$(shell nproc)

# TODO: Add more warning flags like -Wall and -Wextra
CFLAGS=-O3 -g -static -m32
LDFLAGS=-g -m32

BINARIES=ls cat

.PHONY: all clean

#-------------------------------------------------------------------------------

all:	$(BINARIES)
	$(CC)  -O3 -c -Os -fno-ident -fno-asynchronous-unwind-tables -fno-stack-protector -fomit-frame-pointer -o obj/sh.o sh.c
	$(ASM) syscalls.asm -o obj/syscalls.o
	$(LD)  obj/sh.o obj/syscalls.o -o bin/sh -T custom.ld --strip-all -z noexecstack
clean:
	rm -f bin/ls
	rm -f bin/cat
	rm -f bin/sh

#-------------------------------------------------------------------------------

$(BINARIES):
	$(CC) $(CFLAGS) -o bin/$@ $@.c $(LDFLAGS)

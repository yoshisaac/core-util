CC=cc

MAKEFLAGS := --jobs=$(shell nproc)

# TODO: Add more warning flags like -Wall and -Wextra
CFLAGS=-O3 -g -static
LDFLAGS=-g

SOURCE_FILES=ls.c
BINARIES=ls

.PHONY: all clean

#-------------------------------------------------------------------------------

all: $(BINARIES)

clean:
	rm -f $(BINARIES)

#-------------------------------------------------------------------------------

$(BINARIES): $(SOURCE_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

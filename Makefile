# Makefile for UM test build - Optimized
#
# Last updated: April 21, 2026


############## Variables ###############

CC = gcc # The compiler being used

# Updating include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/build/include -I/usr/sup/cii40/include/cii

# Compile flags
# USE THE O2 COMPILING FLAG FOR OPTIMIZATION
CFLAGS = -g -O2 -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags
LDFLAGS = -g -L/comp/40/build/lib -L/usr/sup/cii40/lib64

# Libraries needed for linking
# cii40 is the Hanson library
LDLIBS = -lcii40

# Collect all .h files
INCLUDES = $(shell echo *.h)

############### Rules ###############

all: um

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

um: main.o um.o segment.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f umtest *.o
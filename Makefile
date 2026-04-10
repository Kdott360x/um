# Makefile for UM test build
#
# This Makefile is intentionally a bit verbose to match the style
# of the sample Comp 40 Makefile.
#
# Last updated: April 6, 2026


############## Variables ###############

CC = gcc # The compiler being used

# Updating include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/build/include -I/usr/sup/cii40/include/cii

# Compile flags
# Set debugging information, allow GNU99,
# max out warnings, and use the updated include path
CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g -L/comp/40/build/lib -L/usr/sup/cii40/lib64

# Libraries needed for linking
# cii40 is the Hanson library
LDLIBS = -lcii40

# Collect all .h files in your directory.
# This way, you can never forget to add
# a local .h file in your dependencies.
INCLUDES = $(shell echo *.h)

############### Rules ###############

all: um


## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@


## Linking step (.o -> executable program)

um: main.o um.o segment.o instructions.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)


clean:
	rm -f umtest *.o
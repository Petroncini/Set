# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

# Source files
SRCS = main.c set.c avl.c rbt.c

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = program

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild from scratch
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild

zip:
	zip -r zip Makefile main.c avl.c avl.h README.md set.c set.h avl_tests/ rbt_tests/


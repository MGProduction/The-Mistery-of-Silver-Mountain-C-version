# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Source and output
SRC = c_silvermountain.c
OUT = bin/c_silvermountain

# Detect OS
UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    # Windows (MinGW or MSVC)
    CFLAGS += -D_CRT_SECURE_NO_WARNINGS
    OUT := bin/c_silvermountain.exe
else ifeq ($(UNAME_S),Darwin)
    # macOS
    CFLAGS += 
else
    # Assume Linux/Unix
    CFLAGS +=
endif

# Default build rule
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Clean rule
clean:
# Compiler Settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c2x -g

# Directories
SRC_DIR = src
EXERCISE_DIR = exercises
PATCH_DIR = patches

# Files
VERIFY_SRC = $(SRC_DIR)/ceilings.c
VERIFY_BIN = ceilings

# Find all exercise source files (e.g., exercises/001.c)
EXERCISE_SRCS := $(wildcard $(EXERCISE_DIR)/*.c)
# Convert source paths to executable paths (removing .c)
EXERCISE_BINS := $(EXERCISE_SRCS:.c=)

# Platform specific tweaks
ifdef OS
   EXT = .exe
else
   EXT = 
endif

all: $(VERIFY_BIN)

$(VERIFY_BIN): $(VERIFY_SRC)
	$(CC) $(CFLAGS) -o $(VERIFY_BIN)$(EXT) $(VERIFY_SRC)

# Rule to compile any exercise directly (e.g., make exercises/001_stdio)
# This allows the verification tool to call "make exercises/001_stdio"
$(EXERCISE_DIR)/%: $(EXERCISE_DIR)/%.c
	$(CC) $(CFLAGS) -o $@$(EXT) $< -lm

# utility for checking everything)
exercises: $(EXERCISE_BINS)

clean:
	rm -f $(VERIFY_BIN)$(EXT)

.PHONY: all clean exercises

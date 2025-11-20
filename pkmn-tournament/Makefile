# --- Configuration ---
TARGET := app
CC := gcc

# 1. Define Raylib Paths (Apple Silicon / Homebrew)
RAYLIB_INC_PATH := /opt/homebrew/include
RAYLIB_LIB_PATH := /opt/homebrew/lib

# 2. Compiler Flags (CFLAGS)
# Added: -I for Raylib, -arch arm64 for Apple Silicon
CFLAGS := -Wall -Wextra -Wpedantic -std=c99 \
          -Wunused -Wuninitialized -Wmissing-prototypes \
          -Wstrict-prototypes -Wimplicit-function-declaration \
          -Wreturn-type -Wshadow -Wpointer-arith \
          -Wcast-qual -Wwrite-strings \
          -arch arm64 \
          -I$(RAYLIB_INC_PATH)

# 3. Linker Flags (LDFLAGS)
# Added: -L for Raylib path, -lraylib, macOS Frameworks, -arch arm64
LDFLAGS := -L$(RAYLIB_LIB_PATH) \
           -lraylib \
           -framework CoreVideo \
           -framework IOKit \
           -framework Cocoa \
           -framework GLUT \
           -framework OpenGL \
           -arch arm64

# --- Directory Setup ---
SRC_DIR := src
OBJ_DIR := obj

# --- Source and Object Discovery ---

# Recursively find all .c files in src/
SOURCES := $(shell find $(SRC_DIR) -name "*.c")

# Convert source file list to object file list
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# --- Include Paths ---

# Find all unique directories containing headers in your src folder
# and add them to the include path
INCLUDE_DIRS := $(sort $(dir $(shell find $(SRC_DIR) -name "*.h")))
CFLAGS += $(patsubst %,-I%,$(INCLUDE_DIRS))

# --- Targets ---

.PHONY: all run clean

all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJECTS)
	@echo "Linking $@"
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

# Rule to compile each .c file into a .o file
# Uses mkdir -p to ensure the directory exists before compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Target to run the compiled executable
run: $(TARGET)
	@echo "Running $(TARGET)..."
	./$(TARGET)

# Target to clean up generated files
clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET)
	@rm -rf $(OBJ_DIR)
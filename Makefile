# Define the C compiler (Clang is the default on macOS)
CC = clang

# Source files (all .c files in the src/ directory)
SRCS = $(wildcard src/*.c src/*/*.c)

# Object files directory
OBJ_DIR = build/obj
OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# The above assumes all .c files are directly under src/ or one level deep.
# If you have deeper nested files, you might need to adjust SRCS and OBJS.

# Output executable name
TARGET = build/bin/c_game

# Raylib include and library paths (Homebrew default locations)
# Adjust these if your Homebrew prefix is different (e.g., /opt/homebrew for Apple Silicon)
# You can check your Homebrew prefix with `brew --prefix`
# For Apple Silicon (M1/M2/M3), use:
RAYLIB_INC_PATH = /opt/homebrew/include
RAYLIB_LIB_PATH = /opt/homebrew/lib

# Compiler flags for compilation (.c to .o)
# -I: Include path for header files
# -std=c11: C standard to use (Raylib is compatible with C99/C11)
# -Wall -Wextra: Enable common warnings
# -arch arm64: Explicitly compile for arm64 architecture (good practice on Apple Silicon)
CFLAGS = -I$(RAYLIB_INC_PATH) -std=c11 -Wall -Wextra -arch arm64

# Linker flags for linking (.o to executable)
# -L: Library path for library files
# -lraylib: Link against the raylib library (libraylib.a or libraylib.dylib)
# -frameworks: Required for macOS graphics/windowing (CoreVideo, IOKit, Cocoa, OpenGL)
# -arch arm64: Explicitly link for arm64 architecture
LDFLAGS = -L$(RAYLIB_LIB_PATH) -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL -arch arm64

.PHONY: all clean run

all: $(TARGET)

# Rule to create object files from source files (for single level)
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D) # Create directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create sub-directory object files (for one nested level)
$(OBJ_DIR)/%/*.o: src/%/*.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(@D) # Create directory if it doesn't exist
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET) # Pass $(LDFLAGS) here

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	$(TARGET)
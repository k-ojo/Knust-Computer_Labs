CC := gcc
CFLAGS := -Wall -Wextra -g
LIBS := -lm

SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build
TARGET := $(BIN_DIR)/khash# Define the final executable name

# Ensure directories exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Get all source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Generate object file names in build/
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default target: Compile and link all
all: dir $(TARGET)

# Compile each .c file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link all object files into a single executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

# Ensure build and bin directories exist
dir: $(BUILD_DIR) $(BIN_DIR)


run: 
	"./$(TARGET)"

.PHONY: dir clean all

# Clean build and bin directories
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

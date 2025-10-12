# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -O2

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Target executable
TARGET := $(BIN_DIR)/app

# Find all .cpp files in src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Create corresponding .o files in build/
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Default rule
all: $(TARGET)

# Link object files into the final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

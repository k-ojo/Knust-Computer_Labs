CC = gcc
CFLAGS = -Wall -Wextra
DFLAGS = -g  # Debug flags
RFLAGS = -O2  # Optimization for release
SRC_DIR = src
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
TARGET = $(BUILD_DIR)/Iceshop
PREFIX = /usr/local/bin

all: release  # Default build is release

release: CFLAGS += $(RFLAGS)
release: $(TARGET)

debug: CFLAGS += $(DFLAGS)
debug: $(TARGET)

$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

install: release
	sudo install -m 755 $(TARGET) $(PREFIX)

uninstall:
	sudo rm -f $(PREFIX)/Iceshop

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

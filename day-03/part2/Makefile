CC = gcc
CFLAGS = -I../include -fsanitize=address -fsanitize=undefined -static-libasan -g

BUILD_DIR = ../../build
TARGET_EXEC = d3p2

$(BUILD_DIR)/$(TARGET_EXEC): main.c ../common/engine.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $?

clean:
	rm -f $(BUILD_DIR)/$(TARGET_EXEC)
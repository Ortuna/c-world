SRC_DIR   := "src"
BUILD_DIR := "build"
SOURCES   := $(shell find $(SRC_DIR) -type f -name "*.c")

.PHONY: all clean src/*

$(SOURCES): SRC_FILE = $(shell echo $@ | sed "s#$(SRC_DIR)/##g")
$(SOURCES):
	$(CC) $(CFLAGS) $@ -o ./build/$(SRC_FILE).o

clean:
	-rm ./build/*
	
	

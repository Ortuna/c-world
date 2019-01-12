SRC     := src
BUILD   := build
SOURCES := $(shell find $(SRC) -type f -name "*.c")

CFLAGS = -Wall -I src -lm

.PHONY: clean $(SOURCES)

$(SOURCES):
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) -o $(BUILD)/c-world

run:
	./build/c-world

clean:
	-rm -r ./$(BUILD)/*


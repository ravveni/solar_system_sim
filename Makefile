CC = gcc
CFLAGS = -std=c99 -I./include -Wall
LDFLAGS = -L./lib -lraylib -rpath ./lib

SRC_DIR = src
BIN_DIR = bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))

EXECUTABLE = solar-system-sim

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all:
	make clean; make; ./$(EXECUTABLE)

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)

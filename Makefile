CC = gcc
CFLAGS = -std=c17 -I./raylib/include -Wall
LDFLAGS = -L./raylib/lib -lraylib

SRC_DIR = src
BIN_DIR = bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))

EXECUTABLE = simulation

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all:
	make clean; make; ./$(EXECUTABLE)

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)

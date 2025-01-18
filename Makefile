CC = g++
CFLAGS = -std=c++11 -I./include -Wall
LDFLAGS = -L./lib -lraylib -rpath ./lib

SRC_DIR = src
BIN_DIR = bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(SRC_FILES))

EXECUTABLE = raytest

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all:
	make clean; make; ./$(EXECUTABLE)

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)

CC = g++
CFLAGS= -Wall -O2 -std=c++11
LDFLAGS = 
EXEC = $(BUILD_DIR)/paralGen

SRC = 	main.cpp\
		itemSet.cpp

OBJ_DIR = ./obj
SRC_DIR = ./src
BIN_DIR = ./bin
BUILD_DIR = ./build
INC_DIR = ./include

OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	
$(OBJ_DIR)/itemSet.o: $(SRC_DIR)/itemSet.cpp
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/itemSet.h

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -f $(OBJ_DIR)/*.o

mrproper: clean
	rm -f $(EXEC)
	

CC = g++
CFLAGS= -Wall -O2 -std=c++11
LDFLAGS = 
EXEC = $(BUILD_DIR)/paralGen

SRC =	main.cpp	\
	itemSet.cpp	\
	dataSet.cpp 	\
	individual.cpp	\
	geneticAlgo.cpp

OBJ_DIR = ./obj
SRC_DIR = ./src
BUILD_DIR = ./build
INC_DIR = ./include

OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	


$(OBJ_DIR)/main.o: $(INC_DIR)/dataSet.h 
$(OBJ_DIR)/dataSet.o: $(INC_DIR)/itemSet.h
$(OBJ_DIR)/geneticAlgo.o : $(INC_DIR)/individual.h

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -f $(OBJ_DIR)/*.o

mrproper: clean
	rm -f $(EXEC)
	
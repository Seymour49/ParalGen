CC = g++
CFLAGS= -Wall -O2 -std=c++11
LDFLAGS = 
EXEC = $(BUILD_DIR)/paralGen

SRC =	main.cpp		\
	freqEval.cpp		\
	evaluate.cpp		\
	randomMutator.cpp	\
	mutator.cpp		\
	uniformCross.cpp	\
	multiPointCross.cpp 	\
	classicCross.cpp 	\
	cross.cpp		\
	itemSetC.cpp		\
	itemSet.cpp		\
	dataSet.cpp 		\
	dataSetC.cpp		\
	individual.cpp		\
	geneticAlgo.cpp		\
	geneticAlgoC.cpp

OBJ_DIR = ./obj
SRC_DIR = ./src
BUILD_DIR = ./build
INC_DIR = ./include

OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	

$(OBJ_DIR)/main.o: $(INC_DIR)/dataSet.h $(INC_DIR)/dataSetC.h $(INC_DIR)/cross.h $(INC_DIR)/classicCross.h $(INC_DIR)/multiPointCross.h $(INC_DIR)/uniformCross.h $(INC_DIR)/geneticAlgoC.h
$(OBJ_DIR)/freqEval.o: $(INC_DIR)/evaluate.h
$(OBJ_DIR)/evaluate.o: $(INC_DIR)/itemSet.h $(INC_DIR)/itemSetC.h $(INC_DIR)/dataSet.h $(INC_DIR)/dataSetC.h
$(OBJ_DIR)/randomMutator.o: $(INC_DIR)/randomMutator.h $(INC_DIR)/mutator.h $(INC_DIR)/itemSet.h $(INC_DIR)/itemSetC.h
$(OBJ_DIR)/mutator.o: $(INC_DIR)/mutator.h $(INC_DIR)/individual.h $(INC_DIR)/itemSet.h $(INC_DIR)/itemSetC.h
$(OBJ_DIR)/uniformCross.o: $(INC_DIR)/uniformCross.h $(INC_DIR)/cross.h $(INC_DIR)/itemSet.h $(INC_DIR)/itemSetC.h
$(OBJ_DIR)/multiPointCross.o: $(INC_DIR)/multiPointCross.h $(INC_DIR)/cross.h $(INC_DIR)/itemSet.h $(INC_DIR)/itemSetC.h
$(OBJ_DIR)/classicCross.o: $(INC_DIR)/classicCross.h $(INC_DIR)/cross.h $(INC_DIR)/itemSet.h $(INC_DIR)/itemSetC.h
$(OBJ_DIR)/cross.o: $(INC_DIR)/cross.h $(INC_DIR)/individual.h $(INC_DIR)/itemSet.h $(INC_DIR)/itemSetC.h
$(OBJ_DIR)/itemSetC.o: $(INC_DIR)/itemSetC.h $(INC_DIR)/individual.h 
$(OBJ_DIR)/itemSet.o: $(INC_DIR)/itemSet.h $(INC_DIR)/individual.h 
$(OBJ_DIR)/dataSet.o: $(INC_DIR)/dataSet.h $(INC_DIR)/itemSet.h 
$(OBJ_DIR)/dataSetC.o: $(INC_DIR)/dataSetC.h $(INC_DIR)/itemSetC.h 
$(OBJ_DIR)/geneticAlgo.o : $(INC_DIR)/geneticAlgo.h $(INC_DIR)/individual.h $(INC_DIR)/dataSet.h $(INC_DIR)/randomMutator.h $(INC_DIR)/uniformCross.h $(INC_DIR)/multiPointCross.h $(INC_DIR)/classicCross.h
$(OBJ_DIR)/geneticAlgoC.o : $(INC_DIR)/geneticAlgoC.h $(INC_DIR)/individual.h $(INC_DIR)/dataSetC.h

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -f $(OBJ_DIR)/*.o

mrproper: clean
	rm -f $(EXEC)
	

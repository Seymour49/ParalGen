CC = g++
CFLAGS= -Wall -O2 -std=c++11 -ggdb
LDFLAGS = 
EXEC = $(BUILD_DIR)/paralGen

SRC =	main.cpp		\
	irandomPop.cpp		\
	randomPop.cpp		\
	freqPop.cpp		\
	initPop.cpp		\
	closeEval.cpp		\
	freqEval.cpp		\
	evaluate.cpp		\
	randomMutator.cpp	\
	mutator.cpp		\
	uniformCross.cpp	\
	multiPointCross.cpp 	\
	classicCross.cpp 	\
	cross.cpp		\
	itemSet.cpp		\
	itemSetO.cpp		\
	dataSet.cpp 		\
	dataSetO.cpp		\
	individual.cpp		\
	geneticAlgo.cpp		\
	initPop.cpp		\
	randomPop.cpp		\
	freqPop.cpp		\
	charDataSet.cpp		\
	charDataSetO.cpp	\
	selectPolicy.cpp	\
	indelPolicy.cpp		\
	ageIDPolicy.cpp		\
	fitnessIDPolicy.cpp	\
	tournamentSelect.cpp	\
	bestSelect.cpp		\
	randomSelect.cpp	\
	closeEval.cpp
    

OBJ_DIR = ./obj
SRC_DIR = ./src
BUILD_DIR = ./build
INC_DIR = ./include

OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/main.o: $(INC_DIR)/dataSet.h $(INC_DIR)/dataSetO.h $(INC_DIR)/cross.h $(INC_DIR)/classicCross.h $(INC_DIR)/multiPointCross.h $(INC_DIR)/uniformCross.h $(INC_DIR)/geneticAlgo.h $(INC_DIR)/randomMutator.h $(INC_DIR)/freqEval.h $(INC_DIR)/randomPop.h $(INC_DIR)/freqPop.h $(INC_DIR)/irandomPop.h
$(OBJ_DIR)/freqEval.o: $(INC_DIR)/freqEval.h $(INC_DIR)/evaluate.h $(INC_DIR)/dataSet.h $(INC_DIR)/dataSetO.h
$(OBJ_DIR)/evaluate.o: $(INC_DIR)/evaluate.h $(INC_DIR)/individual.h
$(OBJ_DIR)/randomMutator.o: $(INC_DIR)/randomMutator.h $(INC_DIR)/mutator.h
$(OBJ_DIR)/mutator.o: $(INC_DIR)/mutator.h $(INC_DIR)/individual.h
$(OBJ_DIR)/uniformCross.o: $(INC_DIR)/uniformCross.h $(INC_DIR)/cross.h
$(OBJ_DIR)/multiPointCross.o: $(INC_DIR)/multiPointCross.h $(INC_DIR)/cross.h
$(OBJ_DIR)/classicCross.o: $(INC_DIR)/classicCross.h $(INC_DIR)/cross.h
$(OBJ_DIR)/cross.o: $(INC_DIR)/cross.h $(INC_DIR)/individual.h
$(OBJ_DIR)/itemSet.o: $(INC_DIR)/itemSet.h $(INC_DIR)/individual.h
$(OBJ_DIR)/itemSetO.o: $(INC_DIR)/itemSetO.h $(INC_DIR)/individual.h
$(OBJ_DIR)/dataSet.o: $(INC_DIR)/dataSet.h
$(OBJ_DIR)/dataSetO.o: $(INC_DIR)/dataSetO.h
$(OBJ_DIR)/individual.o: $(INC_DIR)/individual.h
$(OBJ_DIR)/geneticAlgo.o : $(INC_DIR)/geneticAlgo.h $(INC_DIR)/individual.h $(INC_DIR)/itemSet.h $(INC_DIR)/itemSetO.h $(INC_DIR)/mutator.h $(INC_DIR)/cross.h $(INC_DIR)/evaluate.h $(INC_DIR)/initPop.h
$(OBJ_DIR)/initPop.o : $(INC_DIR)/initPop.h $(INC_DIR)/individual.h
$(OBJ_DIR)/irandomPop.o: $(INC_DIR)/irandomPop.h $(INC_DIR)/initPop.h 
$(OBJ_DIR)/randomPop.o : $(INC_DIR)/randomPop.h $(INC_DIR)/initPop.h
$(OBJ_DIR)/freqPop.o : $(INC_DIR)/freqPop.h $(INC_DIR)/initPop.h $(INC_DIR)/dataSet.h $(INC_DIR)/dataSetO.h
$(OBJ_DIR)/charDataSet.o : $(INC_DIR)/charDataSet.h $(INC_DIR)/dataSet.h 
$(OBJ_DIR)/charDataSetO.o : $(INC_DIR)/charDataSetO.h $(INC_DIR)/dataSetO.h
$(OBJ_DIR)/selectPolicy.o: $(INC_DIR)/selectPolicy.h $(INC_DIR)/individual.h
$(OBJ_DIR)/indelPolicy.o: $(INC_DIR)/indelPolicy.h $(INC_DIR)/individual.h
$(OBJ_DIR)/ageIDPolicy.o: $(INC_DIR)/ageIDPolicy.h $(INC_DIR)/indelPolicy.h
$(OBJ_DIR)/fitnessIDPolicy.o: $(INC_DIR)/fitnessIDPolicy.h $(INC_DIR)/indelPolicy.h
$(OBJ_DIR)/tournamentSelect.o: $(INC_DIR)/tournamentSelect.h $(INC_DIR)/selectPolicy.h
$(OBJ_DIR)/bestSelect.o: $(INC_DIR)/bestSelect.h $(INC_DIR)/selectPolicy.h
$(OBJ_DIR)/randomSelect.o: $(INC_DIR)/randomSelect.h $(INC_DIR)/selectPolicy.h
$(OBJ_DIR)/closeEval.o: $(INC_DIR)/closeEval.h $(INC_DIR)/evaluate.h



$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
clean:
	rm -f $(OBJ_DIR)/*.o

mrproper: clean
	rm -f $(EXEC)
	

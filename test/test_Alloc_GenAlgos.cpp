
#include <iostream>

#include "../include/dataSet.h"
#include "../include/itemSet.h"
#include "../include/itemSetC.h"
#include "../include/dataSetC.h"
#include "../include/classicCross.h"
#include "../include/multiPointCross.h"
#include "../include/uniformCross.h"
#include "../include/randomMutator.h"
#include "../include/geneticAlgo.h"
#include "../include/geneticAlgoC.h"
#include "../include/freqEval.h"

using namespace std;

int main(int argc, char **argv) {

    srand(time(NULL));
    
    DataSet* data = new DataSet();
    data->loadFile("./data/mushroom.dat");
    
    DataSetC* dataC = new DataSetC();
    dataC->loadFile("./data/mushroom.dat");
    
    RandomMutator* mut = new RandomMutator();
    ClassicCross* cross = new ClassicCross((int)(data->getNbCol()/2)-1);
    FreqEval* eval = new FreqEval();
    
    GeneticAlgo gen(1000,10,0.3,mut,cross,eval);
    GeneticAlgo* gen2 = new GeneticAlgo(1000,10,0.3,mut,cross,eval);
    gen.setData(data);
    gen2->setData(data);
    gen.initRandomPop();
    gen2->setData(data);
    gen.displayPopulation();
    gen2->displayPopulation();
    cout << "====================================" << endl;
    cout << "====================================" << endl;
    cout << "====================================" << endl;
    GeneticAlgoC genC(1000,10,0.3,mut,cross,eval);
    GeneticAlgoC* genC2 = new GeneticAlgoC(1000,10,0.3,mut,cross,eval);
    genC.setData(dataC);
    genC2->setData(dataC);
    genC.initRandomPop();
    genC2->initRandomPop();
    genC.displayPopulation();
    genC2->displayPopulation();
    
    delete mut; delete cross; delete eval;
    delete data; delete dataC;
    delete gen2; delete genC2;
  return 0;
}

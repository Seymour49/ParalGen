
#include <iostream>

#include "../include/dataSet.h"
#include "../include/dataSetC.h"
#include "../include/classicCross.h"
#include "../include/multiPointCross.h"
#include "../include/uniformCross.h"
#include "../include/randomMutator.h"
#include "../include/freqEval.h"
#include "../include/freqPop.h"
#include "../include/randomPop.h"
#include "../include/geneticAlgo.h"
#include "../include/geneticAlgoC.h"

using namespace std;

int main(int argc, char **argv) {

    srand(time(NULL));
    cout << "====================================" << endl;
    cout << "=  DEBUT DES TESTS INITIALISATION  =" << endl;
    cout << "====================================" << endl;
    DataSetC* dataC = new DataSetC();
    dataC->loadFile("./data/mushroom.dat");
    
    RandomMutator* mut = new RandomMutator();
    ClassicCross* cross = new ClassicCross((int)(dataC->getNbCol()/2)-1);
    FreqEval* eval = new FreqEval();
    FreqPop* pop = new FreqPop(dataC);
    GeneticAlgoC* genC = new GeneticAlgoC(1000,10,0.3,mut,cross,eval,pop);
    cout << "====================================" << endl;
    cout << "==  DEBUT DES TESTS SUR METHODES  ==" << endl;
    cout << "====================================" << endl;
    genC->setData(dataC);
    
    cout << "**** Init Pop ****" << endl;
    genC->initPop();
    cout << "**** Eval Pop ****" << endl;
    genC->EvalPop();
    cout << "**** Display Pop ****" << endl;
    genC->displayPopulation();
    
    cout << "**** Display Ind 0 ****" << endl;
    genC->displayPopulationAt(0);
    
    cout << "**** Mut Ind 0 ****" << endl;
    genC->doMutation(0);
    cout << "**** Display Ind 0 ****" << endl;
    genC->displayPopulationAt(0);
    
    
    cout << "delete mut" << endl;
    delete mut; 
    cout << "delete cross" << endl;
    delete cross;
    cout << "delete eval" << endl;
    delete eval; 
    cout << "delete pop" << endl;
    delete pop;
    cout << "delete dataC" << endl;
    delete dataC;
    cout << "delete genC" << endl;
    delete genC;
  return 0;
}

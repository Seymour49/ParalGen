
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
    cout << "=     DEBUT DES TESTS ALGOGENC     =" << endl;
    cout << "====================================" << endl;
    cout << "====================================" << endl;
    cout << "=  DEBUT DES TESTS INITIALISATION  =" << endl;
    cout << "====================================" << endl;
    DataSetC* dataC = new DataSetC();
    dataC->loadFile("./data/mushroom.dat");
    
    RandomMutator* mut = new RandomMutator();
    ClassicCross* cross = new ClassicCross((int)(dataC->getNbCol()/2)-1);
    FreqEval* eval = new FreqEval();
    FreqPop* pop = new FreqPop(dataC);
    RandomPop* pop1 = new RandomPop(dataC->getNbCol(),0.05);
    
    GeneticAlgoC* genC = new GeneticAlgoC(1000,10,0.3,mut,cross,eval,pop);
    cout << "====================================" << endl;
    cout << "==  DEBUT DES TESTS SUR METHODES  ==" << endl;
    cout << "====================================" << endl;
    genC->setData(dataC);
    
    cout << "**** Init Pop ****" << endl;
    genC->initPop();
    cout << "**** Eval Pop ****" << endl;
    genC->EvalPop();
    cout << "**** incAge Pop ****" << endl;
    genC->incAgePop();
    cout << "**** Display Pop ****" << endl;
    genC->displayPopulation();
    
    cout << "**** Display Ind 0 ****" << endl;
    genC->displayPopulationAt(0);
    
    cout << "**** Mut Ind 0 ****" << endl;
    genC->doMutation(0);
    cout << "**** Display Ind 0 ****" << endl;
    genC->displayPopulationAt(0);
    
    cout << "====================================" << endl;
    cout << "=     DEBUT DES TESTS ALGOGEN      =" << endl;
    cout << "====================================" << endl;
    cout << "====================================" << endl;
    cout << "=  DEBUT DES TESTS INITIALISATION  =" << endl;
    cout << "====================================" << endl; 
    DataSet* data = new DataSet();
    data->loadFile("./data/mushroom.dat");
    
    GeneticAlgo* gen = new GeneticAlgo(1000,10,0.3,mut,cross,eval,pop1);
    cout << "====================================" << endl;
    cout << "==  DEBUT DES TESTS SUR METHODES  ==" << endl;
    cout << "====================================" << endl;
    gen->setData(data);
    
    cout << "**** Init Pop ****" << endl;
    gen->initPop();
    cout << "**** Eval Pop ****" << endl;
    gen->EvalPop();
    cout << "**** Inc Age Pop ****" << endl;
    gen->incAgePop();
    cout << "**** Display Pop ****" << endl;
    gen->displayPopulation();
    
    cout << "**** Display Ind 0 ****" << endl;
    gen->displayPopulationAt(0);
    
    cout << "**** Mut Ind 0 ****" << endl;
    gen->doMutation(0);
    cout << "**** Display Ind 0 ****" << endl;
    gen->displayPopulationAt(0);
    cout << "**** Cross 1&&2 ****" << endl;
    gen->displayPopulationAt(1);
    gen->displayPopulationAt(2);
    gen->doCrossFor(1,2);
    cout << "delete mut" << endl;
    delete mut; 
    cout << "delete cross" << endl;
    delete cross;
    cout << "delete eval" << endl;
    delete eval; 
    cout << "delete pop" << endl;
    delete pop;
    cout << "delete pop1" << endl;
    delete pop1;    
    cout << "delete dataC" << endl;
    delete dataC;
    cout << "delete genC" << endl;
    delete genC;
    cout << "delete data" << endl;
    delete data;
    cout << "delete gen" << endl;
    delete gen;
    
  return 0;
}

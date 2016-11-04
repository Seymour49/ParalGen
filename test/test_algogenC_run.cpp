
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
    DataSetC* dataC = new DataSetC();
    dataC->loadFile("./data/mushroom.dat");
    
    RandomMutator* mut = new RandomMutator();
    size_t* pivots = new size_t[3];
    pivots[0] = 25; pivots[1] = 50; pivots[2] = 75;
//     MultiPointCross* cross = new MultiPointCross(pivots,3);
    ClassicCross* cross = new ClassicCross((int)(dataC->getNbCol()/2)-1);
//     UniformCross* cross = new UniformCross();
    FreqEval* eval = new FreqEval();
    FreqPop* pop = new FreqPop(dataC);
    
    RandomPop* pop1 = new RandomPop(dataC->getNbCol(),0.05);
    
    GeneticAlgoC* genC = new GeneticAlgoC(5,10,0.3,mut,cross,eval,pop);
    cout << "====================================" << endl;
    cout << "============  DEBUT RUN  ===========" << endl;
    cout << "====================================" << endl;
    genC->setData(dataC);

    genC->run();
    
    
    genC->displayPopulation();
    cout << "====================================" << endl;
    cout << "=============  FIN RUN  ============" << endl;
    cout << "====================================" << endl;
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
    delete[] pivots;
    
  return 0;
}

#include <iostream>

#include "../include/dataSet.h"
#include "../include/itemSet.h"
#include "../include/geneticAlgo.h"

using namespace std;

int main(int argc, char **argv) {
   
    DataSet* data = new DataSet();
    data->loadFile("./data/mushroom.dat");

    cout << "Nombre d'items : " << data->getNbCol() << endl;
    GeneticAlgo gen(10000,10);
    gen.setData(data);
    
    cout << "Items dans gen : " << gen.getDataSet()->getNbCol() << endl;
    gen.initRandomPop();
    
    
    gen.displayPopulation();
  
  return 0;
}

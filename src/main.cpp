
#include <iostream>

#include "../include/dataSet.h"
#include "../include/itemSet.h"
#include "../include/itemSetC.h"
#include "../include/dataSetC.h"
#include "../include/geneticAlgo.h"

using namespace std;

int main(int argc, char **argv) {

    
    
    DataSetC data1;
    
    data1.loadFile("./data/mushroom.dat");
    
    char * v = data1.getData()[0];
    
    ItemSetC a(v, data1.getNbCol());
    
    v = data1.getData()[1];
    
    ItemSetC b(v, data1.getNbCol());
    
    ItemSetC res = a.CrossUniform(b);
    
    
    cout << endl << a << endl << endl << b << endl << endl << res << endl;

  return 0;
}

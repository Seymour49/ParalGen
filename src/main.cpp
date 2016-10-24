
#include <iostream>

#include "../include/dataSet.h"
#include "../include/itemSet.h"
#include "../include/itemSetC.h"
#include "../include/dataSetC.h"
#include "../include/geneticAlgo.h"

using namespace std;

int main(int argc, char **argv) {
    /*
    DataSet* data = new DataSet();
    data->loadFile("./data/mushroom.dat");
    
    cout << "Nombre d'items : " << data->getNbCol() << endl;
    GeneticAlgo gen(10000,10);
    gen.setData(data);
    
    cout << "Items dans gen : " << gen.getDataSet()->getNbCol() << endl;
    gen.initRandomPop();
    
    
    gen.displayPopulation();
    */
    
    /*char* tmp = new char[15];
    for(int i=0; i < 15; ++i){
	tmp[i] = '1';
    }
    
    
    cout << "Allocation statique" << endl;
    
    cout << "Constructeur par défaut" << endl;
    ItemSetC it;
    cout << it;
    cout << "Jusqu'ici tout va bien." << endl;
    
    cout << "Constructeur avec char*" << endl;
    ItemSetC it2(tmp,15);
    cout << it2;
    cout << "Jusqu'ici tout va bien." << endl;
    
    cout << "Constructeur par recopie" << endl;
    ItemSetC it3(it2);
    cout << it3;    
    
    cout << "Jusqu'ici tout va bien." << endl;
    
    cout << "Allocation dynamique" << endl;
    cout << "Constructeur par défaut" << endl;
    ItemSetC *dit = new ItemSetC();
    
    cout << *dit;
    cout << "Jusqu'ici tout va bien." << endl;
    cout << "Constructeur par liste d'initialisation" << endl;
    ItemSetC *dit2 = new ItemSetC(tmp,15);
    cout << *dit2;

    cout << "Jusqu'ici tout va bien." << endl;    
    
    cout << "Constructeur par recopie" << endl;
    ItemSetC *dit3 = new ItemSetC(*dit2);
    cout << *dit3;
    cout << "Jusqu'ici tout va bien." << endl; 
    
    dit2->Mutate();
    cout << *dit2 << *dit3;
    
    delete dit; delete dit2; delete dit3; delete[] tmp;*/
    /*
    */
    
    
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

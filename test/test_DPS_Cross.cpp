
#include <iostream>

#include "../include/dataSet.h"
#include "../include/itemSet.h"
#include "../include/itemSetC.h"
#include "../include/dataSetC.h"
#include "../include/classicCross.h"
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
    
    delete data;
    */
    srand(time(NULL));
    char* tmp = new char[15];
    vector<char> vtmp, vtmp2;
    int alea = 0;
    for(int i=0; i < 15; ++i){
	alea = rand() % 100;
	if( alea < 50){
	  tmp[i] = '1';
	  vtmp.push_back('1');
	}else{
	  tmp[i] = '0';
	  vtmp.push_back('0');
	}
    }	
    char* tmp2 = new char[15];

    for(int i=0; i < 15; ++i){
	alea = rand() % 100;
	if( alea < 50){
	  vtmp2.push_back('1');
	  tmp2[i] = '1';
	}else{
	  tmp2[i] = '0';
	  vtmp2.push_back('0');
	}
    }    
    
    
    cout << "Itemset via vector" << endl;
    cout << "Allocation statique" << endl;
    ItemSet it(vtmp);
    ItemSet it2(vtmp2);
    cout << it << it2;
    
    cout << "Alloccation dynamique" << endl;
    ItemSet* dit = new ItemSet(vtmp);
    ItemSet* dit2= new ItemSet(vtmp2);
    cout << *dit << *dit2;
    
    cout << "ItemsetC via char*" << endl;
    cout << "Allocation statique" << endl;
    ItemSetC itc(tmp,15);
    ItemSetC itc2(tmp2,15);
    cout << itc << itc2;

    cout << "Allocation dynamique" << endl;
    ItemSetC *ditc = new ItemSetC(tmp,15);
    ItemSetC *ditc2 = new ItemSetC(tmp2,15);
    cout << *ditc << *ditc2;
    
    size_t pivot = 7;
    ClassicCross* tcross = new ClassicCross(pivot);
    
    ItemSetC* child = tcross->execute(ditc,ditc2);
    cout << "Enfant du croisement de ditc, ditc2" << endl;
    cout << *child;
    
    cout << "Jusqu'ici tout va bien" << endl;
    
    ItemSet* child2 = tcross->execute(dit, dit2);
    cout << "Enfant du croisement de itc, itc2" << endl;
    cout << *child2;
    
    delete tcross;
    delete child2; delete child;
    delete dit; delete dit2; delete ditc; delete ditc2;
    delete[] tmp; delete[] tmp2;
    
    /*
    */
  return 0;
}

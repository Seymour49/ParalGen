
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

using namespace std;

int main(int argc, char **argv) {
    /*
    DataSet* data = new DataSet();
    data->loadFile("./data/mushroom.dat");
    
    cout << "Nombre d'items : " << data->getNbCol() << endl;
    GeneticAlgo gen(10000,20);
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
    
    cout << "Alloccation dynamique" << endl;
    ItemSet* dit = new ItemSet(vtmp);
    ItemSet* dit2= new ItemSet(vtmp2);
    cout << "======DIT======"<< endl <<  *dit	
         << "======DIT2=====" << endl<< *dit2;
	 
    cout << "Allocation dynamique" << endl;
    ItemSetC *ditc = new ItemSetC(tmp,15);
    ItemSetC *ditc2 = new ItemSetC(tmp2,15);
    cout << "======DITC======"<< endl <<  *ditc
         << "======DITC2=====" << endl<< *ditc2;
    
    cout << "=================================" << endl ;
    cout << "	Tests sur randomMutator"	<< endl;
    cout << "=================================" << endl ;
    RandomMutator* mutator = new RandomMutator();
    cout << "Création ok" << endl;
    
    cout << "randomMutator sur ItemSet" << endl;
    ItemSet* mchild1 = mutator->execute(dit);
    cout << "Parent : ";
    for(unsigned i=0; i < dit->getSize(); ++i)
      cout << dit->getBitset()[i] << " ";
    cout << endl << "Enfant : ";
    for(unsigned i=0; i < mchild1->getSize(); ++i)
      cout << mchild1->getBitset()[i] << " ";    
    
    cout << endl << "==================================" << endl;
    cout << "randomMutator sur ItemSetC" << endl;
    ItemSetC* mchild2 = mutator->execute(ditc);
    cout << "Parent : ";
    for(unsigned i=0; i < ditc->getSize(); ++i)
      cout << ditc->getBitsetAt(i) << " ";
    cout << endl << "Enfant : ";
    for(unsigned i=0; i < mchild2->getSize(); ++i)
      cout << mchild2->getBitsetAt(i) << " ";    
    
    cout << endl << "==================================" << endl;
    
    delete mutator;
    delete mchild1; delete mchild2;
    delete dit; delete dit2; delete ditc; delete ditc2;
    delete[] tmp; delete[] tmp2; 
  return 0;
}

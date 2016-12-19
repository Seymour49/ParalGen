
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
#include "../include/freqEval.h"

using namespace std;

int main(int argc, char **argv) {

    srand(time(NULL));
    
    DataSet* data = new DataSet();
    data->loadFile("./data/testEval.dat");
    
    DataSetC* dataC = new DataSetC();
    dataC->loadFile("./data/testEval.dat");

    char * init1 = new char[data->getNbCol()];
    char * init2 = new char[data->getNbCol()];
    char * init3 = new char[data->getNbCol()];
    vector<char> v1,v2,v3;
    for(unsigned i=0; i < data->getNbCol(); ++i){
	if( i == 1 || i == 3 || i == 6 ){
	    init1[i] = '1';
	    v1.push_back('1');
	}
	else{
	    init1[i] = '0';
	    v1.push_back('0');
	}
	if( i == 0 || i == 2 || i == 5){
	    init2[i] = '1';
	    v2.push_back('1');
	}
	else{
	    init2[i] = '0';
	    v2.push_back('0');
	}
	if( i == 1 || i == 5 || i == 7){
	    init3[i] = '1';
	    v3.push_back('1');
	}
	else{
	    init3[i] = '0';
	    v3.push_back('0');
	}
    }
    
    ItemSet* dit1 = new ItemSet(v1);
    ItemSet* dit2 = new ItemSet(v2);
    ItemSet* dit3 = new ItemSet(v3);
    
    ItemSetC* ditc1 = new ItemSetC(init1,dataC->getNbCol());
    ItemSetC* ditc2 = new ItemSetC(init2,dataC->getNbCol());
    ItemSetC* ditc3 = new ItemSetC(init3,dataC->getNbCol());
    
    cout << *dit1 << *dit2 << *dit3;
    
    cout << *ditc1 << *ditc2 << *ditc3;
    
    cout << "=========DATASET==========" << endl;
    cout << *data;
    cout << "=========DATASETC=========" << endl;
    cout << *dataC;
    
    cout <<"Scores avant eval itemSet : " <<  dit1->getScore() << " ; " 
	 << dit2->getScore() << " ; " << dit3->getScore() << endl;
    
	 
    cout <<"Scores avant eval itemSetC : " <<  ditc1->getScore() << " ; " 
	 << ditc2->getScore() << " ; " << ditc3->getScore() << endl;
    
    FreqEval* eval = new FreqEval();
    eval->execute(dit1,data);
    eval->execute(dit2,data);
    eval->execute(dit3,data);
    
    eval->execute(ditc1,dataC);
    eval->execute(ditc2,dataC);
    eval->execute(ditc3,dataC);
    
    cout <<"Scores après eval itemSet : " <<  dit1->getScore() << " ; " 
	 << dit2->getScore() << " ; " << dit3->getScore() << endl;
    
	 
    cout <<"Scores après eval itemSetC : " <<  ditc1->getScore() << " ; " 
	 << ditc2->getScore() << " ; " << ditc3->getScore() << endl;
	 
    delete eval;
    delete data; delete dataC;
    delete dit1; delete dit2; delete dit3;
    delete ditc1; delete ditc2; delete ditc3;
    delete[] init1; delete[] init2; delete[] init3;
  return 0;
}

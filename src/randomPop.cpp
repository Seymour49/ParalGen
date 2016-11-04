#include "../include/randomPop.h"

using namespace std;

RandomPop::RandomPop(unsigned int nbI):_nbItems(nbI),_density(0.05)
{
}


RandomPop::RandomPop(unsigned int nbI, float density):_nbItems(nbI),
_density(density)
{
}


RandomPop::~RandomPop()
{
}


void RandomPop::execute(std::vector< ItemSet* >* pop, unsigned int taillePop)
{
    int alea;
     int d = _density*100;
    for(unsigned int i=0; i < taillePop; ++i){
	vector<char> tmp;
	tmp.resize(_nbItems);
	
	alea = rand() % _nbItems;
	tmp.at(alea) = '1';
	for(unsigned j=0; j < _nbItems; ++j){
	    alea = rand() % _nbItems;
	    if( alea < d)
	      tmp.at(j) = '1';
	    else
	      tmp.at(j) = '0';
	}
      
	ItemSet* it = new ItemSet(tmp);
	
	pop->push_back(it);
    }
}


void RandomPop::execute(std::vector< ItemSetC* >* pop, unsigned int taillePop)
{
    int alea;
    int d = _density*100;
    for(unsigned i=0; i < taillePop; ++i){
	char * tmp = new char[_nbItems];
	alea = rand() % _nbItems;
	tmp[alea] = '1';
	for(unsigned j=0; j < _nbItems; ++j){
	    alea = rand() % 100;
	    if( alea < d)
	      tmp[j] = '1';
	    else
	      tmp[j] = '0';
	}
      
	ItemSetC* it = new ItemSetC(tmp, _nbItems);
	pop->push_back(it);
	delete[] tmp;
    }
}

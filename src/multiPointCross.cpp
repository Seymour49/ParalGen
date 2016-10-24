#include "../include/multiPointCross.h"

using namespace std;

MultiPointCross::MultiPointCross(size_t* pivots, unsigned nbPivots):_nbPivots(nbPivots)
{
  size_t* tmp = new size_t[_nbPivots];
  for(unsigned i=0; i < _nbPivots; ++i)
    tmp[i] = pivots[i];
  _pivots = tmp;
}

MultiPointCross::~MultiPointCross()
{
  delete[] _pivots;
}

ItemSetC* MultiPointCross::execute(ItemSetC* p1, ItemSetC* p2)
{
    if( _pivots == NULL ){
	cerr << "Erreur, _pivots = NULL" << endl;
	exit(EXIT_FAILURE);
    }
    else if( _nbPivots > p1->getSize() ){
	cerr << "Erreur, trop de pivots" << endl;
	exit(EXIT_FAILURE);
    }
    else if( _pivots[0] < 1 || _pivots[_nbPivots-1] > (p1->getSize()-2) ){
	cerr << "Erreur, pivots[0]  = 0 ou pivots[last] = p1.getSize() -2" << endl;
	exit(EXIT_FAILURE);
    }
    else{
	char* bitset = new char[p1->getSize()];
	unsigned j=0;
	bool b=true; /* Vrai si l'individu fils récupère les données de 
		      l'ItemSetC courant et faux si il récupère les données de it 
		      (passé en paramètre)*/
// 	while( i < p1->getSize() ){

	for(unsigned i=0; i < p1->getSize(); ++i){
	    if( i < _pivots[j] ){
		if(b) bitset[i] = p1->getBitsetAt(i);
		else  bitset[i] = p2->getBitsetAt(i);
	    }
	    else if( i == _pivots[j] ){
	      if(b) bitset[i] = p1->getBitsetAt(i);
	      else  bitset[i] = p2->getBitsetAt(i);
	      b = (!b);
	      if( j < (_nbPivots-1) )
		j++;
	    }
	    else{
	      if(b) bitset[i] = p1->getBitsetAt(i);
	      else  bitset[i] = p2->getBitsetAt(i); 
	    }
	}
	
	ItemSetC* child = new ItemSetC(bitset, p1->getSize());
	delete[] bitset;
	return child;
    }
    
}


ItemSet* MultiPointCross::execute(ItemSet* p1, ItemSet* p2)
{
    if( _pivots == NULL ){
	cerr << "Erreur, _pivots = NULL" << endl;
	exit(EXIT_FAILURE);
    }
    else if( _nbPivots > p1->getSize() ){
	cerr << "Erreur, trop de pivots" << endl;
	exit(EXIT_FAILURE);
    }
    else if( _pivots[0] == 0 || _pivots[_nbPivots-1] > (p1->getSize() -2) ) {
	cerr << "Erreur, pivots[0]  = 0 ou pivots[last] = p1.getSize() -2" << endl;
	exit(EXIT_FAILURE);      
    }
    else{
      
      	vector<char> bitset;
	unsigned j=0;
	bool b=true; /* Vrai si l'individu fils récupère les données de 
		      l'ItemSetC courant et faux si il récupère les données de it 
		      (passé en paramètre)*/
	for(unsigned i=0; i < p1->getSize(); ++i){
	    if( i < _pivots[j] ){
	      
	      if(b) bitset.push_back(p1->getBitset()[i]);
	      else  bitset.push_back(p2->getBitset()[i]);
	    
	      
	    }else if( i == _pivots[j] ){
	      
	      if(b) bitset.push_back(p1->getBitset()[i]);
	      else  bitset.push_back(p2->getBitset()[i]);
	      b = (!b);
	      if( j < (_nbPivots-1) )
		j++;
	    
	      
	    }else{
	      if(b) bitset.push_back(p1->getBitset()[i]);
	      else  bitset.push_back(p2->getBitset()[i]); 
	    }
	}
	
	ItemSet* child = new ItemSet(bitset);	
	return child;
    }
}

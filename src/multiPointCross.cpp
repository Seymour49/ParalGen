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
    else{
	char* bitset = new char[p1->getSize()];
	unsigned i =0, tmp=0;
	bool b=true; /* Vrai si l'individu fils récupère les données de 
		      l'ItemSetC courant et faux si il récupère les données de it 
		      (passé en paramètre)*/
	while( i < p1->getSize() ){
	  
	  if( i > (_pivots[tmp] -1) ){
	      b = (!b);
	      ++tmp;
	  }
	  if (b) bitset[i] = p1->getBitsetAt(i);
	  else bitset[i] = p2->getBitsetAt(i);
	  
	  ++i;
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
    else{
      
      	vector<char> bitset;
	unsigned i =0, tmp=0;
	bool b=true; /* Vrai si l'individu fils récupère les données de 
		      l'ItemSetC courant et faux si il récupère les données de it 
		      (passé en paramètre)*/
	while( i < p1->getSize() ){
	  
	  if( i > (_pivots[tmp] -1) ){
	      b = (!b);
	      ++tmp;
	  }
	  if (b) bitset.push_back(p1->getBitset()[i]);
	  else bitset.push_back(p2->getBitset()[i]);
	  
	  ++i;
	}
	
	ItemSet* child = new ItemSet(bitset);	
	return child;
    }
}

#include "../include/classicCross.h"

using namespace std;

ClassicCross::ClassicCross(size_t pivot):_pivot(pivot)
{
}

ClassicCross::~ClassicCross()
{
}


ItemSet* ClassicCross::execute(ItemSet* p1, ItemSet* p2)
{
    if(p1 != NULL && p2 != NULL){
      
	if( p1->getSize() != p2->getSize() ){
		cerr << "Erreur. ItemsetC de tailles différentes" << endl;
		exit(EXIT_FAILURE);
	}
	else if(  _pivot > (p1->getSize()-2)){
	    cerr << "Erreur, le pivot utilisé est trop grand" << endl;
	    exit(EXIT_FAILURE);
	}
	else{
	    vector<char> tmp;
	    
	    for (unsigned int i = 0; i < _pivot; ++i) {
		tmp.push_back(p1->getBitset()[i]);
	    }
	    for (unsigned int i = _pivot; i < p2->getSize(); ++i) {
		tmp.push_back(p2->getBitset()[i]);
	    }
			  
	    ItemSet* child = new ItemSet(tmp);
	    return child;
	}
    }
    else{
      cerr << "Erreur. Pointeurs nuls" << endl;
      exit(EXIT_FAILURE);
    }
}


ItemSetC* ClassicCross::execute(ItemSetC* p1, ItemSetC* p2)
{
    if( p1 != NULL && p2 != NULL){
      
	if( p1->getSize() != p2->getSize() ){
	    cerr << "Erreur. ItemsetC de tailles différentes" << endl;
	    exit(EXIT_FAILURE);
	}
	else{
	    char* bitset = new char[p1->getSize()];
	    for(unsigned i = 0; i < _pivot; ++i){
		bitset[i] = p1->getBitsetAt(i);
	    }
	    for(unsigned j=_pivot ; j < p2->getSize();++j){
		bitset[j] = p2->getBitsetAt(j);
	    }
	    
	    ItemSetC* child = new ItemSetC(bitset,p1->getSize());		
	    delete[] bitset;
	    return child;
	  }
	    
    }else{
      
      cerr <<"Erreur. Pointeurs nuls" << endl;
      exit(EXIT_FAILURE);
    }
      
}

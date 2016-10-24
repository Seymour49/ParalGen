#include "../include/uniformCross.h"
#include <ctime>

using namespace std;

UniformCross::UniformCross()
{
}

UniformCross::~UniformCross()
{
}

ItemSetC* UniformCross::execute(ItemSetC* p1, ItemSetC* p2)
{
  if( p1 == NULL || p2 == NULL){
      cerr << "Erreur, parent(s) nul(s)." << endl;
      exit(EXIT_FAILURE);
  }
  else if( p1->getSize() != p2->getSize() ){
      cerr << "Erreur, parents de tailles différentes" << endl;
      exit(EXIT_FAILURE);
  }
  else{
      char* bitset = new char[p1->getSize()];
      srand(time(NULL));
      int alea;
      for(unsigned i=0; i < p1->getSize(); ++i){
	 alea = rand()%2;
	 if( alea == 0)
	   bitset[i] = p1->getBitsetAt(i);
	 else
	   bitset[i] = p2->getBitsetAt(i);
      }
      
      ItemSetC* child = new ItemSetC(bitset, p1->getSize());
      delete[] bitset;
      return child;
  }
}

ItemSet* UniformCross::execute(ItemSet* p1, ItemSet* p2)
{
  if( p1 == NULL || p2 == NULL){
      cerr << "Erreur, parent(s) nul(s)." << endl;
      exit(EXIT_FAILURE);
  }
  else if( p1->getSize() != p2->getSize() ){
      cerr << "Erreur, parents de tailles différentes" << endl;
      exit(EXIT_FAILURE);
  }
  else{
      vector<char> bitset;
      srand(time(NULL));
      int alea;
      for(unsigned i=0; i < p1->getSize(); ++i){
	 alea = rand()%2;
	 if( alea == 0)
	   bitset.push_back(p1->getBitset()[i]);
	 else
	   bitset.push_back(p2->getBitset()[i]);
      }
      
      ItemSet* child = new ItemSet(bitset);
      return child;
  }
}

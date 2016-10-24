#include "../include/randomMutator.h"

using namespace std;

RandomMutator::RandomMutator()
{
}


RandomMutator::~RandomMutator()
{
}


ItemSet* RandomMutator::execute(ItemSet* p1)
{
    if(p1 == NULL){
	cerr << "Erreur, individu à muter nul (pointeur = NULL)." << endl;
	exit(EXIT_FAILURE);
    }
    else{
	srand(time(NULL));
	vector<char> tmp;
	for(unsigned i=0; i < p1->getSize();++i){
	    tmp.push_back(p1->getBitset()[i]);
	}
	int pivot = rand()% (p1->getSize()-1);
	if(p1->getBitset()[pivot] == '0'){
	    tmp[pivot] = '1';
	}else{
	    tmp[pivot] = '0';
	}
	ItemSet* child = new ItemSet(tmp);
	return child;
    }
}


ItemSetC* RandomMutator::execute(ItemSetC* p1)
{
    if(p1 == NULL){
	cerr << "Erreur, individu à muter nul (pointeur = NULL)." << endl;
	exit(EXIT_FAILURE);
    }
    else{
	srand(time(NULL));
	char* tmp = new char[p1->getSize()];
	for(unsigned i=0; i < p1->getSize();++i){
	    tmp[i] = p1->getBitsetAt(i);
	}
	int pivot = rand()% (p1->getSize()-1);
	if(p1->getBitsetAt(pivot) == '0'){
	    tmp[pivot] = '1';
	}else{
	    tmp[pivot] = '0';
	}
	ItemSetC* child = new ItemSetC(tmp,p1->getSize());
	delete[] tmp;
	return child;
    }
}

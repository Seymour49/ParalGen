#include "../include/freqPop.h"
#include <algorithm>

#define toDigit(c) (c-'0')
using namespace std;

FreqPop::FreqPop():_density(0.05)
{
}


FreqPop::FreqPop(float density):_density(density)
{
}


FreqPop::~FreqPop()
{
}

/**
 * Fonction de comparaison entre deux paires <entier-float>
 * Renvoie vrai si f1 > f2
 * @author Ugo Rayer 
 */
bool descPair (pair<int,float>* i, pair<int,float>* j) { return (i->second>j->second); }


void FreqPop::execute(std::vector< ItemSet* >* pop,unsigned taillePop, DataSet* data)
{
    // A implémenter
}


void FreqPop::execute(std::vector< ItemSetC* >* pop, unsigned taillePop, DataSetC* data)
{
    unsigned line = data->getNbLine();
    unsigned item = data->getNbCol();
  
    vector<pair<int, float>*> itemOcc;
    itemOcc.resize(item);
    
    for(unsigned i=0; i < item; ++i){
	itemOcc[i] = new pair<int,float>(i,0);
	
	for(unsigned j=0; j < line; ++j){
	    itemOcc[i]->second += toDigit( data->getDataAt(j,i));
	}
    }
   
    sort(itemOcc.begin(), itemOcc.end(), descPair);

    unsigned nbBrik = (item/10);
    int brik[nbBrik];
    unsigned nbCiment = (item/5);
    int ciment[nbCiment];
    int brikP = 0 ; int cimentP = 0;
    for(unsigned i=0; i < item; ++i){
	if(i <= nbBrik){
	    brik[brikP] = itemOcc[i]->first;
	    ++brikP;
	}
	else if( i > nbBrik && i <= (nbBrik+nbCiment) ){
	    ciment[cimentP] = itemOcc[i]->first;
	    ++cimentP;
	}
    }
    
    for(unsigned i=0; i < itemOcc.size(); ++i){
	delete itemOcc[i];
    }
    
    int selectedBrik;
    int selectedCiment;
    
    int indBrik, indCiment;
    // Correspond à la densité choisie. 
    int max_bit = _density*100;
    
      
    while(pop->size() != taillePop){
	char* tmp = new char[item];
	for(unsigned i=0; i < item; ++i) tmp[i] = '0';
	
	selectedBrik = rand() % max_bit;
	selectedCiment = max_bit - selectedBrik;
      
	for(int i=0; i < selectedBrik; ++i){
	    indBrik = rand() % (nbBrik -1);
	    tmp[brik[indBrik]] = '1';
	}
	/*
	 * Use of uninitialised value of size 8 detecté de manière aléatoire
	 * dans la boucle for ci-dessous
	 * TODO Trouver l'origine
	 * 
	 */
	for(int j=0; j < selectedCiment; ++j){
	    indCiment = rand() % (nbCiment) + nbBrik;
	    tmp[ciment[indCiment]] = '1';
	}
	
	ItemSetC* child = new ItemSetC(tmp,item);
	delete[] tmp;
	
	pop->push_back(child);
	
    }
}


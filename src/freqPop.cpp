#include "../include/freqPop.h"
#include <algorithm>
#include <utility>

#define toDigit(c) (c-'0')
using namespace std;

FreqPop::FreqPop(DataSet* data):_density(0.05),_data(data),_dataC(NULL)
{
}


FreqPop::FreqPop(float density, DataSet* data):_density(density),_data(data),
_dataC(NULL)
{
}


FreqPop::FreqPop(DataSetC* data):_density(0.05),_data(NULL),_dataC(data)
{
}


FreqPop::FreqPop(float density, DataSetC* data):_density(density),_data(NULL),_dataC(data)
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


void FreqPop::execute(std::vector< ItemSet* >* pop,unsigned taillePop)
{
    // A implémenter
    if( pop->size() != 0){
	cerr << "Erreur, population déjà initialisée" << endl;
	exit(EXIT_FAILURE);
    }
    else{
	unsigned line = _dataC->getNbLine();
	unsigned item = _dataC->getNbCol();
      
	vector<pair<int, float>*> itemOcc;
	
	for(unsigned i=0; i < item; ++i){
	    pair<int,float>* tmp = new pair<int,float>(i,0);
	    itemOcc.push_back(tmp);
	    
	    for(unsigned j=0; j < line; ++j){
		itemOcc[i]->second += toDigit( _dataC->getDataAt(j,i));
	    }
	}
      
	sort(itemOcc.begin(), itemOcc.end(), descPair);

	unsigned nbBrik = (item/10);
	int brik[nbBrik] = { };
	unsigned nbCiment = (item/5);
	int ciment[nbCiment] = { };
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
	
	int indBrik;
	int indCiment;
	// Correspond à la densité choisie. 
	int max_bit = _density*100;
	
	
	while(pop->size() != taillePop){
	    vector<char> tmp;
	    for(unsigned i=0; i < item; ++i) tmp.push_back('0');
	    selectedBrik = rand() % max_bit;
	    selectedCiment = max_bit - selectedBrik;
	  
	    for(int i=0; i < selectedBrik; ++i){
		indBrik = rand() % (nbBrik -1);
		tmp[brik[indBrik]] = '1';
	    }
	   
	    for(int j=0; j < selectedCiment; ++j){
		indCiment = rand() % (nbCiment-1);
		tmp[ciment[indCiment]] = '1';
	    }
	    
	    ItemSet* child = new ItemSet(tmp);	    
	    pop->push_back(child);
	    
	}
	
    }
}


void FreqPop::execute(std::vector< ItemSetC* >* pop, unsigned taillePop)
{
    if( pop->size() != 0){
	cerr << "Erreur, population déjà initialisée" << endl;
	exit(EXIT_FAILURE);
    }
    else{
	unsigned line = _dataC->getNbLine();
	unsigned item = _dataC->getNbCol();
      
	vector<pair<int, float>*> itemOcc;
	
	for(unsigned i=0; i < item; ++i){
	    pair<int,float>* tmp = new pair<int,float>(i,0);
	    itemOcc.push_back(tmp);
	    
	    for(unsigned j=0; j < line; ++j){
		itemOcc[i]->second += toDigit( _dataC->getDataAt(j,i));
	    }
	}
      
	sort(itemOcc.begin(), itemOcc.end(), descPair);

	unsigned nbBrik = (item/10);
	int brik[nbBrik] = { };
	unsigned nbCiment = (item/5);
	int ciment[nbCiment] = { };
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
	
	int selectedBrik = 0;
	int selectedCiment = 0;
	
	int indBrik = 0;
	int indCiment = 0;
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
	   
	    for(int j=0; j < selectedCiment; ++j){
		indCiment = rand() % (nbCiment-1);
		tmp[ciment[indCiment]] = '1';
	    }
	    
	    ItemSetC* child = new ItemSetC(tmp,item);
	    delete[] tmp;
	    
	    pop->push_back(child);
	    
	}
	
    }

}


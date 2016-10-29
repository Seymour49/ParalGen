#include "../include/geneticAlgoC.h"
#include <algorithm>

#define toDigit(c) (c-'0')

using namespace std;


GeneticAlgoC::GeneticAlgoC():_nbIteration(10000),_taillePop(100), _seuilFrequence(0.6)
{}


GeneticAlgoC::GeneticAlgoC(unsigned int it, unsigned int pop, float seuilfrequence, Mutator* mut, Cross* cross, Evaluate* eval):
  _nbIteration(it), _taillePop(pop), _seuilFrequence(seuilfrequence), _mutator(mut), _cross(cross), _eval(eval)
{}


GeneticAlgoC::~GeneticAlgoC()
{
  for(unsigned int i=0; i < _population.size(); ++i){
      delete _population[i];
  }
}


void GeneticAlgoC::setData(DataSetC* input){
    _data = input;
}


/**
 * Méthode non-générique. Initialisation d'itemSet
 * et pas d'individus.
 */
void GeneticAlgoC::initRandomPop()
{    
    srand(time(NULL));
    int alea;
    
    for(unsigned int i=0; i < _taillePop; ++i){
	char * tmp = new char[_data->getNbCol()];
	alea = rand() % 99;
	tmp[alea] = '1';
	for(unsigned j=0; j < _data->getNbCol(); ++j){
	    alea = rand() % 99;
	    if( alea < 5)
	      tmp[j] = '1';
	    else
	      tmp[j] = '0';
	}
      
	ItemSetC* it = new ItemSetC(tmp, _data->getNbCol());
	_eval->execute(it,_data);
	_population.push_back(it);
	delete[] tmp;
    }
    
}


void GeneticAlgoC::initFreqPop()
{
    unsigned line = _data->getNbLine();
    unsigned item = _data->getNbCol();
    
    vector<pair<int, float>*> itemOcc;
    itemOcc.resize(item);
    
    for(unsigned i=0; i < item; ++i){
	itemOcc[i] = new pair<int,float>(i,0);
	
	for(unsigned j=0; j < line; ++j){
	    itemOcc[i]->second += toDigit( _data->getDataAt(j,i));
	}
    }
   
//     sort(itemOcc.begin(), itemOcc.end(), descPair);

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
    int max_bit = 5;
    
    while(_population.size() != _taillePop){
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
	_eval->execute(child,_data);
	_population.push_back(child);
	
    }
   
}


void GeneticAlgoC::displayPopulation() {
    cout << "La population actuelle est la suivante : " << endl;
    
    for(unsigned i=0; i<_population.size(); ++i){
	_population[i]->print(cout);
    }
}

#include "../include/geneticAlgoC.h"
#include <algorithm>

#define toDigit(c) (c-'0')

using namespace std;


GeneticAlgoC::GeneticAlgoC():_nbIteration(10000),_taillePop(100), _seuilFrequence(0.6)
{
   _population = new vector<ItemSetC*>();
}


GeneticAlgoC::GeneticAlgoC(unsigned int it, unsigned int pop, float seuilfrequence, Mutator* mut, Cross* cross, Evaluate* eval, InitPop* init):
  _nbIteration(it), _taillePop(pop), _seuilFrequence(seuilfrequence), _mutator(mut), _cross(cross), _eval(eval), _init(init)
{
  _population = new vector<ItemSetC*>();
}


GeneticAlgoC::~GeneticAlgoC()
{
  for(unsigned int i=0; i < _population->size(); ++i){
      delete _population->at(i);
  }
  _population->clear();
  _population->shrink_to_fit();
  delete _population;
}


void GeneticAlgoC::setData(DataSetC* input){
    _data = input;
}

void GeneticAlgoC::EvalPop()
{
  for(unsigned i=0; i < _population->size(); ++i)
    _eval->execute(_population->at(i), _data);
}

void GeneticAlgoC::initPop()
{
    if(_init != NULL){
	_init->execute(_population,_taillePop);
    }
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
	_population->push_back(it);
	delete[] tmp;
    }
    
}


void GeneticAlgoC::initFreqPop()
{
   
}


void GeneticAlgoC::displayPopulation() {
    cout << "La population actuelle est la suivante : " << endl;
    
    for(unsigned i=0; i<_population->size(); ++i){
	cout << *_population->at(i);
    }
}

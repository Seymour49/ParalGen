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
    if(_init == NULL){
	cerr << "Erreur, initPop null" << endl;
	exit(EXIT_FAILURE);
    }
    else{
	_init->execute(_population,_taillePop);
    }
}


void GeneticAlgoC::doMutation(unsigned ind)
{
    if( _population->size() == 0 ){
	cerr << "Erreur population vide" << endl;
	exit(EXIT_FAILURE);
    }
    else if( _mutator == NULL){
	cerr << "Méthode de mutation null" << endl;
	exit(EXIT_FAILURE);
    }
    else if( ind < 0  ){
	cerr << "Erreur  sur indice" << endl;
	exit(EXIT_FAILURE); 
    }
    else if( ind > (_population->size()-1) ){
	cerr << "Erreur sur indice" << endl;
	exit(EXIT_FAILURE); 
    }
    else{
	_population->at(ind) = _mutator->execute(_population->at(ind));
    }
}


void GeneticAlgoC::displayPopulationAt(unsigned int ind)
{
    if( _population->size() == 0 ){
	cerr << "Erreur population vide" << endl;
	exit(EXIT_FAILURE);
    }
    else if( ind < 0  ){
	cerr << "Erreur  sur indice" << endl;
	exit(EXIT_FAILURE); 
    }
    else if( ind > (_population->size()-1) ){
	cerr << "Erreur sur indice" << endl;
	exit(EXIT_FAILURE); 
    }
    else{
	cout << *_population->at(ind);
    }
}

void GeneticAlgoC::displayPopulation() {
    cout << "La population actuelle est la suivante : " << endl;
    
    for(unsigned i=0; i<_population->size(); ++i){
	cout << *_population->at(i);
    }
}

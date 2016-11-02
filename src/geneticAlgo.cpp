#include "../include/geneticAlgo.h"

using namespace std;

GeneticAlgo::GeneticAlgo():_nbIteration(10000),_taillePop(100), _seuilFrequence(0.6)
{
    _population = new vector<ItemSet*>();
}


GeneticAlgo::GeneticAlgo(unsigned int it, unsigned int pop, float seuilFrequence,
			 Mutator* mut, Cross* cross, Evaluate* eval, InitPop* init):
			 _nbIteration(it),_taillePop(pop), _seuilFrequence(seuilFrequence),
			 _mutator(mut), _cross(cross), _eval(eval),_init(init)
{
    _population = new vector<ItemSet*>();
}


GeneticAlgo::~GeneticAlgo()
{
  for(unsigned int i=0; i < _population->size(); ++i){
      delete _population->at(i);
  }
  _population->clear();
  _population->shrink_to_fit();
  delete _population;
}


void GeneticAlgo::setData(DataSet* input){
    _data = input;
}


void GeneticAlgo::EvalPop()
{
    for(unsigned i=0; i < _population->size(); ++i){
	_eval->execute(_population->at(i),_data);
    }
}


void GeneticAlgo::initPop()
{
   if(_init == NULL){
	cerr << "Erreur, initPop null" << endl;
	exit(EXIT_FAILURE);
    }
    else{
	_init->execute(_population,_taillePop);
    }
}


void GeneticAlgo::doMutation(unsigned int ind)
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


void GeneticAlgo::doCrossFor(unsigned int id1, unsigned int id2)
{
    if(  (id1 > (_taillePop-1)) || (id2 > (_taillePop-1)) ){
	cerr << "Erreur, indices des parents hors de la population" << endl;
	exit(EXIT_FAILURE);
    }
    else{
	ItemSet* newI = _cross->execute(_population->at(id1),
					_population->at(id2) );
	cout << "NOUVEL INDIVIDU A INSERER DANS LA POPULATION" << endl;
	cout << *newI;
	
	cout << "TODO : voir pour la suppression du mauvais" << endl;
	delete newI;
    }
}


void GeneticAlgo::incAgePop()
{
  for (unsigned int i = 0; i < _population->size(); ++i) {
    _population->at(i)->incAge();
  }
}


void GeneticAlgo::run()
{
  unsigned int iteration = 0;
  int alea;
  vector<unsigned int> 
  initRandomPop();
  while (iteration < _nbIteration) {
    incAgePop();
    alea = rand()%100 + 1;
    if (alea == 1) {
      
    }
    else {
      
    }
  }
}


void GeneticAlgo::displayPopulation() {
    cout << "La population actuelle est la suivante : " << endl;
    
    for(unsigned i=0; i<_population->size(); ++i){
	cout << *_population->at(i);
    }
}


void GeneticAlgo::displayPopulationAt(unsigned ind)
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
#include "../include/geneticAlgo.h"
#include <time.h>

using namespace std;

GeneticAlgo::GeneticAlgo():_nbIteration(10000),_taillePop(100)
{
}

GeneticAlgo::GeneticAlgo(unsigned int it, unsigned int pop): _nbIteration(it), _taillePop(pop)
{
}

GeneticAlgo::~GeneticAlgo()
{
    for(unsigned int i=0; i < _population.size(); ++i){
	delete _population[i];
    }
}


void GeneticAlgo::setData(DataSet* input){
    _data = input;
}

/**
 * Méthode non-générique. Initialisation d'itemSet
 * et pas d'individus.
 */
void GeneticAlgo::initRandomPop()
{    
    srand(time(NULL));
    int alea;
    
    for(unsigned int i=0; i < _taillePop; ++i){
	vector<char> tmp;
	
	for(unsigned j=0; j < _data->getNbCol(); ++j){
	    alea = rand() % 100;
	    if( alea <= 50)
	      tmp.push_back('1');
	    else
	      tmp.push_back('0');
	}
      
	ItemSet* it = new ItemSet(tmp);
	_population.push_back(it);
    }
    
}


void GeneticAlgo::initFreqPop()
{
  if ((_seuilFrequence > 0)&&(_seuilFrequence <= 1)) {
    unsigned int count_pop = 0; // Compteur de la population
    vector<vector<char > > listItem;
    while (count_pop < _taillePop) {
      for (unsigned int i = 0; i < _data->getNbCol(); ++i) {
	
      }
      count_pop++;
    }
  } 
  else cerr << "Le seuil de fréquence doit être compris entre 0 et 1 pour pouvoir initialiser une population de fréquent !" << endl; 
}


void GeneticAlgo::displayPopulation(){
    cout << "La population actuelle est la suivante : " << endl;
    
    for(unsigned i=0; i<_population.size(); ++i){
	cout << *_population[i];
    }
  
}

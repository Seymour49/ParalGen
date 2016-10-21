#include "../include/geneticAlgo.h"
#include <time.h>

using namespace std;

GeneticAlgo::GeneticAlgo():_nbIteration(10000),_taillePop(100)
{
}

GeneticAlgo::GeneticAlgo(int it, int pop): _nbIteration(it), _taillePop(pop)
{
}

GeneticAlgo::~GeneticAlgo()
{
    for(unsigned int i=0; i < _population.size(); ++i){
	delete _population[i];
    }
}


void GeneticAlgo::setData(DataSet* input){
    data = input;
}

/**
 * Méthode non-générique. Initialisation d'itemSet
 * et pas d'individus.
 */
void GeneticAlgo::initRandomPop()
{    
    srand(time(NULL));
    int alea;
    
    for(int i=0; i < _taillePop; ++i){
	vector<char> tmp;
	
	for(unsigned j=0; j < data->getNbCol(); ++j){
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

void GeneticAlgo::displayPopulation(){
    cout << "La population actuelle est la suivante : " << endl;
    
    for(unsigned i=0; i<_population.size(); ++i){
	cout << *_population[i];
    }
  
}

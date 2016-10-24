#include "../include/geneticAlgo.h"

using namespace std;

GeneticAlgo::GeneticAlgo():_nbIteration(10000),_taillePop(100), _seuilFrequence(0.6)
{}

GeneticAlgo::GeneticAlgo(unsigned int it, unsigned int pop, float seuilfrequence): _nbIteration(it), _taillePop(pop), _seuilFrequence(seuilfrequence)
{}

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
    unsigned int size = 0; // Taille population courante
    vector<vector<char > > listItem;
    vector<char> item;
    while (listItem.size() < _taillePop) {
      for (unsigned int i = 0; i < _data->getNbCol(); ++i) {
	item.assign(_data->getNbCol(), '0');
	item[i] = '1';
	if (_data->freqItemSet(item) >= _seuilFrequence) {
	  listItem.push_back(item);
	  size = listItem.size();
	  for (unsigned int j = 0; (j < size)&&(listItem.size() < _taillePop); ++i) {
	    item = listItem[j];
	    item[i] = '1';
	    if (_data->freqItemSet(item) >= _seuilFrequence) listItem.push_back(item);
	  }
	}
      }
    }
    for (unsigned int i = 0; i < listItem.size(); ++i) {
      ItemSet * it = new ItemSet(listItem[i]);
      _population.push_back(it);
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

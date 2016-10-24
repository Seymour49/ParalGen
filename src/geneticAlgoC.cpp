#include "../include/geneticAlgoC.h"

using namespace std;


GeneticAlgoC::GeneticAlgoC():_nbIteration(10000),_taillePop(100), _seuilFrequence(0.6)
{}


GeneticAlgoC::GeneticAlgoC(unsigned int it, unsigned int pop, float seuilfrequence): _nbIteration(it), _taillePop(pop), _seuilFrequence(seuilfrequence)
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
	
	for(unsigned j=0; j < _data->getNbCol(); ++j){
	    alea = rand() % 100;
	    if( alea <= 50)
	      tmp[j] = '1';
	    else
	      tmp[j] = '0';
	}
      
	ItemSetC* it = new ItemSetC(tmp, _data->getNbCol());
	_population.push_back(it);
    }
    
}


void GeneticAlgoC::initFreqPop()
{
  if ((_seuilFrequence > 0)&&(_seuilFrequence <= 1)) {
    unsigned int nbItem = _data->getNbCol();
    if (nbItem > 0) {
      unsigned int size = 0; // Taille population courante
      vector<char * > listItem;
      char * item;
      while (listItem.size() < _taillePop) {
	for (unsigned int i = 0; i < nbItem; ++i) {
	  item = new char[nbItem];
	  for (unsigned int j = 0; j < nbItem; ++j) {
	    item[j] = '0';
	  }
	  item[i] = '1';
	  if (_data->freqItemSet(item, nbItem) >= _seuilFrequence) {
	    listItem.push_back(item);
	    size = listItem.size();
	    for (unsigned int j = 0; (j < size)&&(listItem.size() < _taillePop); ++j) {
	      item = listItem[j];
	      item[i] = '1';
	      if (_data->freqItemSet(item, nbItem) >= _seuilFrequence) listItem.push_back(item);
	    }
	  }
	}
      }
      for (unsigned int i = 0; i < listItem.size(); ++i) {
	ItemSetC * it = new ItemSetC(listItem[i], nbItem);
	_population.push_back(it);
      }
      //for (unsigned int i = 0; i < listItem.size(); ++i) delete[] listItem[i];
      delete item;
    } 
    else cerr << "Impossible d'initialiser une population de fréquent si il n'y a pas de jeu de donnée !" << endl;
  } 
  else cerr << "Le seuil de fréquence doit être compris entre 0 et 1 pour pouvoir initialiser une population de fréquent !" << endl; 
}


void GeneticAlgoC::displayPopulation() {
    cout << "La population actuelle est la suivante : " << endl;
    
    for(unsigned i=0; i<_population.size(); ++i){
	_population[i]->print(cout);
    }
}

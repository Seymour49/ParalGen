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
	it->setScore(_data->freqItemSet(*it));
	_population.push_back(it);
	delete[] tmp;
    }
    
}


void GeneticAlgoC::initFreqPop()
{
  if ((_seuilFrequence > 0)&&(_seuilFrequence <= 1)) {
    unsigned int nbItem = _data->getNbCol();
    
    if (nbItem > 0) { // On vérifie que le jeu de donnée n'est pas vide
      char ** tabItem =  new char*[_taillePop];
      float * tabScore = new float[_taillePop];
      unsigned int size = 0, size2; // Taille de la population courante
      float eval = 0;
      for (unsigned int i = 0; (i < nbItem)&&(size < _taillePop); ++i) {
	char * item = new char[nbItem];
	for (unsigned int j = 0; j < nbItem; ++j) {
	  item[j] = '0';
	}
	item[i] = '1';
	eval = _data->freqItemSet(item, nbItem);
	if ((eval >= _seuilFrequence)&&(size < _taillePop)) {
	  tabItem[size] = item;
	  tabScore[size] = eval;
	  size++;
	  size2 = size;
	  for (unsigned int j = 0; (j < size2)&&(size < _taillePop); ++j) {
	    item = tabItem[j];
	    item[i] = '1';
	    eval = _data->freqItemSet(item, nbItem);
	    if (eval >= _seuilFrequence) {
	      char * item2 = new char[nbItem];
	      for (unsigned int k = 0; k < nbItem; ++k) item2[k] = item[k];
	      tabItem[size] = item2;
	      tabScore[size] = eval;
	      size++;
	    }
	    item[i] = '0';
	  }
	}
	else delete[] item;
      }
      cout << "size = " << size << endl << "_taillePop = " << _taillePop << endl;
      for (unsigned int i = 0; i < size; ++i) {
	ItemSetC * it = new ItemSetC(tabItem[i], nbItem);
	it->setScore(tabScore[i]);
	_population.push_back(it);
      }
      cout << _population.size() << endl;
      for (unsigned int i = 0; i < _taillePop; ++i) delete[] tabItem[i];
      delete[] tabItem;
      delete[] tabScore;
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

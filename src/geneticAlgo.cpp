#include "../include/geneticAlgo.h"

using namespace std;

GeneticAlgo::GeneticAlgo():_nbIteration(10000),_taillePop(100), _seuilFrequence(0.6)
{}


GeneticAlgo::GeneticAlgo(unsigned int it, unsigned int pop, float seuilFrequence, Mutator* mut, Cross* cross): _nbIteration(it),
_taillePop(pop), _seuilFrequence(seuilFrequence), _mutator(mut), _cross(cross)
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
	it->setScore(_data->freqItemSet(*it));
	_population.push_back(it);
    }
    
}

void GeneticAlgo::doMutationFor(unsigned int ind)
{
    if(ind > (_taillePop-1) || ind < 0){
      
	cerr << "Erreur, indice de l'individu hors de la population" << endl;
	exit(EXIT_FAILURE);
    }else{
	_population[ind] = _mutator->execute(dynamic_cast<ItemSet*>(_population[ind]));
    }
}

void GeneticAlgo::doCrossFor(unsigned int id1, unsigned int id2)
{
    if( (id1 < 0) || (id2 < 0) || (id1 > (_taillePop-1)) || (id2 > (_taillePop-1)) ){
	cerr << "Erreur, indices des parents hors de la population" << endl;
	exit(EXIT_FAILURE);
    }
    else{
	ItemSet* newI = _cross->execute(dynamic_cast<ItemSet*>(_population[id1]),
					dynamic_cast<ItemSet*>(_population[id2]) );
	cout << "NOUVEL INDIVIDU A INSERER DANS LA POPULATION" << endl;
	cout << *newI;
	
	cout << "TODO : voir pour la suppression du mauvais" << endl;
	delete newI;
    }
}


void GeneticAlgo::initFreqPop()
{
  if ((_seuilFrequence > 0)&&(_seuilFrequence <= 1)) { // On vérifie que le seuil de fréquence est correctement défini
    unsigned int nbItem = _data->getNbCol();
    
    if (nbItem > 0) { // On vérifie que le jeu de donnée n'est pas vide
      unsigned int size = 0; // Taille population courante
      vector<pair< vector<char >, float> > listItem;
      vector<char> item;
      float eval = 0;
      
      for (unsigned int i = 0; (i < nbItem)&&(listItem.size() < _taillePop); ++i) {
	item.assign(nbItem, '0');
	item[i] = '1';
	eval = _data->freqItemSet(item);
	
	if (eval >= _seuilFrequence) {
	  listItem.push_back(make_pair(item, eval));
	  size = listItem.size();
	  
	  for (unsigned int j = 0; (j < size)&&(listItem.size() < _taillePop); ++j) {
	    item = listItem[j].first;
	    item[i] = '1';
	    eval = _data->freqItemSet(item);
	    if (eval >= _seuilFrequence) listItem.push_back(make_pair(item, eval));
	  }
	  
	}
	
      }
      
      for (unsigned int i = 0; i < listItem.size(); ++i) {
	ItemSet * it = new ItemSet(listItem[i].first);
	it->setScore(listItem[i].second);
	_population.push_back(it);
      }
    }
    else cerr << "Impossible d'initialiser une population de fréquent si il n'y a pas de jeu de donnée !" << endl;
  } 
  else cerr << "Le seuil de fréquence doit être compris entre 0 et 1 pour pouvoir initialiser une population de fréquent !" << endl; 
}


void GeneticAlgo::incAgePop()
{
  for (unsigned int i = 0; i < _population.size(); ++i) {
    _population[i]->incAge();
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
    
    for(unsigned i=0; i<_population.size(); ++i){
	_population[i]->print(cout);
    }
}

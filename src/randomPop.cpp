#include "../include/randomPop.h"

using namespace std;


RandomPop::RandomPop(unsigned int nbItem, float density): _nbItem(nbItem), _density(density)
{}


RandomPop::RandomPop(const RandomPop& r): _nbItem(r.getNbItem()), _density(r.getDensity())
{}


void RandomPop::execute(vector< Individual<char>* >& pop)
{
  if (pop.size() == 0) throw string("Erreur, population à initialiser vide");
  else if (_nbItem == 0) throw string("Erreur, le nombre d'item par individu n'est pas initalisé");
  else {
    int alea;
    float density = _density*100;
    for (unsigned int i = 0; i < pop.size() ; ++i) {
      pop[i]->resize(_nbItem);
      alea = rand() % _nbItem;
      
      (*pop[i])[alea] = '1';
      for (unsigned int j = 0; j < _nbItem; ++j) {
	  alea = rand() % 100;
	  if( alea < density)
	    (*pop[i])[j] = '1';
	  else
	    (*pop[i])[j] = '0';
      }
    }
  }
}


void RandomPop::executeO(std::vector< Individual< char >* >& pop)
{
    throw string("A implémenter");
}

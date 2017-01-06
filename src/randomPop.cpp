#include "../include/randomPop.h"

using namespace std;


RandomPop::RandomPop(unsigned int nbItem, float density): _nbItem(nbItem), _density(density)
{}


RandomPop::RandomPop(const RandomPop& r): _nbItem(r.getNbItem()), _density(r.getDensity())
{}


void RandomPop::execute(vector< Individual<char>* >& pop)
{
  if (pop.size() == 0) throw string("Erreur, population à initialiser vide (randomPop)");
  else if (_nbItem == 0) throw string("Erreur, le nombre d'item par individu n'est pas initalisé (randomPop)");
  else {
    
    
    int indice[_nbItem];
    for(unsigned int i=0; i < _nbItem; ++i)
	indice[i] = i;
    
    for (unsigned int i = 0; i < pop.size() ; ++i) {
      int lim = _nbItem;
      int nbBits = rand() % _nbItem;
      
      pop[i]->resize(_nbItem);
      
      
      for (unsigned int j = 0; j < _nbItem; ++j)
	  (*pop[i])[j] = '0';
	  
      for(int j = 0; j < nbBits; ++j){
	  int pos = rand() % lim;
	  (*pop[i])[indice[pos]] = '1';
	  int tmp = indice[pos];
	  indice[pos] = indice[lim-1];
	  indice[lim-1] = tmp;
	  --lim;
	 
      }
    }
  }
}


void RandomPop::executeO(std::vector< Individual< char >* >& pop)
{
    throw string("A implémenter");
}

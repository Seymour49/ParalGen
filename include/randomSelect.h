#ifndef RANDOMSELECT_H
#define RANDOMSELECT_H

#include "selectPolicy.h"


/**
 * Cette classe implémente une sélection aléatoire de deux parents
 * au sein de la population passée en paramètres de la fonction execute.
 * Cette classe ne nécessite pas de variables.
 * Implémente le design pattern Strategy.
 * 
 * @author Ugo Rayer
 */
template <typename T>
class RandomSelect : public SelectPolicy<T> {
public:
    /* * * * * * * *
     * CONSTRUCTOR *
     * * * * * * * */
    
    /**
     * Constructeur par défaut ne nécessitant aucun paramètre.
     * @author Ugo Rayer
     */
    RandomSelect()
    {}
    
    
    /**
     * Constructeur par recopie
     * @param r : une autre politique de sélection des parents pour un croisement entre individus
     * @author Johan Defaye
     */
    RandomSelect(const RandomSelect<T> & r)
    {}
    
    
    /* * * * * * 
     * METHODS *
     * * * * * */
    
    /**
     * Méthode de sélection de deux parents de manières aléatoire au sein de
     * la population.
     * @param population
     * @author Ugo Rayer
     */ 
    std::pair<int, int> execute(const std::vector<Individual<T> *> & pop) const
    {
      if (pop.size() < 2) throw std::string("Erreur, impossible de sélectionner deux individus car la population en contient moins de deux (randomSelect)");
      else {
	unsigned int sizePop = pop.size();
	unsigned int indice[sizePop];
	for (unsigned int i = 0; i < sizePop; ++i) indice[i] = i;
	
	int parents[2];
	
	for (unsigned int j = 0; j < 2; ++j) {
	  int select = rand()% sizePop;
	  parents[j] = indice[select];
	  indice[select] = indice[sizePop - 1];
	  indice[sizePop - 1] = parents[j];
	  --sizePop;
	}
	
	return std::make_pair(parents[0], parents[1]);
	
	
  //       unsigned int sizePop = pop.size();
  //       int alea = rand() % sizePop;
  //       int alea2 = rand() % sizePop;
  //       while (alea2 == alea) alea2 = rand() % sizePop;
  //       return std::make_pair(alea, alea2);
	
      }
      return std::make_pair(-1, -1);
    }
};

#endif
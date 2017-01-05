#ifndef BESTSELECT_H
#define BESTSELECT_H

#include "selectPolicy.h"

#include <algorithm>

/**
 * Cette classe représente le DP Strategy appliqué à la méthode de sélection
 * des parents au cours d'un algorithme génétique.
 * Les 2 parents sélectionnés sont les meilleurs représentant de la population
 * passée en paramètre.
 * @author Ugo Rayer
 */
template <typename T>
class BestSelect : public SelectPolicy<T> {
 
public:
    /* * * * * * * *
     * CONSTRUCTOR *
     * * * * * * * */
    
    /**
     * Constructeur par défaut. Aucun paramètre requis
     * @author Ugo Rayer
     */
    BestSelect()
    {}
    
    
    /**
     * Constructeur par recopie
     * @param b : une autre politique de sélection des parents pour un croisement entre individus
     * @author Johan Defaye
     */
    BestSelect(const BestSelect<T> & b)
    {}
    
    /* * * * * *
     * METHODS *
     * * * * * */
    
    
    /**
     * Retourne vrai si le score du premier individu passé en paramètre
     * est plus élevé que celui du second
     * Rtourne faux sinon
     * @param i1 : Un premier individu
     * @param i2 : Un second individu
     * @author Ugo Rayer
     */
    static bool scoreIndDesc(const Individual<T> * i1, const Individual<T> * i2)
    {
      return (i1->getScore() > i2->getScore());
    }
    
    
    /**
     * Tri la population par score décroissant
     * @param pop : population
     * @author Ugo Rayer
     */
    void sortByScore(std::vector< Individual<T> *> & pop)
    {
      std::sort(pop.begin(), pop.end(), scoreIndDesc);
    }
    
    
    /**
     * Sélection des deux meilleurs individus pour la reproduction au regard
     * de la fonction d'évaluation de l'algorithme
     * @param pop : population
     * @author Ugo Rayer
     */
    std::pair<int, int> execute(const std::vector<Individual<T> *> & pop) const
    {
      if (pop.size() < 2) throw std::string("Erreur, impossible de sélectionner deux individus car la population en contient moins de deux (bestSelect)");
      else {
	int b1 = 0;
	int b2 = 1;
	
	if (pop[b1]->getScore() < pop[b2]->getScore() ){
	  b1 = 1;
	  b2 = 0;
	}
	
	for (unsigned i = 2; i < pop.size(); ++i){
	  if ( pop[i]->getScore() > pop[b1]->getScore() ){
	      b2 = b1;
	      b1 = i;
	  }
	  else if ( pop[i]->getScore() > pop[b2]->getScore() ){
	      b2 = i;	  
	  }
	}
	
	// Les 2 meilleurs sont en indice b1 et b2
	
	return std::make_pair(b1, b2);
      }
      return std::make_pair(-1, -1);
    }
};

#endif
#ifndef AGEIDPOLICY_H
#define AGEIDPOLICY_H

#include "indelPolicy.h"

/**
 * Cette classe représente l'insertion de l'individu passé en paramètre
 * de la fonction execute au détriment du plus agé des individus de la 
 * population courante (2nd paramètre de la fonction execute).
 * Respecte le design pattern Strategy
 * @author Ugo Rayer
 */

template <typename T>
class AgeIDPolicy : public IndelPolicy<T> {

public:
  
    /* * * * * * * *
     * CONSTRUCTOR *
     * * * * * * * */
    
    /**
     * Constructeur par défaut ne nécessitant pas de paramètre.
     * @author Ugo Rayer
     */
    AgeIDPolicy()
    {}
    
    
   /**
    * Constructeur par recopie
    * @param f : une autre politique d'insertion d'individu
    * @author Johan Defaye
    */
    AgeIDPolicy(const AgeIDPolicy<T> & a)
    {}

    
    /* * * * * *
     * METHODS *
     * * * * * */
    
    /**
     * Insertion de l'individu de type bitset au sein de la population
     * d'individu (vector) passé en paramètre
     * @param ind : individu à insérer
     * @param pop : population à gérer
     * @author Ugo Rayer
     */
      void execute(const Individual<T> & ind, std::vector<Individual<T> *> & pop)
      {
	if (pop.empty()) throw std::string("Erreur, impossible d'ajouter un individu si la population est vide (ageIDPolicy)");
	else {
	  // Recherche de l'individu le plus agé
	  int oldest = 0;
	  
	  for (unsigned i = 1; i < pop.size(); ++i){
	    if (pop[i]->getAge() > pop[oldest]->getAge() ) {
		oldest = i;
	    }
	  }
	  
	  // Modification du plus vieux
	  *(pop[oldest]) = ind;
	}
      }
  
};
#endif

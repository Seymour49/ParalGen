#ifndef FITNESSIDPOLICY_H
#define FITNESSIDPOLICY_H

#include "indelPolicy.h"


/**
 * Cette classe représente l'insertion de l'individu passé en paramètre
 * de la fonction execute au détriment du plus mauvais individu au regard
 * de la fonction de fitness (ie le score de chaque individu).
 * @author Ugo Rayer
 */
template <typename T>
class FitnessIDPolicy : public IndelPolicy<T> {

public:
    
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur par défaut. Ne nécessite aucun paramètre.
   * @author Ugo Rayer
   */
  FitnessIDPolicy()
  {}
  
  
  /**
   * Constructeur par recopie
   * @param f : une autre politique d'insertion d'individu
   * @author Johan Defaye
   */
  FitnessIDPolicy(const FitnessIDPolicy<T> & f)
  {}
  
  
  /* * * * * *
   * METHODS *
   * * * * * */
  
  /**
   * Méthode remplaçant l'individu ayant le score le plus faible par l'individu passé en paramètre
   * @param ind : individu
   * @param pop : population
   * @author Ugo rayer
   */
  void execute(const Individual<T> & ind, std::vector<Individual<T> *> & pop)
  {
    if (pop.empty()) throw std::string("Erreur, impossible d'ajouter un individu si la population est vide");
    else {
      // Rechercher l'indice du plus mauvais individus
      int worst = 0;
      
      for (unsigned int i = 1; i < pop.size(); ++i) {
	  if ( pop[i]->getScore() < pop[worst]->getScore() ) {
	      worst = i;
	  }
      }
      
      // Modification de l'individu ayant le score le plus faible
      *(pop[worst]) = ind;
    }
  }
  
};

#endif
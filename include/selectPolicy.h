#ifndef SELECTPOLICY_H
#define SELECTPOLICY_H

#include <iostream>
#include <vector>
#include "individual.h"

/**
 * Classe abstraite représentant la politique de sélection des individus allant
 * être croisés lors d'une passe de notre algorithme génétique.
 * Nous partons du principe que seuls deux parents sont sélectionné.
 * Ainsi, nous utilisons une paire d'individus choisis parmi la population
 * passée en paramètres de la fonction exécute.
 * Chaque implémentation de cette classe peut posséder divers attributs :
 * 	- Tournoi : 	nombre de participants
 * 			nombre d'équipes... * 
 * @author Ugo Rayer
 */
template <typename T>
class SelectPolicy {
public:
  
  
  /* * * * * *
   * METHODS *
   * * * * * */
  
  /**
   * Méthode de sélection de deux parents parmi la population passée en 
   * paramètres. Retourne la paire d'indice des parents au sein de la 
   * population
   * @param pop : population
   * @author Ugo Rayer
   */
  virtual std::pair<int,int> execute(const std::vector<Individual<T> *> & pop) const = 0;
  
  
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
    
  virtual ~SelectPolicy()
  {}
  
};

#endif
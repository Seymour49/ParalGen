#ifndef CROSS_H
#define CROSS_H

#include <iostream>
#include "individual.h"

/**
 * Cette classe abstraite est la base du design-pattern Strategy appliqué
 * à la méthode de croisement de notre algorithme. Elle définit une seule 
 * méthode virtuelle pure execute devant être redéfinie par les sous-classes 
 * représentant une implémentation de la méthode de croisement entre deux 
 * individus.
 * @author Ugo Rayer
 * 
 */
template <typename T>
class Cross {
  
public:
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  virtual ~Cross() {}
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  
/**
 * Méthode effectuant le croisement entre deux individus de classe Individual ou de ses classes filles. 
 * Doit être redéfinie dans chaque sous-classe
 * @author Johan Defaye
 */
  virtual void execute(const Individual<T> & parent1, const Individual<T> & parent2, Individual<T> & enfant) = 0;
  
};

#endif
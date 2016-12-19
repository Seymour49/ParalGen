#ifndef MUTATOR_H
#define MUTATOR_H

#include <iostream>

#include "individual.h"

/**
 * Cette classe abstraite est la base du design-pattern Strategy appliqué
 * à la méthode de mutation de notre algorithme génétique. Elle définit une
 * seule méthode virtuelle pure execute() devant être redéfinie par les sous-
 * classes de Mutator représentant une implémentation de la méthode de mutation
 * d'un individu.
 * @author Ugo Rayer
 * 
 */
template <typename T>
class Mutator {
public:
  
  
  
  
   /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  virtual ~Mutator() {}
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  /**
   * Méthode effectuant la mutation d'un individu passé en paramètre
   * Doit être redéfinie dans chaque sous-classes
   * @param ind : individu à muter
   * @author Ugo Rayer, Johan Defaye
   */
   virtual void execute(Individual<T> & ind) = 0;
   
      
};

#endif
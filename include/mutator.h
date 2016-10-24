#ifndef MUTATOR_H
#define MUTATOR_H

#include <iostream>

#include "individual.h"
#include "itemSet.h"
#include "itemSetC.h"

/**
 * Cette classe abstraite est la base du design-pattern Strategy appliqué
 * à la méthode de mutation de notre algorithme génétique. Elle définit une
 * seule méthode virtuelle pure execute() devant être redéfinie par les sous-
 * classes de Mutator représentant une implémentation de la méthode de mutation
 * d'un individu.
 * TODO Refactorisation lors de la mise en place du design-pattern Template
 * @author Ugo Rayer
 * 
 */

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
   * ItemSet. Doit être redéfinie dans chaque sous-classes
   * @param ItemSet* individu à muter
   * @author Ugo Rayer
   */
   virtual ItemSet* execute(ItemSet* p1) = 0;
      
  /**
   * Méthode effectuant la mutation d'un individu passé en paramètre
   * ItemSet. Doit être redéfinie dans chaque sous-classes
   * @param ItemSetC* individu à muter
   * @author Ugo Rayer
  */
  virtual ItemSetC* execute(ItemSetC* p1) = 0;
  
};

#endif
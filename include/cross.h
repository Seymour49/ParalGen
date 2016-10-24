#ifndef CROSS_H
#define CROSS_H

#include <iostream>
#include "individual.h"
#include "itemSet.h"
#include "itemSetC.h"

/**
 * Cette classe abstraite est la base du design-pattern Strategy appliqué
 * à la méthode de croisement de notre algorithme. Elle définit une seule 
 * méthode virtuelle pure execute devant être redéfinie par les sous-classes 
 * représentant une implémentation de la méthode de croisement entre deux 
 * individus.
 * TODO Refactorisation lors de la mise en place du design-pattern Template
 * @author Ugo Rayer
 * 
 */

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
   * Méthode effectuant le croisement entre deux itemsets de classe
   * ItemSet. Doit être redéfinie dans chaque sous-classes
   * @author Ugo Rayer
   */
   virtual ItemSet* execute(ItemSet* p1, ItemSet* p2) = 0;
      
/**
  * Méthode effectuant le croisement entre deux itemsets de classe
  * ItemSetC. Doit être redéfinie dans chaque sous-classes
  * @author Ugo Rayer
  */
  virtual ItemSetC* execute(ItemSetC* p1, ItemSetC* p2) = 0;
  
};

#endif
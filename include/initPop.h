#ifndef INITPOP_H
#define INITPOP_H

#include <iostream>
#include "individual.h"
#include "itemSet.h"
#include "itemSetC.h"


/**
 * Cette classe abstraite est la base du design-pattern Strategy appliqué
 * à la méthode d'initialisation de la population de notre algorithme. 
 * Elle définit une seule méthode virtuelle pure execute devant être redéfinie
 * par les sous-classes représentant une implémentation de la méthode de
 * création de la population initiale de l'algorithme génétique.
 * TODO Refactorisation lors de la mise en place du design-pattern Template
 * @author Ugo Rayer
 * 
 */

class InitPop {
  
public:
  

  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  virtual ~InitPop() {}
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  /**
   * Méthode effectuant le croisement entre deux itemsets de classe
   * ItemSet. Doit être redéfinie dans chaque sous-classes
   * @author Ugo Rayer
   */
   virtual void execute(std::vector<ItemSet*> *pop,unsigned taillePop) = 0;
      
/**
  * Méthode effectuant le croisement entre deux itemsets de classe
  * ItemSetC. Doit être redéfinie dans chaque sous-classes
  * @author Ugo Rayer
  */
  virtual void execute(std::vector<ItemSetC*>* pop,unsigned taillePop) = 0;
  
  
};

#endif
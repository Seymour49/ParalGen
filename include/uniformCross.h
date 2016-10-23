#ifndef UNIFORMCROSS_H
#define UNIFORMCROSS_H

#include <iostream>
#include "cross.h"

/* Inclusion des différentes structures de données pour lesquelles la
 * méthode execute()
 */
#include "itemSet.h"
#include "itemSetC.h"

/**
 * Croisement uniforme entre deux individus. Chaque bit de l'enfant à 50%
 * de chances de provenir du parent1 ou du parent 2.
 * @author Ugo 
 */

class UniformCross : public Cross {
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
/**
 * Constructeur par défaut et unique.
 * @author Ugo Rayer
 */
  UniformCross();
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
/**
 * Redéfinition du destructeur virtuel
 */
  ~UniformCross();
  
  /* * * * * *
   * METHODS *
   * * * * * */
  
/**
 * Croisement uniforme entre deux individus de type ItemSet via vector.
 * Renvoie une erreur si :
 * - Parent null
 * - Parents de taille différentes
 * @param ItemSet parent1
 * @param ItemSet parent2
 * @return ItemSet enfant
 * @author Ugo Rayer, Johan Defaye
 */  
  ItemSet* execute(ItemSet* p1, ItemSet* p2);
  
/**
 * Croisement uniforme entre deux individus de type ItemSetC via char*.
 * Renvoie une erreur si :
 * - Parent null
 * - Parents de taille différentes
 * @param ItemSetC parent1
 * @param ItemSetC parent2
 * @return ItemSetC enfant
 * @author Ugo Rayer, Johan Defaye
 */  
  ItemSetC* execute(ItemSetC* p1, ItemSetC* p2);
  
};

#endif
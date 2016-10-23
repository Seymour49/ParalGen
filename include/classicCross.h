#ifndef CLASSICCROSS_H
#define CLASSICCROSS_H

#include <iostream>
#include "cross.h"

/* Inclusion des différentes structures de données pour lesquelles la
 * méthode execute()
 */
#include "itemSet.h"
#include "itemSetC.h"

/**
 * Croisement monopoint classique. Un unique pivot est nécessaire
 * @author Ugo 
 */

class ClassicCross : public Cross {
private:
  size_t _pivot;
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
/**
 * Unique constructeur nécessitant un pivot.
 * @param size_t pivot
 * @author Ugo Rayer
 */
  ClassicCross(size_t pivot);
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
/**
 * Redéfinition du destructeur virtuel
 */
  ~ClassicCross();
  
  /* * * * * *
   * METHODS *
   * * * * * */
  
/**
 * Croisement monopoint entre deux individus de type ItemSet via vector.
 * Renvoie une erreur si :
 * - Parent null
 * - Pivot trop grand (TODO voir utilisation de modulo(p1.size())
 * - Parents de taille différentes
 * @param ItemSet parent1
 * @param ItemSet parent2
 * @return ItemSet enfant
 * @author Ugo Rayer, Johan Defaye
 */  
  ItemSet* execute(ItemSet* p1, ItemSet* p2);
  
/**
 * Croisement monopoint entre deux individus de type ItemSetC via char*.
 * Renvoie une erreur si :
 * - Parent null
 * - Pivot trop grand (TODO voir utilisation de modulo(p1.size())
 * - Parents de taille différentes
 * @param ItemSetC parent1
 * @param ItemSetC parent2
 * @return ItemSetC enfant
 * @author Ugo Rayer, Johan Defaye
 */  
  ItemSetC* execute(ItemSetC* p1, ItemSetC* p2);
  
};

#endif
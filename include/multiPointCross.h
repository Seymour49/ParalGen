#ifndef MULTIPOINTCROSS_H
#define MULTIPOINTCROSS_H

#include <iostream>
#include "cross.h"

/* Inclusion des différentes structures de données pour lesquelles la
 * méthode execute()
 */
#include "itemSet.h"
#include "itemSetC.h"

/**
 * Croisement multi-points. Un ensemble de pivots triés est nécessaire.
 * On vérifiera à l'exécution que les pivots sont présents et moins 
 * nombreux que le nombre d'items à croiser.
 * @author Ugo 
 */

class MultiPointCross : public Cross {
private:
  unsigned _nbPivots;
  size_t* _pivots;
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
/**
 * Unique constructeur nécessitant un pointeur sur size_t (ie un ensemble 
 * de pivots). Si le pointeur est non-nul, il contient au moins 1 pivot et
 * le croisement sera au minimum classique.
 * @param size_t* pivots
 * @author Ugo Rayer
 */
 MultiPointCross(size_t* pivots,unsigned nbPivots);
 
 /* * * * * * * *
  * DESTRUCTOR  *
  * * * * * * * */
/**
 * Redéfinition du destructeur virtuel
 */
  ~MultiPointCross();
  
   /* * * * * *
   * METHODS *
   * * * * * */
  
/**
 * Croisement multipoints entre deux individus de type ItemSet via vector.
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
 * Croisement multipoints entre deux individus de type ItemSetC via char*.
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
#ifndef MUTATOR_H
#define MUTATOR_H

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
 * @author Ugo Rayer
 * 
 */

class Mutator {
  
public:
    virtual Individual* execute(Individual* p1, Individual* p2)= 0;
  
};

#endif
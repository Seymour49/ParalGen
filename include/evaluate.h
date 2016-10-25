#ifndef EVALUATE_H
#define EVALUATE_H

#include <iostream>
#include "itemSet.h"
#include "itemSetC.h"
#include "dataSet.h"
#include "dataSetC.h"

/**
 * Cette classe abstraite est la base du design-pattern Strategy appliqué à 
 * la fonction d'évaluation de notre algorithme. Elle définit une seule méthode
 * virtuelle pure execute() devant être redéfinie par les sous-classes repré-
 * sentant un objectif à évaluer.
 * TODO Refactorisation lors de la mise en place du design-pattern Template
 * @author Ugo Rayer
 * 
 */

class Evaluate {

public:

  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  virtual ~Evaluate() {}
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
/**
 * Méthode évaluant un individu de type itemSet vis à vis d'un jeu de 
 * données de même type passés en paramètres.
 * @param ItemSet* individu à évaluer
 * @param DataSet* jeu de données
 * @author Ugo Rayer
 */
  virtual void execute(ItemSet* ind, DataSet* data) = 0;

/**
 * Méthode évaluant un individu de type itemSetC vis à vis d'un jeu de 
 * données de même type passés en paramètres.
 * @param ItemSetC* individu à évaluer
 * @param DataSetC* jeu de données
 * @author Ugo Rayer
 */
  virtual void execute(ItemSetC* ind, DataSetC* data) = 0;
    
};

#endif
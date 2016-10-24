#ifndef RANDOMMUTATOR_H
#define RANDOMMUTATOR_H

#include <iostream>
#include "mutator.h"

/* Inclusion des différentes structures de données pour lesquelles la
 * méthode execute()
 */
#include "itemSet.h"
#include "itemSetC.h"

/**
 * Classe implémentant une mutation unique et aléatoire sur un individu.
 * Un bit aléatoire est sélectionné et sa valeur nous flipons sa valeur.
 * @author Ugo Rayer
 * 
 */
class RandomMutator: public Mutator {
public:
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
/**
 * Constructeur unique. Ne nécessite pas de paramètres
 * car tout est calculé.
 * @author Ugo Rayer
 */
  RandomMutator();
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
/**
 * Redéfinition du destructeur virtuel
 * @author Ugo Rayer
 */
  ~RandomMutator();
  
  /* * * * * *
   * METHODS *
   * * * * * */
  
/**
 * Mutation aléatoire d'un individu de type ItemSet passé en paramètre.
 * Renvoie une erreur si :
 * - individu null
 * @param ItemSet* individu à muter
 * @author Ugo Rayer
 */
  ItemSet* execute(ItemSet* p1);
  
/**
 * Mutation aléatoire d'un individu de type ItemSetC passé en paramètre.
 * Renvoie une erreur si :
 * - individu null
 * @param ItemSetC* individu à muter
 * @author Ugo Rayer 
 */
  ItemSetC* execute(ItemSetC* p1);
};

#endif
#ifndef EVALUATE_H
#define EVALUATE_H

#include <iostream>
#include "individual.h"

/**
 * Cette classe abstraite est la base du design-pattern Strategy appliqué à 
 * la fonction d'évaluation de notre algorithme. Elle définit une seule méthode
 * virtuelle pure execute() devant être redéfinie par les sous-classes repré-
 * sentant un objectif à évaluer.
 * TODO Refactorisation lors de la mise en place du design-pattern Template
 * @author Ugo Rayer
 * 
 */

template <typename T>
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
 * Méthode évaluant un individu 
 * Modifie l'attribut score d'un individu
 * @param ind: individu à évaluer
 * @author Ugo Rayer, Johan Defaye
 */
  virtual void execute(Individual<T> & ind) = 0;

  virtual void executeO(Individual<T> &ind);
};

#endif
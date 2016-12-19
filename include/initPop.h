#ifndef INITPOP_H
#define INITPOP_H

#include <iostream>
#include <vector>
#include "individual.h"


/**
 * Cette classe abstraite est la base du design-pattern Strategy appliqué
 * à la méthode d'initialisation de la population de notre algorithme. 
 * Elle définit une seule méthode virtuelle pure execute devant être redéfinie
 * par les sous-classes représentant une implémentation de la méthode de
 * création de la population initiale de l'algorithme génétique.
 * @author Ugo Rayer, Johan Defaye
 * 
 */
template <typename T>
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
   * Méthode initialisant une population d'individu
   * @author Ugo Rayer
   */
   virtual void execute(std::vector<Individual<T>* > & pop) = 0;
  
  
};

#endif
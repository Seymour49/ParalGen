#ifndef UNIFORMCROSS_H
#define UNIFORMCROSS_H

#include <iostream>
#include "cross.h"

/**
 * Croisement uniforme entre deux individus. Chaque bit de l'enfant à 50%
 * de chances de provenir du parent1 ou du parent 2.
 * @author Ugo 
 */

template <typename T>
class UniformCross : public Cross<T> {
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
/**
 * Constructeur par défaut
 * @author Ugo Rayer
 */
  UniformCross() {}
  
  
/**
 * Constructeur par recopie
 * @author Ugo Rayer
 */
  UniformCross(const UniformCross<T> & u) {}

  
  /* * * * * *
   * METHODS *
   * * * * * */
  
  
/**
 * Croisement multipoint entre deux individus de type Individual<T>
 * Renvoie une erreur si :
 * - Un des parent vide
 * - Pivot trop grand (TODO voir utilisation de modulo(p1.size())
 * - Parents de taille différentes
 * @param parent1 : parent1
 * @param parent2 : parent2
 * @param efant : Enfant résultant du croisement de parent1 et parent2
 * @author Ugo Rayer, Johan Defaye
 */
  void execute(const Individual<T> & parent1, const Individual<T> & parent2, Individual<T> & enfant) {
    if( parent1.size() == 0 || parent2.size() == 0) throw std::string("Erreur, un des individu parent est vide");
    else if( parent1.size() != parent2.size() ) throw std::string("Erreur, individus parents de taille différente");
    else {
      enfant.resize(parent1.size());
      int alea;
      for(unsigned int i = 0; i < parent1.size(); ++i){
	alea = rand() % 2;
	if (alea == 0) enfant[i] = parent1[i];
	else enfant[i] = parent2[i];
      }
    } 
  }
  
};

#endif
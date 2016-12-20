#ifndef CLASSICCROSS_H
#define CLASSICCROSS_H

#include <iostream>
#include "cross.h"

/**
 * Croisement monopoint classique. Un unique pivot est nécessaire
 * @author Ugo 
 */
template <typename T>
class ClassicCross : public Cross<T> {
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
/**
 * Unique constructeur
 * @author Ugo Rayer
 */
  ClassicCross()
  {}
  
  
  /**
   * Constructeur par recopie
   * @param cc : Un autre operateur de croisement classique
   * @author Johan Defaye
   */
  ClassicCross(const ClassicCross<T> & cc)
  {}
  
  
  /* * * * * *
   * GETTER  *
   * * * * * */

  
  /* * * * * *
   * METHODS *
   * * * * * */
  
  
/**
 * Croisement monopoint entre deux individus de type Individual<T>
 * Renvoie une erreur si :
 * - Pivot trop grand (TODO voir utilisation de modulo(p1.size())
 * - Parents de taille différentes
 * @param parent1 : parent1
 * @param parent2 : parent2
 * @param efant : Enfant résultant du croisement de parent1 et parent2
 * @author Ugo Rayer, Johan Defaye
 */
  void execute(const Individual<T> & parent1, const Individual<T> & parent2, Individual<T> & enfant) {
    
    if ( parent1.size() != parent2.size()) throw std::string("Erreur, individus parents de tailles différentes");
    else {
      unsigned int alea = rand() % parent1.size();
      enfant.resize(parent1.size());
      for (unsigned int i = 0; i < alea; ++i) {
	  enfant[i] = parent1[i];
      }
      for (unsigned int j = alea ; j < parent2.size(); ++j) {
	  enfant[j] = parent2[j];
      }
    }
  }
  
  
  /* * * * * * * * * * * * *
   * OPERATOR OVERLOADING  *
   * * * * * * * * * * * * */
  
  ClassicCross<T> & operator=(const ClassicCross<T> & c) {
    return *this;
  }
  
};

#endif
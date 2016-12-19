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
  ClassicCross(size_t pivot): _pivot(pivot)
  {}
  
  
  /**
   * Constructeur par recopie
   * @param cc : Un autre operateur de croisement classique
   * @author Johan Defaye
   */
  ClassicCross(const ClassicCross<T> & cc): _pivot(cc.getPivot())
  {}
  
  
  /* * * * * *
   * GETTER  *
   * * * * * */
  
  size_t getPivot() const { return _pivot; }
  

  
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
      enfant.resize(parent1.size());
      for (unsigned int i = 0; i < _pivot; ++i) {
	  enfant[i] = parent1[i];
      }
      for (unsigned int j =_pivot ; j < parent2.size(); ++j) {
	  enfant[j] = parent2[j];
      }
    }
  }
  
  
  /* * * * * * * * * * * * *
   * OPERATOR OVERLOADING  *
   * * * * * * * * * * * * */
  
  ClassicCross<T> & operator=(const ClassicCross<T> & c) {
    _pivot = c.getPivot();
    return *this;
  }
  
};

#endif
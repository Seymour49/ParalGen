#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
/**
 * Classe abstraite représentant un individu générique.
 * Dispose de méthodes de mutation et de croisement.
 * On conserve pour un individu son âge et son score.
 * @author Ugo Rayer
 */

class Individual {

private:
  int _age;
  float _score;
  
public:
  /**
   * Destructeur
   */
  virtual ~Individual() {}
  
  /* * * * * * 
   * GETTERS *
   * * * * * */
  int getAge() const { return _age; }
  float getScore() const { return _score; }
  
  /* * * * * * 
   * SETTERS *
   * * * * * */
  void setScore(float s);
  void setAge(int a);
  
/**
  * Incrémente l'âge d'une unité
  */
  void incAge() {++_age;}
 
  /* * * * * * * * * * * * *
   * SURCHARGE D'OPÉRATEUR *
   * * * * * * * * * * * * */
  
  
  
/** 
  * Affiche l'ItemSet dans le flux passé en paramètre
  * @param flux Un flux pour l'affichage
  */
  virtual void print(std::ostream & flux) const;
  
  
};


/** 
* Surcharge de l'opérateur d'affichage
* @param flux Un flux pour l'affichage
* @param i Individu à afficher
*/
std::ostream& operator<<(std::ostream &flux, const Individual & i);

  


#endif
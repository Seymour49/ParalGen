#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <vector>
/**
 * Classe abstraite représentant un individu générique.
 * Un individu doit cependant posséder l'opérateur d'affectation [] car il représente un ensemble.
 * On conserve pour un individu son âge et son score.
 * @author Ugo Rayer
 */

template <typename T>
class Individual {

private:
  int _age;
  float _score;

public:
  
  Individual(): _age(0), _score(0.0)
  {}
  
  Individual(unsigned int age, float score = 0.0): _age(age), _score(score)
  {}
  
  Individual(const Individual<T> & ind): _age(ind.getAge()), _score(ind.getScore())
  {}
  
  /* * * * * * 
   * GETTERS *
   * * * * * */
  
  int getAge() const { return _age; }
  float getScore() const { return _score; }
  virtual unsigned int size() const =0;
  virtual std::vector<T> get() const = 0;
  
  
  /* * * * * * 
   * SETTERS *
   * * * * * */
  
  
  void setScore(float s) {_score = s;}
  void setAge(int a) {_age = a;}
  
  /**
   * Incrémente l'âge d'une unité
   */
  void incAge() {++_age;}
  
  /**
   * Réserve l'emplacement mémoire nécessaire
   * @param size : Nouvelle taille de l'emplacement mémoire
   * @author Johan Defaye
   */
  virtual void resize(unsigned int size) =0;
 
  /* * * * * * * * * * * * *
   * SURCHARGE D'OPÉRATEUR *
   * * * * * * * * * * * * */
  
  
/** 
 * Affiche l'ItemSet dans le flux passé en paramètre
 * @param flux Un flux pour l'affichage
 */
  virtual void print(std::ostream & flux) const {
    flux << "Age : " << _age << "; Score : " << _score << std::endl;
  }
  
/**
 * Opérateur d'accès qui permet d'accéder au i ème élément d'un individu
 * @param indice : Indice de l'élément à accéder
 * @return La valeur à l'indice donné en paramètre
 * @author Johan Defaye
 */
  virtual T& operator[] (unsigned int indice) =0;
  
/**
 * Opérateur d'accès qui permet d'accéder au i ème élément d'un individu sans possibilité de le modifier
 * @param indice : Indice de l'élément à accéder
 * @return La valeur à l'indice donné en paramètre
 * @author Johan Defaye
 */
  virtual const T& operator[] (unsigned int indice) const =0;
  
  
  
  /**
   * Opérateur d'affectation
   * @param i : un autre individu
   * @author Johan Defaye
   */
  virtual Individual<T> & operator=(const Individual<T> & i)
  {
    _age = i.getAge();
    _score = i.getScore();
    
    if (size() != i.size()) resize(i.size());
    for (unsigned int j = 0; j < size(); ++j) {
      (*this)[j] = i[j];
    }
    
    return *this;
  }
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  
  virtual ~Individual() {}
  
};

/** 
 * Surcharge de l'opérateur d'affichage
 * @param flux Un flux pour l'affichage
 * @param i Individu à afficher
 */
template <typename T>
std::ostream& operator<<(std::ostream &flux, const Individual<T> & i) {
  i.print(flux);
  return flux;
}


#endif
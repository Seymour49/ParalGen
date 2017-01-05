#ifndef RANDOMMUTATOR_H
#define RANDOMMUTATOR_H

#include <iostream>
#include <vector>
#include "mutator.h"


/**
 * Classe implémentant une mutation unique et aléatoire sur un individu.
 * Un bit aléatoire est sélectionné et nous flipons sa valeur.
 * @author Ugo Rayer
 */
template <typename T>
class RandomMutator: public Mutator<T> {
  
private:
  std::vector<T> _listParam;
  
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
/**
  * Constructeur unique
  * @param listParam : Liste des valeurs possible que peut prendre un élement d'un individu
  * @author Ugo Rayer
  */
  RandomMutator(const std::vector<T> & listParam): _listParam(listParam)
  {}
  
  
/**
  * Constructeur par recopie
  * @param rm : Un autre randomMutator
  * @author Johan Defaye
  */
  RandomMutator(const RandomMutator<T> & rm): _listParam(rm.getListParam())
  {}
  
  
  /* * * * * *
   * GETTER  *
   * * * * * */
  
  std::vector<T> getListParam() const { return _listParam; }
  
  
  /* * * * * *
   * METHODS *
   * * * * * */
  
/**
 * Mutation aléatoire d'un individu passé en paramètre.
 * Renvoie une erreur si :
 * - individu vide
 * @param ind: individu à muter
 * @return L'individu après la mutation
 * @author Ugo Rayer, Johan Defaye
 */
  void execute(Individual<T> & ind) {
    if (ind.size() == 0) throw std::string("Erreur, l'individu à muter est vide (randomMutator)");
    else {
      ind.setAge(0);
      int pivot = rand() % (ind.size());
      int indElement = rand() % (_listParam.size());
      while (_listParam[indElement] == ind[pivot]) {
	indElement = rand() % (_listParam.size());
      }
      ind[pivot] = _listParam[indElement];
    }
  }

  
};

#endif
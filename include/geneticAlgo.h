#ifndef GENETICALGO_H
#define GENETICALGO_H

#include "individual.h"
#include "itemSet.h"
#include "itemSetO.h"
#include "mutator.h"
#include "cross.h"
#include "evaluate.h"
#include "initPop.h"
#include "selectPolicy.h"
#include "indelPolicy.h"

#include <vector>

/**
 * Cette classe implémente un algorithme génétique
 * pour la recherche d'itemset fréquent. Elle gère une
 * population constante d'individus qu'elle croise et
 * fait muter pendant un nombre d'itérations passé en 
 * paramètre.
 */

template <typename T>
class GeneticAlgo {
  
private:
  
    Mutator<T> * _mutator;
    Cross<T> * _cross;
    Evaluate<T> * _eval;
    InitPop<T> * _initPop;
    SelectPolicy<T> * _select;
    IndelPolicy<T> * _insert;
    
    unsigned int _nbIteration;
    std::vector<Individual<T>*> _population;
        
    
public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur prenant un nombre d'itérations, une taille de population, un seuil de fréquence et un opérateur de mutation et de croisement
  * en paramètres.
  * @param ind : Type d'individu à manipuler
  * @param mut : opérateur de mutation
  * @param cross : opérateur de croisement
  * @param init : opérateur d'initialisation de la population
  * @param select : politique de sélection des individu pour le croisement
  * @param insert : politique de suppression d'un individu en faveur d'un autre individu résultant d'un croisement
  * @param taillePop : Taille de la population à manipuler
  * @param it : nombre d'itérations de l'algorithme
  * @param seuilFrequence : seuil minimum de fréquence
  * @author Ugo Rayer
  */
  GeneticAlgo(Individual<T> * const ind, Mutator<T>* const mut, Cross<T> * const cross, Evaluate<T> * const eval, InitPop<T> * const init, SelectPolicy<T> * const select, IndelPolicy<T> * const insert, unsigned int taillePop = 100, unsigned int it = 10000)
  :_mutator(mut), _cross(cross), _eval(eval), _initPop(init), _select(select), _insert(insert), _nbIteration(it), _population(taillePop)
  {
    if (ind != NULL) {
      ItemSet<T> * itemset = dynamic_cast<ItemSet<T> *>(ind);
      ItemSetO<T> * itemsetO = dynamic_cast<ItemSetO<T> *>(ind);
      
      if (itemset != NULL) {
	for (unsigned int i = 0; i < taillePop; ++i) {
	  _population[i] = new ItemSet<T>;
	}
      }
      else if (itemsetO != NULL){
	for (unsigned int i = 0; i < taillePop; ++i) {
	  _population[i] = new ItemSetO<T>;
	}
      }
    }
  }
  
  /* * * * * * * * * 
   *   DESTRUCTOR  *
   * * * * * * * * */
  ~GeneticAlgo()
  {
    for (unsigned int i = 0; i < _population.size(); ++i) {
      delete _population[i];
    }
  }
  
  /* * * * * * * * * 
   *  ACCESSEURS   *
   * * * * * * * * */
  unsigned int getNbIteration() const { return _nbIteration; }
  
  unsigned int getTaillePop() const { return _population.size(); }
      
  /* * * * * * 
   * METHODS *
   * * * * * */

  
/**
 * Méthode effectuant une mutation sur un individu de la population.
 * Prend en paramètre l'indice de l'individu dans la population.
 * Renvoie une erreur si l'indice n'est pas dans la population
 * @param int indice de l'individu à muter
 * @author Ugo Rayer
 */
  void doMutationFor(unsigned ind)
  {
    if (ind > (_population.size() - 1) || ind < 0) throw std::string("Erreur, indice de l'individu à muter hors de la population");
    else _mutator->execute(*_population[ind]);
  }
  
/**
 * Méthode effectuant un croisement sur deux individus de la population.
 * Prend en paramètre les deux indices des individus parents
 * Renvoie une erreur si les indices sont en dehors de la population.
 * @param indParent1 : indice du premier parent
 * @param indParent2 : indice du deuxième parent
 * @param indEnfant  : indice de l'enfant
 * @author Ugo Rayer
 */
  void doCrossFor(unsigned int indParent1, unsigned int indParent2, unsigned int indEnfant)
  {
    if( (indParent1 < 0) || (indParent2 < 0) || (indParent1 > (_population.size() - 1)) || (indParent2 > (_population.size() - 1)) ) throw std::string("Erreur, indices des parents hors de la population");
    else if ((indEnfant < 0) || (indEnfant > (_population.size() - 1))) throw std::string("Erreur, indice de l'enfant hors de la population");
    else _cross->execute(*(_population[indParent1]), *(_population[indParent2]), *(_population[indEnfant]));
  }
  
/**
  * Méthode permettant d'incrémenter l'âge de toute la population
  * @author Johan Defaye
  */
  void incAgePop()
  {
    for (unsigned int i = 0; i < _population.size(); ++i) {
      _population[i]->incAge();
    }
  }
  
  
  /**
   * Intialise la population en appelant la méthode d'exécution de l'attribut initPop
   * @author Johan Defaye
   */
  void initPop()
  {
    _initPop->execute(_population);
  }
  
  /**
   * Évalue toute la population en mettant à jour les score de chaque individu
   * @author Johan Defaye
   */
  void evalPop()
  {
    for (unsigned int i = 0; i < _population.size(); ++i) {
      _eval->execute(*(_population[i]));
    }
  }
  
/**
 * Méthode principale de la classe. Lance l'algorithme génétique avec un nombre d'itération 
 * et une taille de population définit dans le constructeur.
 * @author Johan Defaye
 */
  void run()
  {
  }
  
/**
 * Méthode d'affichage de la population utile pendant le dev.
 * @author Ugo Rayer
 */
  void displayPopulation()
  {
    std::cout << "La population actuelle est la suivante : " << std::endl;
    for (unsigned int i = 0; i < _population.size(); ++i) {
      std::cout << *(_population[i]) << std::endl;
    }
  }

};

#endif
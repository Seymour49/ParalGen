#ifndef GENETICALGO_H
#define GENETICALGO_H

#include "individual.h"
#include "dataSet.h"
#include "randomMutator.h"
#include "uniformCross.h"
#include "multiPointCross.h"
#include "classicCross.h"
#include "freqEval.h"
#include "randomPop.h"
#include "freqPop.h"
#include <vector>
#include <ctime>

/**
 * Cette classe implémente un algorithme génétique
 * pour la recherche d'itemset fréquent. Elle gère une
 * population constante d'individus qu'elle croise et
 * fait muter pendant un nombre d'itérations passé en 
 * paramètre.
 * 
 */

class GeneticAlgo {
  
private:
    unsigned int _nbIteration;
    unsigned int _taillePop;
    DataSet* _data;
    std::vector<ItemSet*>* _population;
    float _seuilFrequence; // TODO Définir _seuilFrequence comme un argument à définir par l'utilisateur pour l'initFreqPop
    Mutator* _mutator;
    Cross* _cross;
    Evaluate* _eval;
    InitPop* _init;
    
    
public:
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
   
/** 
  * Constructeur par défaut d'un algo génétique
  * @author Ugo Rayer
  */
  GeneticAlgo();
  
/** 
  * Constructeur prenant un nombre d'itérations, une taille de population, 
  * un seuil de fréquence et un opérateur de mutation et de croisement
  * en paramètres.
  * @param it : nombre d'itérations de l'algorithme
  * @param pop : taille de la population à gérer
  * @param seuilFrequence : seuil minimum de fréquence
  * @param mut : opérateur de mutation
  * @param cross : opérateur de croisement
  * @author Ugo Rayer
  */
  GeneticAlgo(unsigned int it, unsigned int pop, float seuilFrequence, Mutator* mut,
	      Cross* cross, Evaluate* eval, InitPop* init);
  
  /* * * * * * * * * 
   *   DESTRUCTOR  *
   * * * * * * * * */
  ~GeneticAlgo();
  
  /* * * * * * * * * 
   *  ACCESSEURS   *
   * * * * * * * * */
  unsigned int getNbIteration() const { return _nbIteration; }
  
  unsigned int getTaillePop() const { return _taillePop; }
  
  DataSet* getDataSet() const { return _data; }
  
  void setData(DataSet* input);
  
  std::vector<ItemSet*>* getPopulation() const { return _population; }
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
/**
 * Méthode évaluant l'ensemble de la population et devant être appelée après
 * l'initialisation de la population
 * @author Ugo Rayer
 */  
  void EvalPop();
  

/**
 * Méthode initialisation la population via la méthode passée 
 * en paramètre de la classe
 * Retourne une erreur si :
 *  - vecteur non vide
 * @author Ugo Rayer
 */  
  void initPop();

/**
 * Méthode effectuant une mutation sur un individu de la population.
 * Prend en paramètre l'indice de l'individu dans la population.
 * Renvoie une erreur si l'indice n'est pas dans la population
 * @param int indice de l'individu à muter
 * @author Ugo Rayer
 */
  void doMutation(unsigned ind);
  
/**
 * Méthode effectuant un croisement sur deux individus de la population.
 * Prend en paramètre les deux indices des individus parents
 * Renvoie une erreur si les indices sont en dehors de la population.
 * @param int indice du parent 1
 * @param int indice du parent 2
 * @author Ugo Rayer
 */
  void doCrossFor(unsigned id1, unsigned id2);
  
/**
  * Méthode permettant d'incrémenter l'âge de toute la population
  * @author Johan Defaye
  */
  void incAgePop();
  
/**
 * Méthode principale de la classe. Lance l'algorithme génétique avec un nombre d'itération 
 * et une taille de population définit dans le constructeur.
 * @author Johan Defaye
 */
  void run();
  
/**
 * Méthode d'affichage de la population utile pendant le dev.
 * @author Ugo Rayer
 */
  void displayPopulationAt(unsigned ind);
  
  /**
 * Méthode d'affichage de la population utile pendant le dev.
 * @author Ugo Rayer
 */
  void displayPopulation();


};

#endif
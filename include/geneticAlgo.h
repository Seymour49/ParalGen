#ifndef GENETICALGO_H
#define GENETICALGO_H

#include "individual.h"
#include "dataSet.h"
#include "dataSetC.h"
#include "randomMutator.h"
#include "uniformCross.h"
#include "multiPointCross.h"
#include "classicCross.h"
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
    std::vector<Individual*> _population;
    float _seuilFrequence; // TODO Définir _seuilFrequence comme un argument à définir par l'utilisateur pour l'initFreqPop
    Mutator* _mutator;
    Cross* _cross;
    
    
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
  * Constructeur prenant un nombre d'itérations et une taille de population
  * en paramètres.
  * @param it : nombre d'itérations de l'algorithme
  * @param pop : taille de la population à gérer
  * @author Ugo Rayer
  */
  GeneticAlgo(unsigned int it, unsigned int pop, float seuilfrequence, Mutator* mut, Cross* cross);
  
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
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
/** 
  * Méthode initialisant une population de manière totalement aléatoire.
  * @author Ugo Rayer
  */
  void initRandomPop();
  
/**
 * Méthode effectuant une mutation sur un individu de la population.
 * Prend en paramètre l'indice de l'individu dans la population.
 * Renvoie une erreur si l'indice n'est pas dans la population
 * @param int indice de l'individu à muter
 * @author Ugo Rayer
 */
  void doMutationFor(unsigned ind);
  
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
  * Méthode initialisant une population de manière réfléchie.
  * Nous allons chercher à instancier des individus représentant
  * des itemsets composés d'item fréquents.
  * @author Johan Defaye
  */
  void initFreqPop();
  
  
  
/**
 * Méthode d'affichage de la population utile pendant le dev.
 * @author Ugo Rayer
 */
  void displayPopulation();

  
};

#endif
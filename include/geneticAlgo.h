#ifndef GENETICALGO_H
#define GENETICALGO_H

#include "individual.h"
#include "dataSet.h"
#include <vector>

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
    int _nbIteration;
    int _taillePop;
    DataSet* data;
    std::vector<Individual*> _population;
    
    
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
  GeneticAlgo(int it, int pop);
  
  /* * * * * * * * * 
   *   DESTRUCTOR  *
   * * * * * * * * */
  ~GeneticAlgo();
  
  /* * * * * * * * * 
   *  ACCESSEURS   *
   * * * * * * * * */
  int getNbIteration() const { return _nbIteration; }
  
  int getTaillePop() const { return _taillePop; }
  
  DataSet* getDataSet() const { return data; }
  
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
  * Méthode initialisant une population de manière réfléchie.
  * Nous allons chercher à instancier des individus représentant
  * des itemsets composés d'item fréquents.
  * @author Ugo Rayer
  */
  void initFreqPop();
  
/**
 * Méthode d'affichage de la population utile pendant le dev.
 * @author Ugo Rayer
 */
  void displayPopulation();

  
};

#endif
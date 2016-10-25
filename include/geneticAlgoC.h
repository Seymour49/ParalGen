#ifndef GENETICALGOC_H
#define GENETICALGOC_H

#include "individual.h"
#include "dataSetC.h"
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

class GeneticAlgoC {
  
private:
    unsigned int _nbIteration;
    unsigned int _taillePop;
    DataSetC* _data;
    std::vector<Individual*> _population;
    float _seuilFrequence; // TODO Définir _seuilFrequence comme un argument à définir par l'utilisateur
    
    
public:
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
   
/** 
  * Constructeur par défaut d'un algo génétique
  * @author Ugo Rayer
  */
  GeneticAlgoC();
  
/** 
  * Constructeur prenant un nombre d'itérations et une taille de population
  * en paramètres.
  * @param it : nombre d'itérations de l'algorithme
  * @param pop : taille de la population à gérer
  * @author Ugo Rayer
  */
  GeneticAlgoC(unsigned int it, unsigned int pop, float seuilFrequence);
  
  /* * * * * * * * * 
   *   DESTRUCTOR  *
   * * * * * * * * */
  ~GeneticAlgoC();
  
  /* * * * * * * * * 
   *  ACCESSEURS   *
   * * * * * * * * */
  unsigned int getNbIteration() const { return _nbIteration; }
  
  unsigned int getTaillePop() const { return _taillePop; }
  
  DataSetC* getDataSet() const { return _data; }
  
  void setData(DataSetC* input);
  
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
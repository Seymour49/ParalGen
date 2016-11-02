#ifndef GENETICALGOC_H
#define GENETICALGOC_H

#include "individual.h"
#include "dataSet.h"
#include "randomMutator.h"
#include "uniformCross.h"
#include "multiPointCross.h"
#include "classicCross.h"
#include "evaluate.h"
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

class GeneticAlgoC {
  
private:
    unsigned int _nbIteration;
    unsigned int _taillePop;
    DataSetC* _data;
    std::vector<ItemSetC*>* _population;
    float _seuilFrequence; // TODO Définir _seuilFrequence comme un argument à définir par l'utilisateur
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
  GeneticAlgoC();
  
/** 
  * Constructeur prenant un nombre d'itérations et une taille de population
  * en paramètres.
  * @param it : nombre d'itérations de l'algorithme
  * @param pop : taille de la population à gérer
  * @author Ugo Rayer
  */
  GeneticAlgoC(unsigned int it, unsigned int pop, float seuilFrequence,
	       Mutator* mut, Cross* cross, Evaluate* eval, InitPop* init);
  
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
  
  std::vector<ItemSetC*>* getPopulation() const { return _population; }
  
  
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
 * Méthode effectuant la mutation via la méthode en paramètre de classe
 * selon un indice d'individu.
 * Retourne une erreur si :
 *  - indice en dehors de la population
 *  - population vide
 *  - mutateur null
 * @param unsigned indice de l'individu à muter dans la population
 * @author Ugo Rayer
 */
 ItemSetC* doMutation(unsigned ind);

/**
  * Méthode permettant d'incrémenter l'âge de toute la population
  * @author Johan Defaye
  */
  void incAgePop();
  
/**
 * Fonction booléenne vérifiant si l'ItemSetC passé en paramètre est présent
 * ou non dans la population.
 * @param ItemSetC* individu à tester
 * @return true si l'individu est dans la population, false sinon
 * @author Ugo Rayer
 */
  bool isPartOfPop(ItemSetC* ind);
  
/**
 * Méthode principale de l'algorithme. 
 * @author Ugo Rayer
 */
  void run();
  
/**
 * Méthode d'affichage d'un individu 
 * @param unsigned indice de l'individu
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
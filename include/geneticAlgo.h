#ifndef GENETICALGO_H
#define GENETICALGO_H

#include "individual.h"
#include "itemSet.h"
#include "itemSetO.h"
#include "dataSet.h"
#include "dataSetO.h"
#include "mutator.h"
#include "cross.h"
#include "indelPolicy.h"
#include "selectPolicy.h"
#include "evaluate.h"
#include "initPop.h"

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
    
    /* Modèle en îles */
    float* _tabMig;			// Tableau de _nbIsland float représentant les probabilité de migration
    SelectPolicy<T>* _selectMig;
    IndelPolicy<T>* _indelMig;
    
    /* Fin IM */
    
    unsigned int _nbIteration;
    float _probaM;
    float _probaC;
    std::vector<Individual<T>*> _population;
        
    unsigned int _typeFlag;
    
    /* Reprise du modèle en île */
    
    
    unsigned int _nbIsland;		// Nombre d'iles 
    unsigned int _idIsland;		// Position de l'ile sur la map
    std::string _unitaryName;		// Nom générique d'une ile (ex "Node") -> Utile pour le filesystem
    unsigned _stepM;			// Nombre de générations entre deux migrations
    
    unsigned _nbMigrants;
    
    
    
    // Méthodes
    // void checkFiles()
    // void readFile(File) -> Appel à _indelM
    
    // void writeFile(File) -> Appel à _selectMid
    
    
    
public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur prenant un nombre d'itérations, une taille de population, 
  * un seuil de fréquence et un opérateur de mutation et de croisement
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
  * @param probaM : probabilité de mutation
  * @param probaC : probabilité de croisement
  * @author Ugo Rayer, Johan Defaye
  */
  GeneticAlgo(Individual<T> * const ind, Mutator<T>* const mut, Cross<T> * const cross, 
	      Evaluate<T> * const eval, InitPop<T> * const init, SelectPolicy<T> * const select,
	      IndelPolicy<T> * const insert, float* tM,SelectPolicy<T> * const migS, IndelPolicy<T>* const migID,
	      unsigned int taillePop = 100, unsigned int it = 10000,
	      float pm = 0.005, float pc = 0.8, unsigned int nbI = 1, unsigned int id = 1,
	      std::string name = "Node", unsigned int step = 10)
  :_mutator(mut), _cross(cross), _eval(eval), _initPop(init), _select(select), _insert(insert),_tabMig(tM),
   _selectMig(migS), _indelMig(migID), _nbIteration(it),_probaM(pm), _probaC(pc),
  _population(taillePop),_nbIsland(nbI), _idIsland(id), _unitaryName(name), _stepM(step)
  {
    if (ind != NULL) {
      ItemSet<T> * itemset = dynamic_cast<ItemSet<T> *>(ind);
      ItemSetO<T> * itemsetO = dynamic_cast<ItemSetO<T> *>(ind);
      
      if (itemset != NULL) {
	for (unsigned int i = 0; i < taillePop; ++i) {
	  _population[i] = new ItemSet<T>;
	}
	_typeFlag = 0;
      }
      else if (itemsetO != NULL){
	for (unsigned int i = 0; i < taillePop; ++i) {
	  _population[i] = new ItemSetO<T>;
	}
	_typeFlag = 1;
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
  void doCrossFor(unsigned int indParent1, unsigned int indParent2, Individual<T> & ind)
  {
    if( (indParent1 < 0) || (indParent2 < 0) || (indParent1 > (_population.size() - 1)) || (indParent2 > (_population.size() - 1)) )
      throw std::string("Erreur, indices des parents hors de la population");
    else 
      _cross->execute(*(_population[indParent1]), *(_population[indParent2]), ind);
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
  void populate()
  {
    try{
      _initPop->executeO(_population);
      
    }
    catch(std::string E1){
	try{
	  _initPop->execute(_population);  

	}
	catch(std::string Excep){
	    std::cerr << E1 << " then " << Excep << std::endl;
	}
    }
  }
  
  /**
   * Évalue toute la population en mettant à jour les score de chaque individu
   * @author Johan Defaye
   */
  void evalPop()
  {
    
    for (unsigned int i = 0; i < _population.size(); ++i) {
      
      try{      
	  _eval->executeO(*(_population[i]));
      }
      catch(std::string E1){
	  try{
	      _eval->execute(*(_population[i]));
	  }
	  catch(std::string Excep){
	      std::cerr << E1 << " then " <<Excep << std::endl;
	  }
      }
    }
  }
  
/**
 * Méthode principale de la classe. Lance l'algorithme génétique avec un nombre d'itération 
 * et une taille de population définit dans le constructeur.
 * @author Johan Defaye, Ugo Rayer
 */
  void run()
  {
      try{
	
	  // Initialisation de la population
	  populate();
	  
	  // Evaluation de la population
	  evalPop();
	      
	  // Début de la boucle centrale
	  unsigned i=0;
	  while( i < _nbIteration ){
	      
	
	      Individual<T>* os1 = NULL;
	      Individual<T>* os2 = NULL;
	      
	      Individual<T>* tmp1 = NULL;
	      Individual<T>* tmp2 = NULL;
	      
	      if( _typeFlag == 0){
		  os1 = new ItemSet<T>();
		  os2 = new ItemSet<T>();
		  tmp1 = new ItemSet<T>();
		  tmp2 = new ItemSet<T>();
	      }
	      else if(_typeFlag == 1){
		  os1 = new ItemSetO<T>();
		  os2 = new ItemSetO<T>();
		  tmp1 = new ItemSet<T>();
		  tmp2 = new ItemSet<T>();
	      }
	      
	      std::pair<int,int> parents(_select->execute(_population));
	      
	      int alea = rand()% 1000;
	      
	      if( alea < _probaC*1000){
		  _cross->execute(*_population[parents.first], *_population[parents.second], *tmp1);
		  _cross->execute(*_population[parents.second],*_population[parents.first], *tmp2);

	      }
	      else{
		  *tmp1 = *_population[parents.first]; 
		  *tmp2 = *_population[parents.first];
	      }
	      
	      alea = rand()%1000;
	      if(alea < _probaM*1000){
		  _mutator->execute(*tmp1);
		  *os1 = *tmp1;
		  
		  _mutator->execute(*tmp2);
		  *os2 = *tmp2;
	      }
	      else{
		  *os1 = *tmp1;
		  *os2 = *tmp2;
	      }
	      
	      delete tmp1;
	      delete tmp2;
	      
	      // Evaluation des offsprings
	      
	      try{
		  _eval->executeO(*os1);
		  _eval->executeO(*os2);
	      }
	      catch(std::string Ex1){
		try{
		    _eval->execute(*os1);
		    _eval->execute(*os2);
		}
		catch(std::string Ex2){
		    std::cerr << Ex1 << " then " << Ex2 << std::endl;
		}
	      }
	      
	      _insert->execute(*os1, _population);
	      _insert->execute(*os2, _population);
	      
	      
	      delete os1;
	      delete os2;
	      incAgePop();
	      ++i;      	      
	  }
      }
      catch(std::string Exception){
	  std::cerr << Exception << std::endl;	
      }
    
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
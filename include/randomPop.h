#ifndef RANDOMPOP_H
#define RANDOMPOP_H

#include "initPop.h"

/**
 * Cette classe représente une implémentation de la fonction d'initialisation
 * de la population de notre algorithme génétique. La densité nécessaire cor-
 * respond au nombre de bits allant être fixé à 1 lors de la construction d'un
 * individu. 
 * TODO Voir mise en place design pattern Template
 * @var unsigned nombre de bits d'un individu
 * @var float density
 * @author Ugo Rayer
 * 
 */

class RandomPop : public InitPop {
private: 
  unsigned _nbItems;
  float _density;
  
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur par défaut. Fixe la density par défaut à 5%
   * @param unsigned nombre d'Items
   * @author Ugo Rayer
   */
  RandomPop(unsigned nbI);
  
  
  /**
   * Constructeur recevant une densité en paramètre
   * @param float densité souhaitée
   * @author Ugo Rayer
   */
  RandomPop(unsigned nbI, float density);
  
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  ~RandomPop();

  /* * * * * * 
   * METHODS *
   * * * * * */
/**
 * Rempli un vecteur d'ItemSet initialement null d'un ensemble
 * d'individu.
 * Renvoie une erreur si :
 *  - vecteur non vide
 *  - Problème lors de l'initialisation d'un individu
 * @param std::vector<ItemSet*>* pointeur sur le vecteur à remplir
 * @param unsigned taille de la population à créer
 * @author Ugo Rayer
 */
  void execute(std::vector<ItemSet*>*pop, unsigned taillePop);

/**
 * Rempli un vecteur d'ItemSetC initialement null d'un ensemble
 * d'individu.
 * Renvoie une erreur si :
 *  - vecteur non vide
 *  - Problème lors de l'initialisation d'un individu
 * @param std::vector<ItemSetC*>* pointeur sur le vecteur à remplir
 * @param unsigned taille de la population à créer
 * @author Ugo Rayer
 */
  void execute(std::vector<ItemSetC*>*pop,unsigned taillePop);  
  
};

#endif
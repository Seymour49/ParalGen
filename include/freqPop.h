#ifndef FREQPOP_H
#define FREQPOP_H

#include "initPop.h"
#include "dataSet.h"
#include "dataSetC.h"

/**
 * Cette classe représente une implémentation de la fonction d'initialisation
 * de la population de notre algorithme génétique. La densité nécessaire cor-
 * respond au nombre de bits allant être fixé à 1 lors de la construction d'un
 * individu. 
 * La méthode de construction calcule la fréquence de chaque élément et 
 * catégorise ensuite d'une part les éléments les plus fréquents et d'autre
 * part les suivants de sorte que le nombre total des éléments choisis soit
 * égal à la densité passée en paramètre. Nous recommandons une densité faible
 * ( < 5% ).
 * L'algorithme d'initialisation a également besoin d'avoir accès au jeu de données
 * TODO Voir mise en place design pattern Template
 * @var float density
 * @author Ugo Rayer
 * 
 */

class FreqPop : public InitPop {

private:
  float _density;
  
public: 
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur par défaut. Fixe la density par défaut à 5%
   * @author Ugo Rayer
   */
  FreqPop();
  
  /**
   * Constructeur recevant une densité en paramètre
   * @param float densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop(float density);
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  ~FreqPop();

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
 * @param DataSet* pointeur sur le jeu de données
 * @author 
 */
  void execute(std::vector<ItemSet*>*pop, unsigned taillePop, DataSet* data);

/**
 * Rempli un vecteur d'ItemSetC initialement null d'un ensemble
 * d'individu.
 * Renvoie une erreur si :
 *  - vecteur non vide
 *  - Problème lors de l'initialisation d'un individu
 * @param std::vector<ItemSetC*>* pointeur sur le vecteur à remplir
 * @author Ugo Rayer
 */
  void execute(std::vector<ItemSetC*>*pop,unsigned taillePop, DataSetC* data);  
  
};
#endif
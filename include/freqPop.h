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
 * mais cette classe n'est pas chargée de les détruire.
 * TODO Voir mise en place design pattern Template
 * @var float density
 * @author Ugo Rayer
 * 
 */

class FreqPop : public InitPop {

private:
  float _density;
  DataSet* _data;
  DataSetC* _dataC;
  
public: 
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur par défaut pour un ItemSet. Fixe la density par défaut à 5%
   * Fixe l'autre pointeur à NULL
   * @param DataSet* dataset utilisé
   * @author Ugo Rayer
   */
  FreqPop(DataSet* data);
  
  /**
   * Constructeur pour un DataSet recevant une densité en paramètre
   * Fixe l'autre pointeur à NULL
   * @param DataSet* dataset utilisé
   * @param float densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop(float density, DataSet* data);

  /**
   * Constructeur par défaut pour un DataSetC. Fixe la density par défaut à 5%
   * Fixe l'autre pointeur à NULL
   * @param DataSetC* dataset utilisé
   * @author Ugo Rayer
   */
  FreqPop(DataSetC* data);
  
  /**
   * Constructeur pour un DataSetC recevant une densité en paramètre
   * Fixe l'autre pointeur à NULL
   * @param DataSetC* datasetC utilisé
   * @param float densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop( float density, DataSetC* data);
  
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
  void execute(std::vector<ItemSet*> *pop, unsigned taillePop);

/**
 * Rempli un vecteur d'ItemSetC initialement null d'un ensemble
 * d'individu.
 * Renvoie une erreur si :
 *  - vecteur non vide
 *  - Problème lors de l'initialisation d'un individu
 * @param std::vector<ItemSetC*> pointeur sur le vecteur à remplir
 * @author Ugo Rayer
 */
  void execute(std::vector<ItemSetC*> *pop,unsigned taillePop);  
  
};
#endif
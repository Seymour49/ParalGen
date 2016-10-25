#ifndef FREQEVAL_H
#define FREQEVAL_H

#include "evaluate.h"

/**
 * Cette classe représente une fonction d'évaluation sur la fréquence d'un
 * itemset sur un ensemble d'itemset de même type.
 * TODO Refactorisation lors de la mise en place du design-pattern Template
 * @author Ugo Rayer
 * 
 */

class FreqEval : public Evaluate {
  
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur par défaut. Cette fonction ne nécessite aucun paramètre
   * @author Ugo Rayer
   */
  FreqEval();
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  ~FreqEval();
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
/**
 * Méthode évaluant un individu de type itemSet vis à vis d'un jeu de 
 * données de même type passés en paramètres.
 * @param ItemSet* individu à évaluer
 * @param DataSet* jeu de données
 * @author Ugo Rayer, Johan Defaye
 */
  void execute(ItemSet* ind, DataSet* data);

/**
 * Méthode évaluant un individu de type itemSetC vis à vis d'un jeu de 
 * données de même type passés en paramètres.
 * @param ItemSetC* individu à évaluer
 * @param DataSetC* jeu de données
 * @author Ugo Rayer, Johan Defaye
 */
  void execute(ItemSetC* ind, DataSetC* data);
  

};

#endif
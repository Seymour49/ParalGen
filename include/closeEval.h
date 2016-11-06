#ifndef CLOSEEVAL_H
#define CLOSEEVAL_H

#include "evaluate.h"

/**
 * Cette classe représente la fonction d'évaluation attendue pour notre
 * problème. Elle nécessite un seuil de fréquence choisi par l'utilisateur
 * qui servira lors du calcul de fermeture d'un itemset.
 * Un individu évalué vera sa fréquence calculée puis augmenté de 1 s'il est
 * clos, laissé comme tel sinon.
 * @var float seuil de fréquence
 * @author Ugo Rayer
 * 
 */

class CloseEval : public Evaluate {
  
private:
  float _freq;
  
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
/**
 * Constructeur par défaut nécessitant un seuil de fréquence.
 * @param float frequence
 * @author Ugo Rayer
 */
  CloseEval(float freq);
    
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  ~CloseEval();
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  /**
   * Méthode évaluant un individu de type itemset vis à vis d'un jeu de données
   * de même type passé en passés en paramètres.
   * @param ItemSet* individu à évaluer
   * @param DataSet* jeu de données
   * @author Ugo Rayer
   */
  void execute(ItemSet* ind, DataSet* data);
  
  /**
   * Méthode évaluant un individu de type itemsetC vis à vis d'un jeu de
   * données de même type passé en passés en paramètres.
   * @param ItemSetC* individu à évaluer
   * @param DataSetC* jeu de données
   * @author Ugo Rayer
   */
  void execute(ItemSetC* ind, DataSetC* data);
    

};

#endif
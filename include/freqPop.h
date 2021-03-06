#ifndef FREQPOP_H
#define FREQPOP_H

#include "initPop.h"
#include "dataSet.h"
#include "dataSetO.h"

#include <algorithm>

/**
 * Revoir la description
 * @author Ugo Rayer, Johan Defaye
 * 
 */

class FreqPop : public InitPop<char> {

private:
  DataSet<char> * _data;
  DataSetO<char> * _dataO;
  float _seuilF;

  
public: 
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur initialisant le jeu de donné et la densité à 5 % si non spécifié
   * @param data : dataset utilisé
   * @param density : densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop(DataSet<char> * const data, float sF = 0.05);

  
  /**
   * Constructeur initialisant le jeu de donné optimisé et la densité à 5 % si non spécifié
   * @param data : datasetO utilisé
   * @param density : densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop(DataSetO< char >*const dataO, float sF = 0.05);
  
  
  /**
   * Constructeur initialisant le jeu de donné non optimisé et l'optimisé, et la densité à 5 % si non spécifié
   * @param data : dataset non optimisé
   * @param dataO : data optimisé
   * @param density : densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop(DataSet<char> * const data, DataSetO<char> * const dataO, float sF = 0.05);
  
  
  /**
   * Constructeur par recopie
   * @author Johan Defaye
   */
  FreqPop(const FreqPop & f);
  

  
  
  /* * * * * * * * * * *
   * GETTER ET SETTER  *
   * * * * * * * * * * */
  
  float getseuilF() const {return _seuilF;}
  
  void setseuilF(float sF) {_seuilF = sF;}
    
  void setData(DataSet<char> * const data) { _data = data; }
    
  void setDataO(DataSetO<char> * const dataO) { _dataO = dataO; }
  

  /* * * * * * 
   * METHODS *
   * * * * * */
/**
 * Rempli un vecteur d'individu initialement null avec des individu fréquent dans le jeu de donnée
 * Retourne une exception si :
 *  - population vide
 *  - jeu de donné non initalisé
 *  - jeu de donné vide
 * @param pop :  Référence sur le vecteur à remplir
 * @author Ugo Rayer
 */
  void execute(std::vector<Individual<char> *> & pop);

/**
 * Rempli un vecteur d'individu initialement null avec des individu fréquent dans le jeu de donnée optimisé
 * Retourne une exception si :
 *  - population vide
 *  - jeu de donné optimisé non initalisé
 *  - jeu de donné optimisé vide
 * @param pop : Référence sur le vecteur à remplir
 * @author Ugo Rayer
 */
  void executeO(std::vector<Individual<char> *> & pop);
  
  
};
#endif
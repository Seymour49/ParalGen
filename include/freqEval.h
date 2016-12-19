#ifndef FREQEVAL_H
#define FREQEVAL_H

#include "evaluate.h"
#include "dataSet.h"
#include "dataSetO.h"

/**
 * Cette classe représente une fonction d'évaluation sur la fréquence d'un
 * itemset sur un ensemble d'itemset de même type.
 * TODO Refactorisation lors de la mise en place du design-pattern Template
 * @author Ugo Rayer
 * 
 */

class FreqEval : public Evaluate<char> {
  
private:
  DataSet<char> * _data1;
  DataSetO<char> * _data2;
  
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur par défaut. Cette fonction ne nécessite aucun paramètre
   * @author Ugo Rayer
   */
  FreqEval();
  
  /**
   * Constructeur prenant un dataSet en paramètre
   * @param data : Un jeu de donnée
   * @author Johan Defaye
   */
  FreqEval(DataSet<char> * const data);
  
  /**
   * Constructeur prenant un dataSetO en paramètre
   * @param data : Un jeu de donnée
   * @author Johan Defaye
   */
  FreqEval(DataSetO<char> * const data);
  
  /**
   * Constructeur prenant un dataSet et un dataSetO en paramètre
   * @param data1 : Un jeu de donnée
   * @param data2 : Un deuxième jeu de donnée
   * @author Johan Defaye
   */
  FreqEval(DataSet<char> * const data1, DataSetO<char> * const data2);
  
  /**
   * Constructeur par recopie
   * @author Johan Defaye
   */
  FreqEval(const FreqEval & f);
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  /* * * * * * * * * * *
   * GETTER ET SETTER  *
   * * * * * * * * * * */
  
  DataSet<char> * getData() const {return _data1;}
  
  void setData(const DataSet<char> * data) { *_data1 = *data; }
  
  DataSetO<char> * getDataO() const {return _data2;}
  
  void setDataO(const DataSetO<char> * dataO) { *_data2 = *dataO; }
  
/**
 * Méthode évaluant la fréquence d'un individu par rapport au dataSet
 * Modifie l'attribut score d'un individu
 * @param ind: individu à évaluer
 * @author Ugo Rayer, Johan Defaye
 */
  void execute(Individual<char> & ind);
  
/**
 * Méthode évaluant la fréquence d'un individu par rapport au dataSetO
 * Modifie l'attribut score d'un individu
 * @param ind: individu à évaluer
 * @author Ugo Rayer, Johan Defaye
 */
  void executeO(Individual<char> & ind);
  

};

#endif
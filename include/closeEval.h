#ifndef CLOSEEVAL_H
#define CLOSEEVAL_H

#include "evaluate.h"
#include "dataSet.h"
#include "dataSetO.h"

#include <algorithm>
#include <vector>

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

class CloseEval : public Evaluate<char> {
  
private:
  float _freq;
  DataSet<char> * _data1;
  DataSetO<char> * _data2;
  std::vector<unsigned int> _itemFreq;
  std::vector<unsigned int> _itemFreqO;
  
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
  
  
  /**
   * Constructeur prenant un dataSet en paramètre
   * @param data : Un jeu de donnée
   * @author Johan Defaye
   */
  CloseEval(float freq, DataSet<char> * const data);
  
  /**
   * Constructeur prenant un dataSetO en paramètre
   * @param data : Un jeu de donnée
   * @author Johan Defaye
   */
  CloseEval(float freq, DataSetO<char> * const data);
  
  /**
   * Constructeur prenant un dataSet et un dataSetO en paramètre
   * @param data1 : Un jeu de donnée
   * @param data2 : Un deuxième jeu de donnée
   * @author Johan Defaye
   */
  CloseEval(float freq, DataSet<char> * const data1, DataSetO<char> * const data2);
  
  /**
   * Constructeur par recopie
   * @author Johan Defaye
   */
  CloseEval(const CloseEval & c);
  
  
  /* * * * * * * * * * *
   * GETTER ET SETTER  *
   * * * * * * * * * * */
  
  DataSet<char> * getData() const {return _data1;}
  
  void setData(const DataSet<char> * data) { *_data1 = *data; _itemFreq.clear(); }
  
  DataSetO<char> * getDataO() const {return _data2;}
  
  void setDataO(const DataSetO<char> * dataO) { *_data2 = *dataO; _itemFreqO.clear(); }
  
  float getFrequence() const { return _freq; }
  
  void setFrequence(float freq) {_freq = freq;}
  
  std::vector<unsigned int> getItemFreq() const {return _itemFreq;}
  
  void setItemFreq(const std::vector<unsigned int> & itemFreq) {_itemFreq = itemFreq;}
  
  std::vector<unsigned int> getItemFreqO() const {return _itemFreqO;}
  
  void setItemFreqO(const std::vector<unsigned int> & itemFreqO) {_itemFreqO = itemFreqO;}
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  /**
   * Méthode évaluant un individu de type itemset vis à vis du jeu de donnée non optimisé
   * @param ind : l'individu à évaluer
   * @author Ugo Rayer
   */
  void execute(Individual<char> & ind);
  
  
  /**
   * Méthode évaluant un individu de type itemset vis à vis du jeu de donnée optimisé
   * @param ind : l'individu à évaluer
   * @author Ugo Rayer
   */
  void executeO(Individual<char> & ind);

    

};

#endif

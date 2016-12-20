#ifndef IRANDOMPOP_H
#define IRANDOMPOP_H

#include "initPop.h"
#include "dataSet.h"
#include "dataSetO.h"

/**
 * Cette classe représente l'initialisation d'une population par augmentation.
 * Ce principe revient à effectuer T tirages uniformément aléatoires parmi les
 * différentes transactions du jeu de données passé en paramètre
 * @author Ugo Rayer 
 */

class IRandomPop : public InitPop<char> {

private:
    DataSet<char>* _data;
    DataSetO<char>* _dataO;
    
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur initialisant le jeu de donné 
   * @param data : dataset utilisé
   * @author Ugo Rayer
   */
  IRandomPop(DataSet<char>* const data);
  
  /**
   * Constructeur initialisant le jeu de donné optimisé
   * @param data : datasetO utilisé
   * @author Ugo Rayer
   */
  IRandomPop(DataSetO<char>* const data);
  
   /**
   * Constructeur initialisant le jeu de donné non optimisé et l'optimisé, et la densité à 5 % si non spécifié
   * @param data : dataset non optimisé
   * @param dataO : data optimisé
   * @author Ugo Rayer
   */
  IRandomPop(DataSet<char> * const data, DataSetO<char> * const dataO);
  
  /**
   * Constructeur par recopie
   * @author Ugo Rayer
   */
  IRandomPop(const IRandomPop& irp);
  
   /* * * * * * * * * * *
   * GETTER ET SETTER  *
   * * * * * * * * * * */
  void setData(DataSet<char> * const data) { _data = data; }
    
  void setDataO(DataSetO<char> * const dataO) { _dataO = dataO; }
  
  
  /* * * * * * 
   * METHODS *
   * * * * * */
/**
 * Rempli un vecteur d'individu initialement null avec des individus tirés
 * aléatoirement parmi les transactions du jeu de données
 * Retourne une exception si :
 *  - population vide
 *  - jeu de donné non initalisé
 *  - jeu de donné vide
 * @param pop :  Référence sur le vecteur à remplir
 * @author Ugo Rayer
 */
  void execute(std::vector<Individual<char> *> & pop);

/**
 * Rempli un vecteur d'individu initialement null avec des individus tirés
 * aléatoirement parmi les transactions du jeu de données
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
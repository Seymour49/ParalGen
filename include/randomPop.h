#ifndef RANDOMPOP_H
#define RANDOMPOP_H

#include "initPop.h"

/**
 * Cette classe représente une implémentation de la fonction d'initialisation
 * de la population de notre algorithme génétique. La densité nécessaire cor-
 * respond au nombre de bits allant être fixé à 1 lors de la construction d'un
 * individu. 
 * @var float density
 * @author Ugo Rayer
 * TODO: Ajouter en paramètre une liste des valeurs que peuvent prendre les items d'un individu ('0' et '1' dans notre cas)
 */

class RandomPop : public InitPop<char> {
  
private: 
  unsigned int _nbItem;
  float _density;
  
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  
  /**
   * Constructeur recevant un nombre d'item et une densité en paramètre
   * @param nbItem : nombre d'item d'un individu de la population
   * @param float densité souhaitée
   * @author Ugo Rayer
   */
  RandomPop(unsigned int nbItem, float density = 0.05);
  
  
  /**
   * Constructeur par recopie
   * @param r : une autre fonction d'initialisation de la population
   * @author Ugo Rayer
   */
  RandomPop(const RandomPop & r);
  
  
  /* * * * * * * * * * *
   * GETTER ET SETTER  *
   * * * * * * * * * * */
  
  float getDensity() const { return _density;}
  
  void setDensity(float density) { _density = density;}
  
  float getNbItem() const { return _nbItem;}
  
  void setNbItem(float nbItem) { _nbItem = nbItem;}
  

  /* * * * * * 
   * METHODS *
   * * * * * */
  
  
   /**
    * Rempli un vecteur d'individu initialement null avec des individus initialisés aléatoirement
    * Renvoie une erreur si :
    *  - vecteur non vide
    *  - Problème lors de l'initialisation d'un individu
    * @param pop : référence sur le vecteur à remplir
    * @author Ugo Rayer
    */
  void execute(std::vector<Individual<char>*> & pop);
  
  
  void executeO(std::vector<Individual<char>*> &pop);
  
};

#endif
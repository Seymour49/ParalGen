#ifndef ITEMSET_H
#define ITEMSET_H

#include <vector>
#include <iostream>
#include "../include/individual.h"

/*
 * Classe représentent un ensemble d'items via un bitset codé en vecteur de char. 
 */



/**
  * Représente une transaction en une liste de booléen (1 ou 0) signifiant 
  * si un item est présent dans la transaction ou non
  * @author Johan Defaye
  */
class ItemSet : public Individual {

private:
  std::vector<char> _bitset;
  
public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur par défaut d'un ItemSet
  * Initialise un ItemSet comme un vecteur de char vide
  * @author Johan Defaye
  */
  ItemSet();
  
  
/** 
  * Constructeur prenant un vecteur de char en paramètre
  * Initilise un ItemSet avec un vecteur de char donné en paramètre
  * @param v : Vecteur de char
  * @author Johan Defaye
  */
  ItemSet(const std::vector<char> & v);
  
  
/** 
  * Constructeur par copie
  * Initilise un ItemSet avec un autre ItemSet donné en paramètre
  * @param i : Un ItemSet
  * @author Johan Defaye
  */  
  ItemSet( const ItemSet & i);
  
  /* * * * * * 
   * Getters *
   * * * * * */
  int getSize() const { return (int)_bitset.size(); }
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
/** 
  * Construit et retourne la liste des items présent dans l'ItemSet
  * @return Un vecteur d'int représentant les items présents dans la transaction
  * @author Johan Defaye
  */
  std::vector<int> getListItem() const;
  
  /* * * * * * * * * * * * *
   *    HERITED METHODS    *
   * * * * * * * * * * * * */ 
  
 /**
   * Méthode faisant muter un individu. Modifie de manière aléatoire
   * une seule information de l'individu. 
   */
  void Mutate();
  
  /**
   * Croisement monopoint entre deux individus. Le parent 1 est l'objet
   * courant et le parent 2 est passé en paramètre. La position du pivot
   * est également passsé en paramètre.
   * @param ind Parent 2
   * @param pos Indice du pivot
   * @return nouvel individu
   */
  Individual& CrossClassic(const Individual& ind,std::size_t pos);
  
 
  /* * * * * * * * * * * * *
   * SURCHARGE D'OPÉRATEUR *
   * * * * * * * * * * * * */
  
  
  
/** 
  * Affiche l'ItemSet dans le flux passé en paramètre
  * @param flux : Un flux pour l'affichage
  * @author Johan Defaye
  */
  void print(std::ostream & flux) const;
  
  
};


/** 
* Surcharge de l'opérateur d'affichage
* @param flux : Un flux pour l'affichage
* @param i : ItemSet à afficher
* @author Johan Defaye
*/
std::ostream& operator<<(std::ostream &flux, const ItemSet & i);


#endif
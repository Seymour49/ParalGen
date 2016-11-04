#ifndef ITEMSETC_H
#define ITEMSETC_H

#include <vector>
#include <iostream>
#include <ctime>
#include "../include/individual.h"

/*
 * Classe représentent un ensemble d'items via un bitset codé en vecteur de char. 
 */



/**
  * Représente une transaction en une liste de booléen (1 ou 0) signifiant 
  * si un item est présent dans la transaction ou non
  * @author Johan Defaye
  */
class ItemSetC : public Individual {

private:
  char* _bitset;
  unsigned int _nbItems;
  
public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur par défaut d'un ItemSet
  * Initialise un ItemSet comme un vecteur de char vide
  * @author Johan Defaye
  */
  ItemSetC();
  
  
/** 
  * Constructeur prenant un vecteur de char en paramètre
  * Initilise un ItemSet avec un vecteur de char donné en paramètre
  * @param v : Vecteur de char
  * @author Johan Defaye
  */
  ItemSetC(char* v, int nbI);
  
  
/** 
  * Constructeur par copie
  * Initilise un ItemSet avec un autre ItemSet donné en paramètre
  * @param i : Un ItemSet
  * @author Johan Defaye
  */  
  ItemSetC( const ItemSetC & it);
  
  /* * * * * * * * * 
   *  DESTRUCTOR   *
   * * * * * * * * */
  ~ItemSetC();
  
  /* * * * * * 
   * GETTERS *
   * * * * * */
  unsigned int getSize() const { return _nbItems; }
  
  char* getBitset() const { return _bitset; }
  
  char getBitsetAt(unsigned int pos) const { return _bitset[pos]; }
  
  /* * * * * * 
   * Setters *
   * * * * * */
  

  void setBitset(char* BS, unsigned size);
  
  void flipBit(unsigned ind);
  
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
std::ostream& operator<<(std::ostream &flux, const ItemSetC & i);


#endif
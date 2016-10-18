#ifndef ITEMSET_H
#define ITEMSET_H

#include <vector>
#include <iostream>

/*
 * Classe représentent un ensemble d'items via un bitset codé en vecteur de char. 
 */



/**
  * Représente une transaction en une liste de booléen (1 ou 0) signifiant 
  * si un item est présent dans la transaction ou non
  * @author Johan Defaye
  */
class itemSet : public std::vector<char> {


public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur par défaut d'un itemSet
  * Initialise un itemSet comme un vecteur de char vide
  * @author Johan Defaye
  */
  itemSet();
  
  
/** 
  * Constructeur prenant un vecteur de char en paramètre
  * Initilise un itemSet avec un vecteur de char donné en paramètre
  * @param v : Vecteur de char
  * @author Johan Defaye
  */
  itemSet(const std::vector<char> & v);
  
  
/** 
  * Constructeur par copie
  * Initilise un itemSet avec un autre itemSet donné en paramètre
  * @param i : Un itemSet
  * @author Johan Defaye
  */  
  itemSet( const itemSet & i);
  
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
/** 
  * Construit et retourne la liste des items présent dans l'itemSet
  * @return Un vecteur d'int représentant les items présents dans la transaction
  * @author Johan Defaye
  */
  std::vector<int> getListItem() const;
    
  
  /* * * * * * * * * * * * *
   * SURCHARGE D'OPÉRATEUR *
   * * * * * * * * * * * * */
  
  
  
/** 
  * Affiche l'itemSet dans le flux passé en paramètre
  * @param flux : Un flux pour l'affichage
  * @author Johan Defaye
  */
  void print(std::ostream & flux) const;
  
  
};


/** 
* Surcharge de l'opérateur d'affichage
* @param flux : Un flux pour l'affichage
* @param i : itemSet à afficher
* @author Johan Defaye
*/
std::ostream& operator<<(std::ostream &flux, const itemSet & i);


#endif
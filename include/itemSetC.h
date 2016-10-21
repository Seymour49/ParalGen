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
  
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
/** 
  * Construit et retourne la liste des items présent dans l'ItemSet
  * @return Un vecteur d'int représentant les items présents dans la transaction
  * @author Johan Defaye
  */
  std::vector<int> getListItem() const;
  
  
/**
 * Croisement multipoint entre deux individus. La parent 1 est l'objet 
 * courant et le parent 2 est passé en paramètre. Les positions des pivots
 * sont passés en paramètre en tant que vecteur d'entier
 * L'individu fils est créé en alternant les parties des parents suivant les pivots
 * @param it : Un ItemSetC faisant office de parent 
 * @param pivots : vecteur d'entiers trié dans l'ordre croissant
 * @return Un ItemSetC résultant du croisement des deux ItemSetC
 * @author Johan Defaye
 * TODO Au moment de la création du vecteur de pivot, vérifier qu'il a bien été initialisé dans l'ordre croissant
 */
  ItemSetC CrossMultiPoint(const ItemSetC & it, const std::vector<unsigned int> & pivots) const;
  
  
/**
 * Croisement uniforme entre deux individus. La parent 1 est l'objet 
 * courant et le parent 2 est passé en paramètre. À chaque position
 * de l'ItemSetC, on choisis aléatoirement l'item du parent 1 ou 2
 * @param it : un ItemSetC faisant office de parent
 * @return Un ItemSetC résultant du croisement des deux ItemSetC
 * @author Johan defaye
 */
ItemSetC CrossUniform(const ItemSetC & it) const;
  
  /* * * * * * * * * * * * *
   *    HERITED METHODS    *
   * * * * * * * * * * * * */ 
  
 /**
   * Méthode faisant muter un individu. Modifie de manière aléatoire
   * une seule information de l'individu. 
   * @author Ugo Rayer
   */
  void Mutate();
  
  /**
   * Croisement monopoint entre deux individus. Le parent 1 est l'objet
   * courant et le parent 2 est passé en paramètre. La position du pivot
   * est également passsé en paramètre.
   * @param ind Parent 2
   * @param pos Indice du pivot
   * @return nouvel individu
   * @author Johan Defaye
   */
  Individual* CrossClassic(const Individual * ind, std::size_t pos) const;
  
 
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
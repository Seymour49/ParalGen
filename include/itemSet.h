#ifndef ITEMSET_H
#define ITEMSET_H

#include "individual.h"


/**
  * Représente une transaction en une liste de booléen (1 ou 0) signifiant 
  * si un item est présent dans la transaction ou non
  * @author Johan Defaye
  */
template <typename T>
class ItemSet : public Individual<T> {

private:
  std::vector<T> _bitset;
  
public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur par défaut d'un ItemSet
  * Initialise un ItemSet comme un vecteur vide de T
  * @author Johan Defaye
  */
  ItemSet(): Individual<T>()
  {}
  
  
/** 
  * Constructeur prenant un vecteur de T en paramètre
  * Initilise un ItemSet avec un vecteur de T donné en paramètre
  * @param v : Vecteur de T
  * @author Johan Defaye
  */
  ItemSet(const std::vector<T> & v): Individual<T>(), _bitset(v)
  {}
  
  
 /** 
  * Constructeur prenant un tableau de T en paramètre et sa taille
  * Initilise un ItemSet avec un tableau de T donné en paramètre
  * @param t : tableau de T
  * @param size : taille du tableau
  * @author Johan Defaye
  */
  ItemSet(T * t, unsigned int size): Individual<T>()
  {
    _bitset.resize(size);
    for (unsigned int i = 0; i < size; ++i) _bitset[i] = t[i];
  }
  
  
/** 
  * Constructeur par copie
  * Initilise un ItemSet avec un autre ItemSet donné en paramètre
  * @param i : Un ItemSet
  * @author Johan Defaye
  */  
  ItemSet(const ItemSet<T> & i): Individual<T>(i), _bitset(i.get())
  {}

  
  /* * * * * * * * * * * * * * *
   * ACCESSEURS  ET MUTATEURS  *
   * * * * * * * * * * * * * * */
  
    
  std::vector<T> get() const { return _bitset; }
  
  void set(const std::vector<T> & v) 
  {  
    resize(v.size());
    for (unsigned int i = 0; i < v.size(); ++i) {
      _bitset[i] = v[i];
    }
  }
  
  void set(T* BS, unsigned size)
  {
    if (BS != NULL){
      resize(size);
      for (unsigned int i = 0; i < size; ++i){
	_bitset[i] = BS[i]; 
      }
    }
  }
  
  unsigned int size() const { return _bitset.size(); }
  
  
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  
  /**
   * Réserve l'emplacement mémoire indiqué
   * @param size : Nouvelle taille de l'emplacement mémoire
   * @author Johan Defaye
   */
  virtual void resize(unsigned int size) 
  {
    _bitset.clear();
    _bitset.resize(size);
  }
  
  
  
  /* * * * * * * * * * * * *
   * SURCHARGE D'OPÉRATEUR *
   * * * * * * * * * * * * */
  
  
 /** 
   * Affiche l'ItemSet dans le flux passé en paramètre
   * @param flux : Un flux pour l'affichage
   * @author Johan Defaye
   */
  void print(std::ostream & flux) const
  {
    Individual<T>::print(flux);
    flux << "Bitset : ";
    
    if (_bitset.size() > 0) flux << _bitset.at(0);
    for (unsigned int i = 1; i < _bitset.size(); ++i) {
      flux << "" << _bitset.at(i);
    }
    
    flux << std::endl; 
  }
  
  
  /**
   * Accède au ième élément d'un itemSet
   * @param indice : L'indice de l'élément à accéder
   * @return La valeur du ième élément
   * @author Johan Defaye
   */
  T& operator[](unsigned int indice) {return _bitset[indice];}
  
  const T& operator[](unsigned int indice) const {return _bitset[indice];}
  
  
  /**
   * Opérateur d'affectation
   * @param i : un autre itemSet
   * @author Johan Defaye
   */
  virtual ItemSet<T> & operator=(const ItemSet<T> & i)
  {
    this->setAge(i.getAge());
    this->setScore(i.getScore());
    
    if (_bitset.size() != i.size()) resize(i.size());
    for (unsigned int j = 0; j < size(); ++j) {
      _bitset[j] = i[j];
    }
    
    return *this;
  }

  
};


/** 
 * Surcharge de l'opérateur d'affichage
 * @param flux : Un flux pour l'affichage
 * @param i : ItemSet à afficher
 * @author Johan Defaye
 */
template <typename T>
std::ostream& operator<<(std::ostream &flux, const ItemSet<T> & i)
{
  i.print(flux);
  return flux;
}


#endif
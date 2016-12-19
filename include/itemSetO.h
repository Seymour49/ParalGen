#ifndef ITEMSETC_H
#define ITEMSETC_H

#include "individual.h"


/**
  * Représente une transaction en une liste de booléen (1 ou 0) signifiant 
  * si un item est présent dans la transaction ou non
  * @author Johan Defaye
  */
template <typename T>
class ItemSetO : public Individual<T> {

private:
  T* _bitset;
  unsigned int _nbItems;
  
public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur par défaut d'un ItemSetO
  * Initialise un ItemSetO comme un vecteur de T vide
  * @author Johan Defaye
  */
  ItemSetO(): Individual<T>(), _nbItems(0)
  {
    _bitset = NULL;
  }
  
  
/** 
  * Constructeur prenant un tableau de T en paramètre ainsi que sa taille
  * Initilise un ItemSetO avec un vecteur de T donné en paramètre
  * @param t : Tableau de t
  * @param size : taille du tableau
  * @author Johan Defaye
  */
  ItemSetO(T* t, unsigned int size):Individual<T>(),_nbItems(size)
  {
    _bitset = new T[_nbItems];
    for (unsigned int i = 0; i < _nbItems; ++i){
      _bitset[i] = t[i];
    }
  }
  
  
 /** 
  * Constructeur prenant un vecteur de T en paramètre
  * Initilise un ItemSetO avec un vecteur de T donné en paramètre
  * @param v : Vecteur de T
  * @author Johan Defaye
  */
  ItemSetO(const std::vector<T> & v):Individual<T>(),_nbItems(v.size())
  {
    _bitset = new T[_nbItems];
    for (unsigned int i = 0; i < _nbItems; ++i){
      _bitset[i] = v[i];
    }
  }
  
  
/** 
  * Constructeur par copie
  * Initilise un ItemSet avec un autre ItemSetO donné en paramètre
  * @param i : Un ItemSetO
  * @author Johan Defaye
  */  
  ItemSetO(const ItemSetO<T> & it): Individual<T>(it), _nbItems(it.size())
  {
    _bitset = new T[_nbItems];
    for (unsigned int i = 0; i < _nbItems; ++i){
      _bitset[i] = it[i];
    }
  }
  
  /* * * * * * * * * 
   *  DESTRUCTOR   *
   * * * * * * * * */
  ~ItemSetO()
  {
    delete[] _bitset;
  }
  
  /* * * * * * 
   * GETTERS *
   * * * * * */
  unsigned int size() const { return _nbItems; }
  
  std::vector<T> get() const
  {
    std::vector<T> v;
    v.resize(_nbItems);
    for (unsigned int i = 0; i < _nbItems; ++i) v[i] = _bitset[i];
    return v;
  }
    
  /* * * * * * 
   * Setters *
   * * * * * */
  

  void set(T* BS, unsigned size)
  {
    if (BS != NULL){
      _nbItems = size;
      delete [] _bitset;
      _bitset = new T[size];
      for (unsigned int i = 0; i < size; ++i){
	_bitset[i] = BS[i]; 
      }
    }
  }
  
  void set(const std::vector<T> & v) 
  {  
    resize(v.size());
    for (unsigned int i = 0; i < v.size(); ++i) {
      _bitset[i] = v[i];
    }
  }
  
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  
  /**
   * Réserve l'emplacement mémoire nécessaire
   * @param size : Nouvelle taille de l'emplacement mémoire
   * @author Johan Defaye
   */
  virtual void resize(unsigned int size)
  {
    delete [] _bitset;
    _bitset = new T[size];
    _nbItems = size;
  }
 
 
 
  /* * * * * * * * * * * * *
   * SURCHARGE D'OPÉRATEUR *
   * * * * * * * * * * * * */
  
  
/** 
  * Affiche l'ItemSetO dans le flux passé en paramètre
  * @param flux : Un flux pour l'affichage
  * @author Johan Defaye
  */
  void print(std::ostream & flux) const
  {
    Individual<T>::print(flux);
    flux << "Bitset : ";
    
    if (_nbItems > 0) flux << _bitset[0];
    for (unsigned int i = 1; i < _nbItems; ++i) {
      flux << "" << _bitset[i];
    }
    
    flux << std::endl;
  }
  
  /**
   * Accède au ième élément d'un itemSetO
   * @param indice : L'indice de l'élément à accéder
   * @return La valeur du ième élément
   * @author Johan Defaye
   */
  T& operator[](unsigned int indice) {return _bitset[indice];}
  
  const T& operator[](unsigned int indice) const {return _bitset[indice];}
  
  
  /**
   * Opérateur d'affectation
   * @param i : un autre itemSetO
   * @author Johan Defaye
   */
  virtual ItemSetO<T> & operator=(const ItemSetO<T> & i)
  {
    this->setAge(i.getAge());
    this->setScore(i.getScore());
    
    if (_nbItems != i.size()) resize(i.size());
    for (unsigned int j = 0; j < _nbItems; ++j) {
      _bitset[j] = i[j];
    }
    
    return *this;
  }
  
};


/** 
* Surcharge de l'opérateur d'affichage
* @param flux : Un flux pour l'affichage
* @param i : ItemSetO à afficher
* @author Johan Defaye
*/
template <typename T>
std::ostream& operator<<(std::ostream &flux, const ItemSetO<T> & i)
{
  i.print(flux);
  return flux;
}


#endif
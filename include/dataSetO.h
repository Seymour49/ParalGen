#ifndef DATASETO_H
#define DATASETO_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * Class abstraite représentant un tableau de donnée à deux dimension
 * Le tableau est stocké en tant que vecteur de vecteur
 * @author Johan Defaye
 */
template <typename T>
class DataSetO {
  
  
protected:
  
  unsigned int _nbLine; // Nombre de ligne du tableau
  unsigned int _nbCol;  // Nombre de colonne du tableau
  T ** _data;
  
public:
  
  DataSetO(unsigned int nbLine, unsigned int nbCol):_nbLine(nbLine), _nbCol(nbCol)
  {}
  
  DataSetO(const DataSetO<T> & d):_nbLine(d.getNbLine()), _nbCol(d.getNbCol())
  {
    _data = new T*[_nbLine];
    for (unsigned int i = 0; i < _nbLine; ++i) {
      _data[i] = new T[_nbCol];
      for (unsigned int j = 0; j < _nbCol; ++j) {
	_data[i][j] = d.getDataAt(i,j);
      }
    }
  }
  
  /* * * * * * *
   * ACCESSORS *
   * * * * * * */
  
  /**
   * Retourne le nombre de ligne du tableau 2D
   * @return : Nombre de ligne du tableau
   * @author Johan Defaye
   */
  unsigned int getNbLine() const { return _nbLine;}
  
  /**
   * Retourne le nombre de colonne du tableau 2D
   * @return : Nombre de colonne du tableau
   * @author Johan Defaye
   */
  unsigned int getNbCol() const { return _nbCol; }
  
  
  /**
   * Retourne l'élément d'indice [row,col] sans possibilité de le modifier
   * @param row : indice de ligne
   * @param col : indice de colonne
   * @author Ugo Rayer
   */
  T getDataAt(unsigned row, unsigned col) const 
  {
    if ((row < 0) || (row >= _nbLine) || (col < 0) || (col >= _nbCol)) throw std::string("Erreur, indice non conforme"); 
    else return _data[row][col];
  }

  
  /* * * * * *
   * METHODS *
   * * * * * */
 
  
  /**
   * Lit un fichier de donnée dont le nom est passé en paramètre et remplie les données du tableau avec
   * @param fileName : Chemin d'accès du fichier de donnée
   * @author Ugo Rayer
   */
  virtual void loadFile(const std::string & fileName) =0;
  
  
  /* * * * * * * * * * * * *
   * OPERATOR OVERLOADING  *
   * * * * * * * * * * * * */
  
  
 /**
   * Affiche le tableau de donnée dans le flux passé en paramètre
   * @param flux : Flux pour l'affichage
   * @author Johan Defaye
   */
  void print(std::ostream & flux) const 
  {
    for (unsigned int i = 0; i < _nbLine; ++i) {
      for (unsigned int j = 0; j < _nbCol; ++j) {
	flux << _data[i][j] << " ";
      }
      flux << std::endl;
    }
  }
  
/**
  * Opérateur d'accès qui permet d'accéder à la ième ligne du tableau
  * @param indice : Indice de la ligne à accéder
  * @return Un tableau à une dimension repésentant une ligne du tableau à deux dimensions 
  * @author Johan Defaye
  */
   T* operator[] (unsigned int indice)
   {
     return _data[indice];
   }
    
/**
  * Opérateur d'accès qui permet d'accéder à la ième ligne du tableau sans possibilité de la modifier
  * @param indice : Indice de la ligne à accéder
  * @return Un tableau à une dimension repésentant une ligne du tableau à deux dimensions 
  * @author Johan Defaye
  */
  const T* operator[] (unsigned int indice) const
  {
    return _data[indice];
  }
  
  
  virtual DataSetO<T>& operator=(const DataSetO<T> & data)
  {
    _nbCol = data.getNbCol();
    _nbLine = data.getNbLine();
    _data = new T*[_nbLine];
    for (unsigned int i = 0; i < _nbLine; ++i) {
      _data[i] = new T[_nbCol];
      for (unsigned int j = 0; j < _nbCol; ++j) {
	_data[i][j] = data[i][j];
      }
    }
    return *this;
  }
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  
  virtual ~DataSetO() 
  {
    for (unsigned int i = 0; i < _nbLine; ++i) {
      delete [] (_data[i]);
    }
    if (_nbLine != 0) delete [] (_data);
  }
  
};



  /* * * * * * *
   * FUNCTIONS *
   * * * * * * */

/**
 * Surcharge de l'opérateur d'affichage
 * @param flux : un flux pour l'affichage
 * @param data :  DataSet à afficher
 * @author Johan Defaye
 */
template <typename T>
std::ostream & operator<<(std::ostream & flux, const DataSetO< T > & data)
{
  data.print(flux);
  return flux;
}


#endif
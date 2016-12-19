#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * Class abstraite représentant un tableau de donnée à deux dimension
 * Le tableau est stocké en tant que vecteur de vecteur
 * Chaque ligne représente une transaction et chaque colonne un item
 * @author Johan Defaye
 */
template <typename T>
class DataSet : public std::vector< std::vector< T > > {
  
  
protected:
  
  unsigned int _nbLine; // Nombre de ligne du tableau
  unsigned int _nbCol;  // Nombre de colonne du tableau
  
  
public:
  
  DataSet(unsigned int nbLine, unsigned int nbCol):_nbLine(nbLine), _nbCol(nbCol)
  {}
  
  DataSet(const DataSet<T> & d):std::vector<std::vector<T> >(d), _nbLine(d.getNbLine()), _nbCol(d.getNbCol())
  {}
  
  
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
  const T& getDataAt(unsigned row, unsigned col) const 
  {
    if ((row < 0) || (row >= _nbLine) || (col < 0) || (col >= _nbCol)) throw std::string("Erreur, indice non conforme"); 
    else return this->at(row).at(col);
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
	flux << this->at(i).at(j) << " ";
      }
      flux << std::endl;
    }
  }
  
  
  virtual DataSet<T>& operator=(const DataSet<T> & data)
  {
    _nbCol = data.getNbCol();
    _nbLine = data.getNbLine();
    this->resize(_nbLine);
    for (unsigned int i = 0; i < _nbLine; ++i) {
      this->at(i).resize(_nbCol);
      for (unsigned int j = 0; j < _nbCol; ++j) {
	this->at(i).at(j) = data.getDataAt(i,j);
      }
    }
    return *this;
  }
  
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  
  virtual ~DataSet()
  {}
  
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
std::ostream & operator<<(std::ostream & flux, const DataSet< T > & data)
{
  data.print(flux);
  return flux;
}


#endif
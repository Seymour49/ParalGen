#ifndef DATASETC_H
#define DATASETC_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "itemSetC.h"

/**
 * Représente un ensemble de transaction comme un tableau 2D de char 
 * Chaque ligne représente une transaction et chaque colonne un item
 * La case de coordonnée [i,j] aura pour valeur 1 si l'item j figure
 * dans la transaction i et 0 s'il n'y figure pas
 * @author Johan Defaye
 */
class DataSetC {
  
  
private:
  
  unsigned int _nbLine; // Nombre de ligne du tableau
  unsigned int _nbCol;  // Nombre de colonne du tableau
  char ** _data;
  
  
public:
  
  /* * * * * * * * *
   * CONSTRUCTORS  *
   * * * * * * * * */
  
  
  /**
    * Constructeur par défaut d'un DataSetC
    * @author Johan Defaye
    */
  DataSetC();

  
  /**
    * Constructeur prenant un nombre de transaction et un nombre d'item par transaction en paramètre
    * Construit un tableau de transaction avec le nombre de transaction passé en paramètre
    * @param nbTransaction : Nombre de ligne du tableau
    * @param nbItem : Nombre d'item par transaction
    * @author Johan Defaye 
    */
  DataSetC(unsigned int nbTransaction, unsigned int nbItem);
  
  
  /**
    * Constructeur par copie
    * Utilise les données d'un autre DataSetC pour instancier ses propres données
    * @param data : Un autre DataSetC
    * @author Johan defaye
    */
  DataSetC(const DataSetC & data);
  
  
  /* * * * * * *
   * ACCESSORS *
   * * * * * * */
  
  /**
   * Retourne le nombre de ligne du tableau 2D
   * @return : Nombre de ligne du tableau
   * @author Johan Defaye
   */
  unsigned int getNbLine() const {return _nbLine;}
  
  /**
   * Retourne le nombre de colonne du tableau 2D
   * @return : Nombre de colonne du tableau
   * @author Johan Defaye
   */
  unsigned int getNbCol() const {return _nbCol;}
  
  /**
   * Retourne les données sous forme de tableau 2D de char
   * @return : Pointeur sur pointeur de char
   * @author Johan Defaye
   */
  char ** getData() const {return _data;}
  
  /**
   * Retourne l'élément à la colonne Col et la ligne Row passés en 
   * paramètre.
   * @param unsigned row
   * @param unsigned col
   * @author Ugo Rayer
   */
  char getDataAt(unsigned row, unsigned col) const { return _data[row][col];}

  
  /* * * * * *
   * METHODS *
   * * * * * */
  
  /**
   * Affiche le tableau de donnée dans le flux passé en paramètre
   * @param flux : Flux pour l'affichage
   * @author Johan Defaye
   */
  void print(std::ostream & flux) const;
  
  
  /**
   * Prend un ItemSet en paramètre et retourne sa fréquence d'apparition dans le tableau
   * @param item : Un ItemSet
   * @return La fréquence entre 0 et 1 de l'ItemSet
   * @author Johan Defaye
   */
  float freqItemSet(const ItemSetC & item) const;
  
  
    /**
   * Prend un tableau de char et sa taille en paramètre et retourne sa fréquence d'apparition dans les données
   * @param t : Un tableau de char
   * @param size : Taille du tableau de char
   * @return La fréquence entre 0 et 1 du tableau de char
   * @author Johan Defaye
   */
  float freqItemSet(const char * t, unsigned int size) const;
  
  
  /**
   * Lit un fichier de donnée dont le nom est passé en paramètre et remplie les données du tableau avec
   * @param fileName : Chemin d'accès du fichier de donnée
   * @author Ugo Rayer
   */
  void loadFile(const std::string & fileName);
  
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  
  /**
   * Détruit le dataSet en désallouant la mémoire alloué pour le tableau de char
   * @author Johan Defaye
   */
  ~DataSetC();
  
};



  /* * * * * * *
   * FUNCTIONS *
   * * * * * * */

/**
 * Surcharge de l'opérateur d'affichage
 * @param flux : un flux pour l'affichage
 * @param data :  DataSetC à afficher
 * @author Johan Defaye
 */
std::ostream & operator<<(std::ostream & flux, const DataSetC & data);



/**
 * Fonction utile à la lecture du fichier source. Utilise le séparateur ' '
 * @param str : chaîne de caractères à découper
 * @return un pointeur sur un vecteur contenant chaque mot de str
 * @author Ugo Rayer
 */
std::vector< std::string >& explode(const std::string& str);


#endif
#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "../include/itemSet.h"

/**
 * Représente un ensemble de transaction comme un tableau 2D de char (ou un tableau d'itemSet)
 * Chaque ligne représente une transaction(itemSet) et chaque colonne un item
 * La case de coordonnée [i,j] aura pour valeur 1 si l'item j figure
 * dans la transaction i et 0 s'il n'y figure pas
 * @author Johan Defaye
 */
class dataSet : public std::vector< itemSet > {
  
  
private:
  unsigned int _nbLine; // Nombre de ligne du tableau
  unsigned int _nbCol;  // Nombre de colonne du tableau
  
  
public:
  
  /* * * * * * * * *
   * CONSTRUCTORS  *
   * * * * * * * * */
  
  /**
    * Constructeur par défaut d'un dataSet
    * @author Johan Defaye
    */
  dataSet();

  
  /**
    * Constructeur prenant un nombre de ligne
    * Construit un tableau de transaction avec le nombre de transaction passé en paramètre
    * @param nbTransaction : Nombre de ligne du tableau
    * @author Johan Defaye 
    */
  dataSet(unsigned int nbTransaction);
  
  
  /**
    * Constructeur par copie
    * Utilise les données d'un autre dataSet pour instancier ses propres données
    * @param data : Un autre dataSet
    * @author Johan defaye
    */
  dataSet(const dataSet & data);
  
  
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
   * Prend un itemSet en paramètre et retourne sa fréquence d'apparition dans le tableau
   * @param item : Un itemSet
   * @author Johan Defaye
   */
  float freqItemSet(const itemSet & item) const;
  
  
  /**
   * Lit un fichier de donnée dont le nom est passé en paramètre et remplie les données du tableau avec
   * @param fileName : Chemin d'accès du fichier de donnée
   * @author Ugo Rayer
   */
  void loadFile(const std::string & fileName);
  
};



  /* * * * * * *
   * FUNCTIONS *
   * * * * * * */

/**
 * Surcharge de l'opérateur d'affichage
 * @param flux : un flux pour l'affichage
 * @param data :  dataSet à afficher
 * @author Johan Defaye
 */
std::ostream & operator<<(std::ostream & flux, const dataSet & data);



/**
 * Fonction utile à la lecture du fichier source. Utilise le séparateur ' '
 * @param str : chaîne de caractères à découper
 * @return un pointeur sur un vecteur contenant chaque mot de str
 * @author Ugo Rayer
 */
std::vector< std::string >& explode(const std::string& str);


#endif
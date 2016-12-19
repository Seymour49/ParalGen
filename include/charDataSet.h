#ifndef CHARDATASET_H
#define CHARDATASET_H

#include "dataSet.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * Représente un ensemble de transaction comme un tableau 2D de char
 * @author Johan Defaye
 */
class CharDataSet : public DataSet<char> {
  
public:
  
  /* * * * * * * * *
   * CONSTRUCTORS  *
   * * * * * * * * */
  
  
  /**
    * Constructeur par défaut d'un CharDataSet
    * @author Johan Defaye
    */
  CharDataSet();

  
  /**
    * Constructeur prenant un nombre de ligne en paramètre
    * Construit un tableau de transaction avec le nombre de transaction passé en paramètre
    * @param nbTransaction : Nombre de ligne du tableau
    * @author Johan Defaye 
    */
  CharDataSet(unsigned int nbTransaction, unsigned int nbItem);
  
  
  /**
    * Constructeur par copie
    * Utilise les données d'un autre CharDataSet pour instancier ses propres données
    * @param data : Un autre CharDataSet
    * @author Johan Defaye
    */
  CharDataSet(const CharDataSet & data);
  
  

  
  /* * * * * *
   * METHODS *
   * * * * * */

  /**
    * Lit un fichier de donnée dont le nom est passé en paramètre et remplie les données du tableau avec
    * @param fileName : Chemin d'accès du fichier de donnée
    * @author Ugo Rayer
    */
  void loadFile(const std::string & fileName);
  
  
  /* * * * * * * * * * * * *
   * OPERATOR OVERLOADING  *
   * * * * * * * * * * * * */
  
  
  /**
   * Opérateur d'affectation, prend en paramètre un autre charDataSet
   * @param c : un autre charDataSet
   * @author Johan Defaye 
   */
  CharDataSet & operator=(const CharDataSet & c);
    
};



  /* * * * * * *
   * FUNCTIONS *
   * * * * * * */



/**
 * Fonction utile à la lecture du fichier source. Utilise le séparateur ' '
 * @param str : chaîne de caractères à découper
 * @return un pointeur sur un vecteur contenant chaque mot de str
 * @author Ugo Rayer
 */
std::vector< std::string > explode(const std::string& str);


#endif
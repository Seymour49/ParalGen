#ifndef CHARDATASETO_H
#define CHARDATASETO_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "dataSetO.h"

class CharDataSetO : public DataSetO<char> {
  
public:
  
  
  /**
   * Constructeur par défaut
   * @author Johan Defaye
   */
  CharDataSetO();
  
  
  /**
   * Constructeur par paramètres
   * @param nbTransaction : Nombre de transaction
   * @param nbItem :  Nombre d'item par transaction 
   * @author Johan Defaye
   */
  CharDataSetO(unsigned int nbTransaction, unsigned int nbItem);
  
  
  /**
   * Constructeur par recopie
   * @param data : un autre jeu de donnée
   * @author Johan Defaye
   */
  CharDataSetO(const CharDataSetO & data);
  
  
  /**
   * Lit un fichier de donnée dont le nom est passé en paramètre et remplie les données du tableau avec
   * @param fileName : Chemin d'accès du fichier de donnée
   * @author Ugo Rayer
   */
  void loadFile(const std::string & fileName);
 
  
  
  /* * * * * * * * * * * * *
   * OPERATOR OVERLOADING  *
   * * * * * * * * * * * * */
  
  CharDataSetO & operator=(const CharDataSetO & c);
  
};


std::vector< std::string > explode(const std::string& str);



#endif
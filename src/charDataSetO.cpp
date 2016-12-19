#include "../include/charDataSetO.h"

using namespace std;


CharDataSetO::CharDataSetO(): DataSetO< char >(0,0)
{}



CharDataSetO::CharDataSetO(unsigned int nbTransaction, unsigned int nbItem): DataSetO< char >(nbTransaction,nbItem)
{
  _data = new char*[_nbLine];
  for (unsigned int i = 0; i < _nbLine; ++i) {
    _data[i] = new char[_nbCol];
    for (unsigned int j = 0; j < _nbCol; ++j) {
      _data[i][j] = '0';
    }
  }
}



CharDataSetO::CharDataSetO(const CharDataSetO& data): DataSetO< char >(data)
{}



void CharDataSetO::loadFile(const string& fileName)
{
  
  if ((_nbLine == 0)&&(_nbCol == 0)) {
    ifstream f(fileName.c_str());
    vector< vector<int> > matrice;
    
    if(!f){
      throw string("Erreur lors de l'ouverture du fichier " + fileName + " !");
    }
    else {
      string line;
      while(getline(f,line)){
	if (!line.empty()) {
	  vector<string> tokens = explode(line);
	  vector<int> row;
	  // Traitement
	  for (unsigned int i = 0; i < tokens.size(); ++i){
	    row.push_back(atoi(tokens[i].c_str()));
	  }
	  matrice.push_back(row);
	}
      }
      int Cols = 0;
      int Rows = matrice.size();
      int start_index = 1; // indice du premier item
      for (int i = 0; i < Rows; ++i){ // Recherche du nombre maximum d'item et de l'indice du premier item
	if (matrice[i].back() > Cols) Cols = matrice[i].back();
	if (matrice[i].front() < start_index) start_index = matrice[i].front();
      }
      
      _nbLine = (unsigned int) Rows;
      _nbCol = (unsigned int) Cols;
      
      _data = new char*[_nbLine];
      for (unsigned int i = 0; i < _nbLine; ++i) {
	_data[i] = new char[_nbCol];
      }
      
      for (unsigned int i = 0; i < _nbLine; ++i){
	for (unsigned int j = 0; j < _nbCol; ++j) _data[i][j] = '0';
	for (unsigned int it = 0; it < matrice[i].size(); ++it){
	  _data[i][matrice[i][it]-start_index] = '1';
	}
      }
      
    }
    f.close();
  } 
  else throw string("Impossible de charger plusieurs fois les données d'un fichier sur un même CharDataSetO !");
}


CharDataSetO& CharDataSetO::operator=(const CharDataSetO& c)
{
  // Suppression des anciennes données
  if (_nbLine != 0) {
    if (_nbCol != 0) {
      for (unsigned int i = 0; i < _nbLine; ++i) {
	delete [] _data[i];
      }
    }
    delete [] _data;
  }
  // Ajustement de la nouvelle taille
  _nbLine = c.getNbLine();
  _nbCol = c.getNbCol();
  
  // Copie des données
  _data = new char*[_nbLine];
  for (unsigned int i = 0; i < _nbLine; ++i) {
    
    _data[i] = new char[_nbCol];
    
    for (unsigned int j = 0; j < _nbCol; ++j) {
      _data[i][j] = c[i][j];
    }
    
  }
  return *this;
}



vector< string > explode(const string& str)
{
  istringstream split(str);
  vector< string > tokens;

  for(string each; getline(split, each, ' '); tokens.push_back( each.c_str()) );

  return tokens;
}

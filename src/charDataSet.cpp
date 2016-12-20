#include "../include/charDataSet.h"

using namespace std;


CharDataSet::CharDataSet(): DataSet< char >(0,0)
{}


CharDataSet::CharDataSet(unsigned int nbLine, unsigned int nbItem): DataSet< char >(nbLine, nbItem)
{
  this->resize(_nbLine);
  vector<char> v;
  v.assign(_nbCol, '0');
  for (unsigned int i = 0; i < _nbLine; ++i) {
    at(i) = v;
  }
}


CharDataSet::CharDataSet(const CharDataSet& data): DataSet< char >(data)
{}




void CharDataSet::loadFile(const string& fileName)
{
  if ((_nbLine == 0)&&(_nbCol == 0)) {
    ifstream f(fileName.c_str());
    vector< vector<int> > matrice;
    
    if(!f){	    
      throw string("Erreur lors de l'ouverture du fichier " + fileName + " !");
    }
    else {
      
      // Test pour savoir s'il s'agit d'un fichier csv ou non
      
      string line;
      
      // On lit la première ligne du fichier et si elle n'est composé que de '0' et de '1'
      // On applique le traitement d'un fichier csv
      
      getline(f, line);
      
      while (getline(f,line)){
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
      this->clear();
      this->resize(_nbLine);
      for (int i = 0; i < Rows; ++i){
	this->at(i).assign(_nbCol, '0');
	for (unsigned int it = 0; it < matrice[i].size(); ++it) {
	  this->at(i).at(matrice[i][it]-start_index) = '1';
	}
      }
    }
    f.close();
  }
  else throw string("Impossible de charger plusieurs fois les données d'un fichier sur un même CharDataSet !"); 
}



CharDataSet& CharDataSet::operator=(const CharDataSet& c)
{
  _nbLine = c.getNbLine();
  _nbCol = c.getNbCol();
  this->resize(_nbLine);
  for (unsigned int i = 0; i < _nbLine; ++i) {
    
    this->at(i).resize(_nbCol);
    
    for (unsigned int j = 0; j < _nbCol; ++j) {
      this->at(i).at(j) = c[i][j];
    }
    
  }
  return *this;
}


vector< string > explode(const string& str)
{
  istringstream split(str);
  vector< string > tokens;

  for (string each; getline(split, each, ' '); tokens.push_back( each.c_str()) );

  return tokens;
}
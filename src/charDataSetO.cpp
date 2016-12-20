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
  
  if ((_nbLine != 0)||(_nbCol != 0)) {
    for (unsigned int i = 0; i < _nbLine; ++i) delete []_data[i];
    delete [] _data;
  }
    
  ifstream f(fileName.c_str());
  
  if(!f) throw string("Erreur lors de l'ouverture du fichier " + fileName + " !");
  else {
    
    string line;
    bool isCSV = true;
    vector<string> tokens;
    bool firstLineRead = false;
    
    // On lit la première ligne du fichier et si elle n'est composé que de '0' et de '1' on applique le traitement d'un fichier csv
    
    while (!firstLineRead) { // Tant qu'on lit des lignes vides on continue
      getline(f, line);
    
      if (!line.empty()) {
	tokens = explode2(line);
	// Traitement
	for (unsigned int i = 0; (i < tokens.size())&&(isCSV); ++i){
	  if (tokens[i].size() != 1) isCSV = false;
	  else if ((tokens[i][0] != '0') && (tokens[i][0] != '1')) isCSV = false;
	}
	firstLineRead = true;
      }
    }
    
    if (isCSV) { // Lecture de matrice composé exclusivement de '0' et de '1'
      vector <char> tmp;
      vector< vector<char> > matrice;
      unsigned int nbCol;
      for (unsigned int i = 0; i < tokens.size(); ++i) {
	if (tokens[i].size() != 1) throw string("Erreur, format du jeu de donnée à lire non conforme !");
	else tmp.push_back(tokens[i][0]);
      }
      matrice.push_back(tmp);
      nbCol = tmp.size();
      while (getline(f,line)){
	if (!line.empty()) {
	  tmp.clear();
	  tokens = explode2(line);
	  for (unsigned int i = 0; i < tokens.size(); ++i) {
	    if (tokens[i].size() != 1) throw string("Erreur, format de jeu de donnée à lire non conforme !");
	    else {
	      tmp.push_back(tokens[i][0]);
	    }
	  }
	  if (tmp.size() != nbCol) throw string("Erreur, format de jeu de donnée à lire non conforme !");
	  else matrice.push_back(tmp);
	}
      }
      _nbCol = nbCol;
      _nbLine = matrice.size();

      _data = new char *[_nbLine];
      for (unsigned int i = 0; i < _nbLine; ++i) {
	_data[i] = new char[_nbCol];
	for (unsigned int j = 0; j < _nbCol; ++j) _data[i][j] = matrice[i][j];
      }
    }
    else { // Lecture d'un fichier basique de transaction
      vector< vector<int> > matrice;
      vector<int> row;
      for (unsigned int i = 0; i < tokens.size(); ++i){
	row.push_back(atoi(tokens[i].c_str()));
      }
      matrice.push_back(row);
      
      while (getline(f,line)){
	if (!line.empty()) {

	  vector<string> tokens = explode2(line);
	  vector<int> row;

	  // Traitement
	  for (unsigned int i = 0; i < tokens.size(); ++i){
	    row.push_back(atoi(tokens[i].c_str()));
	  }
	  matrice.push_back(row);
	}
      }
      unsigned int Cols = 0;
      unsigned int Rows = matrice.size();
      int start_index = 1; // indice du premier item
      for (unsigned int i = 0; i < Rows; ++i){ // Recherche du nombre maximum d'item et de l'indice du premier item
	if (matrice[i].back() > (int)Cols) Cols = matrice[i].back();
	if (matrice[i].front() < start_index) start_index = matrice[i].front();
      }
      
      _nbLine = Rows;
      _nbCol = Cols;
      
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
  }
  f.close();
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



vector< string > explode2(const string& str)
{
  istringstream split(str);
  vector< string > tokens;

  for(string each; getline(split, each, ' '); tokens.push_back( each.c_str()) );

  return tokens;
}

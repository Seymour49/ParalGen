#include "../include/dataSet.h"

using namespace std;


vector< string >& explode(const string& str)
{
  istringstream split(str);
  vector< string >* tokens = new vector<string>;

  for(string each; getline(split, each, ' '); tokens->push_back( each.c_str()) );

  return *tokens;
}



dataSet::dataSet(): _nbLine(0), _nbCol(0)
{}



dataSet::dataSet(unsigned int nbLine): _nbLine(nbLine), _nbCol(0)
{
  resize(_nbLine);
  vector<char> v;
  for (unsigned int i = 0; i < _nbLine; ++i) {
    at(i) = v;
  }
}



dataSet::dataSet(const dataSet& data): vector<vector<char>>(data), _nbLine(data.getNbLine()), _nbCol(data.getNbCol())
{}


void dataSet::print(ostream& flux) const
{
  for (unsigned int i = 0; i < _nbLine; ++i) {
    for (unsigned int j = 0; j < _nbCol; ++j) {
      flux << this->at(i).at(j) << " ";
    }
    flux << endl;
  }
}


float dataSet::freqItemSet(const itemSet& item) const
{
  int nbOccurrence = 0;
  
  if (item.size() != _nbCol) {
    cerr << "Erreur ! L'itemSet ne correspond pas au fichier de donnée" << endl;
  }
  for (unsigned int i = 0; i < _nbLine; ++i) {
    for (unsigned int j = 0; j < _nbCol; ++j) {
      
    }
  }
}


float dataSet::freqItemSet(const vector< char >& v) const
{

}



void dataSet::loadFile(const string& fileName)
{
  ifstream f(fileName.c_str());
  vector< vector<int> > matrice;
  
  if(!f){	    
    cerr << "Erreur pendant l'ouverture du fichier" << endl;
  }
  else {
    string line;
    while(getline(f,line)){
      vector<string>& tokens = explode(line);
      vector<int> row;
      // Traitement
      for(unsigned int i = 0; i < tokens.size(); ++i){
	row.push_back(atoi(tokens[i].c_str()));
      }
      matrice.push_back(row);
      delete(&tokens);
    }
    int Cols = 0;
    int Rows = matrice.size();
    int start_index = 1; // indice du premier item
    for(int i = 0; i < Rows; ++i){ // Recherche du nombre maximum d'item et de l'indice du premier item
      if (matrice[i].back() > Cols) Cols = matrice[i].back();
      if (matrice[i].front() < start_index) start_index = matrice[i].front();
    }
    _nbLine = (unsigned int) Rows;
    _nbCol = (unsigned int) Cols;
    resize(_nbLine);
    for (int i = 0; i < Rows; ++i){
      vector<char> line;
      line.assign(_nbCol, '0');
      for (unsigned int it = 0; it < matrice[i].size(); ++it){
	line[matrice[i][it]-start_index] = '1';
      }
      at(i) = line;
   }
  }
}



ostream& operator<<(ostream& flux, const dataSet& data)
{
  data.print(flux);
  return flux;
}
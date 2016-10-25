#include "../include/dataSet.h"

using namespace std;


vector< string >& explode2(const string& str)
{
  istringstream split(str);
  vector< string >* tokens = new vector<string>;

  for(string each; getline(split, each, ' '); tokens->push_back( each.c_str()) );

  return *tokens;
}



DataSet::DataSet(): _nbLine(0), _nbCol(0)
{}



DataSet::DataSet(unsigned int nbLine): _nbLine(nbLine), _nbCol(0)
{
  resize(_nbLine);
  vector<char> v;
  v.assign(_nbCol, '0');
  for (unsigned int i = 0; i < _nbLine; ++i) {
    at(i) = v;
  }
}



DataSet::DataSet(const DataSet& data): vector<vector<char>>(data), _nbLine(data.getNbLine()), _nbCol(data.getNbCol())
{}


void DataSet::print(ostream& flux) const
{
  for (unsigned int i = 0; i < _nbLine; ++i) {
    for (unsigned int j = 0; j < _nbCol; ++j) {
      flux << this->at(i).at(j) << " ";
    }
    flux << endl;
  }
}



float DataSet::freqItemSet(const ItemSet& item) const
{
  float nbOccurrence = 0;
  
  if (item.getSize() != _nbCol) {
    throw string("Erreur ! L'itemSet ne correspond pas au fichier de donnée");
  }
  else {
    bool newOccurrence;
    for (unsigned int i = 0; i < _nbLine; ++i) {
      newOccurrence = true;
      for (unsigned int j = 0; ((j < _nbCol)&&newOccurrence); ++j) {
	if (item.getBitset()[j] == '1')  {
	  if (this->at(i).at(j) != '1') newOccurrence = false;
	}
      }
      if (newOccurrence) nbOccurrence++;
    }
  }
  return (nbOccurrence/_nbLine);
}


float DataSet::freqItemSet(const vector< char >& v) const
{
  float nbOccurrence = 0;
  
  if (v.size() != _nbCol) {
    throw string("Erreur ! L'itemSet ne correspond pas au fichier de donnée");
  }
  else {
    bool newOccurrence;
    for (unsigned int i = 0; i < _nbLine; ++i) {
      newOccurrence = true;
      for (unsigned int j = 0; (j < _nbCol)&&(newOccurrence); ++j) {
	if (v[j] == '1') {
	  if (this->at(i).at(j) != '1') newOccurrence = false;
	}
      }
      if (newOccurrence) nbOccurrence++;
    }
  }
  return (nbOccurrence/_nbLine);
}



void DataSet::loadFile(const string& fileName)
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
	  vector<string>& tokens = explode2(line);
	  vector<int> row;
	  // Traitement
	  for (unsigned int i = 0; i < tokens.size(); ++i){
	    row.push_back(atoi(tokens[i].c_str()));
	  }
	  matrice.push_back(row);
	  delete(&tokens);
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
      clear();
      resize(_nbLine);
      for (int i = 0; i < Rows; ++i){
	vector<char> line;
	line.assign(_nbCol, '0');
	for (unsigned int it = 0; it < matrice[i].size(); ++it) {
	  line[matrice[i][it]-start_index] = '1';
	}
	at(i) = line;
      }
    }
    f.close();
  } else {
    cerr << "Impossible de charger plusieurs fois les données d'un fichier sur un même DataSet !" << endl; 
  }
}



ostream& operator<<(ostream& flux, const DataSet& data)
{
  data.print(flux);
  return flux;
}
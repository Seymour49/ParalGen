#include "../include/dataSet.h"

using namespace std;


vector< string >& explode(const string& str)
{
  istringstream split(str);
  vector< string >* tokens = new vector<string>;

  for(string each; getline(split, each, ' '); tokens->push_back( each.c_str()) );

  return *tokens;
}



DataSet::DataSet(): _nbLine(0), _nbCol(0)
{}



DataSet::DataSet(unsigned int nbTransaction, unsigned int nbItem): _nbLine(nbTransaction), _nbCol(nbItem)
{
  _data = new char*[_nbLine];
  for (unsigned int i = 0; i < _nbLine; ++i) {
    _data[i] = new char[_nbCol];
  }
}



DataSet::DataSet(const DataSet& data): _nbLine(data.getNbLine()), _nbCol(data.getNbCol())
{
  _data = new char*[_nbLine];
  for (unsigned int i = 0; i < _nbLine; ++i) {
    _data[i] = new char[_nbCol];
    for (unsigned int j = 0; j < _nbCol; ++j) {
      _data[i][j] = data.getData()[i][j];
    }
  }
}


void DataSet::print(ostream& flux) const
{
  for (unsigned int i = 0; i < _nbLine; ++i) {
    for (unsigned int j = 0; j < _nbCol; ++j) {
      flux << _data[i][j] << " ";
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
      for (unsigned int j = 0; ((j < item.getSize())&&newOccurrence); ++j) {
	if (item.getBitset()[i][j] == '1')  {
	  if (_data[i][j]!= '1') newOccurrence = false;
	}
      }
      if (newOccurrence) nbOccurrence++;
    }
  }
  return (nbOccurrence/_nbLine);
}


float DataSet::freqItemSet(const char * t, unsigned int size) const
{
  float nbOccurrence = 0;
  
  if (size != _nbCol) {
    throw string("Erreur ! L'itemSet ne correspond pas au fichier de donnée");
  }
  else {
    bool newOccurrence;
    for (unsigned int i = 0; i < _nbLine; ++i) {
      newOccurrence = true;
      for (unsigned int j = 0; (j < _nbCol)&&(newOccurrence); ++j) {
	if (t[j] == '1') {
	  if (_data[i][j] != '1') newOccurrence = false;
	}
      }
      if (newOccurrence) nbOccurrence++;
    }
  }
  return (nbOccurrence/_nbLine);
}



void DataSet::loadFile(const string& fileName)
{
  ifstream f(fileName.c_str());
  vector< vector<int> > matrice;
  
  if(!f){	    
    throw string("Erreur lors de l'ouverture du fichier " + fileName + " !");
  }
  else {
    string line;
    while(getline(f,line)){
      if (line.empty()) throw string("Fichier non conforme! Il existe une ligne vide dans le fichier");
      vector<string>& tokens = explode(line);
      vector<int> row;
      // Traitement
      for (unsigned int i = 0; i < tokens.size(); ++i){
	row.push_back(atoi(tokens[i].c_str()));
      }
      matrice.push_back(row);
      delete(&tokens);
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
    
    _data = (char **)malloc(_nbLine*sizeof(char *));
    for (unsigned int i = 0; i < _nbLine; ++i) {
      _data[i] = (char *)malloc(_nbCol*sizeof(char));
    }
    for (int i = 0; i < _nbLine; ++i){
      char * line = (char *)malloc(_nbCol*sizeof(char));
      for (unsigned int i = 0; i < _nbCol; ++i) line[i] = '0';
      for (unsigned int it = 0; it < matrice[i].size(); ++it){
	line[matrice[i][it]-start_index] = '1';
      }
      _data[i] = line;
   }
  }
}


DataSet::~DataSet()
{
  for (unsigned int i = 0; i < _nbLine; ++i) {
    delete(_data[i]);
  }
  delete [](_data);
}




ostream& operator<<(ostream& flux, const DataSet& data)
{
  data.print(flux);
  return flux;
}
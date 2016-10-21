#include "../include/dataSetC.h"

using namespace std;


vector< string >& explode(const string& str)
{
  istringstream split(str);
  vector< string >* tokens = new vector<string>;

  for(string each; getline(split, each, ' '); tokens->push_back( each.c_str()) );

  return *tokens;
}



DataSetC::DataSetC(): _nbLine(0), _nbCol(0)
{}



DataSetC::DataSetC(unsigned int nbTransaction, unsigned int nbItem): _nbLine(nbTransaction), _nbCol(nbItem)
{
  _data = new char*[_nbLine];
  for (unsigned int i = 0; i < _nbLine; ++i) {
    _data[i] = new char[_nbCol];
    for (unsigned int j = 0; j < _nbCol; ++j) {
      _data[i][j] = '0';
    }
  }
}



DataSetC::DataSetC(const DataSetC& data): _nbLine(data.getNbLine()), _nbCol(data.getNbCol())
{
  _data = new char*[_nbLine];
  for (unsigned int i = 0; i < _nbLine; ++i) {
    _data[i] = new char[_nbCol];
    for (unsigned int j = 0; j < _nbCol; ++j) {
      _data[i][j] = data.getData()[i][j];
    }
  }
}


void DataSetC::print(ostream& flux) const
{
  for (unsigned int i = 0; i < _nbLine; ++i) {
    for (unsigned int j = 0; j < _nbCol; ++j) {
      flux << _data[i][j] << " ";
    }
    flux << endl;
  }
}



float DataSetC::freqItemSet(const ItemSetC& item) const
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
	  if (_data[i][j]!= '1') newOccurrence = false;
	}
      }
      if (newOccurrence) nbOccurrence++;
    }
  }
  return (nbOccurrence/_nbLine);
}


float DataSetC::freqItemSet(const char * t, unsigned int size) const
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



void DataSetC::loadFile(const string& fileName)
{
  ifstream f(fileName.c_str());
  vector< vector<int> > matrice;
  
  if(!f){	    
    throw string("Erreur lors de l'ouverture du fichier " + fileName + " !");
  }
  else {
    string line;
    while(getline(f,line)){
      if (!line.empty()) {
	vector<string>& tokens = explode(line);
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
    if (_data != NULL) {
      for (unsigned int i = 0; i < _nbLine; ++i) {
	delete [] (_data[i]);
      }
      if (_nbLine != 0) delete [] (_data);
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


DataSetC::~DataSetC()
{
  for (unsigned int i = 0; i < _nbLine; ++i) {
    delete [] (_data[i]);
  }
  if (_nbLine != 0) delete [] (_data);
}




ostream& operator<<(ostream& flux, const DataSetC& data)
{
  data.print(flux);
  return flux;
}

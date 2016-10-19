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
  itemSet item;
  for (unsigned int i = 0; i < _nbLine; ++i) {
    at(i) = item;
  }
}



dataSet::dataSet(const dataSet& data): vector<itemSet>(data), _nbLine(data.getNbLine()), _nbCol(data.getNbCol())
{}


void dataSet::print(ostream& flux) const
{
  for (unsigned int i = 0; i < _nbLine; ++i) {
    flux << at(i) << endl;
  }
}


float dataSet::freqItemSet(const itemSet& item) const
{
  return 0.0;
}



void dataSet::loadFile(const string& fileName)
{
  ifstream f(fileName.c_str());
  vector< vector<unsigned int> > matrice;
  
  if(!f){	    
    cerr << "Erreur pendant l'ouverture du fichier" << endl;
  }
  else {
    string line;
    while(getline(f,line)){
      vector<string>& tokens = explode(line);
      vector<unsigned int> row;
      // Traitement
      for(unsigned i=0; i<tokens.size(); ++i){
	row.push_back(atoi(tokens[i].c_str()));
      }
      matrice.push_back(row);
      delete(&tokens);
    }
    unsigned int Cols = 0;
    unsigned int Rows = matrice.size()-1;
    resize(Rows);
    for(unsigned i=0; i < Rows; ++i){ // Recherche du nombre d'item
	if( matrice[i].back() > Cols) Cols = matrice[i].back();
    }
    _nbLine = Rows;
    _nbCol = Cols;
    cout << "ligne = " << _nbLine << "\t colonnes = " << _nbCol << endl;
    resize(_nbLine);
    for(unsigned i=0; i < Rows; ++i){
      cout << "début " << i << endl;
      vector<char> line;
      line.assign(_nbCol, '0');
      cout << "ici 0 " << endl;
      for(unsigned it=0; it < matrice[i].size(); ++it){
	cout << "\t" << matrice[i][it]-1 << endl;
	  line[matrice[i][it]-1] = '1';
      }
      cout << "ici 1" << endl;
      at(i) = line;
      cout << "ici 2" << endl;
   }
  }
}



ostream& operator<<(ostream& flux, const dataSet& data)
{
  data.print(flux);
  return flux;
}
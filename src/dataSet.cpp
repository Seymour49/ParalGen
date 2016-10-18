#include "../include/dataSet.h"

using namespace std;


vector< string >& explode(const string& str)
{
  istringstream split(str);
  vector< string >* tokens = new vector<string>;

  for(string each; getline(split, each, ' '); tokens->push_back( each.c_str()) );

  return *tokens;
}



dataSet::dataSet(): _nbLine(0), _nbRow(0)
{}



dataSet::dataSet(unsigned int nbLine, unsigned int nbRow): _nbLine(nbLine), _nbRow(nbRow)
{}



dataSet::dataSet(const dataSet& data): vector<itemSet>(data), _nbLine(data.getNbLine()), _nbRow(data.getNbRow())
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


ostream& operator<<(ostream& flux, const dataSet& data)
{
  data.print(flux);
  return flux;
}
#include "../include/itemSet.h"


using namespace std;


itemSet::itemSet()
{}


itemSet::itemSet(const vector< char >& v): vector<char>(v)
{}



itemSet::itemSet(const itemSet& i): vector<char>(i)
{}




vector< int > itemSet::getListItem() const
{
  vector<int> listItem; // Valeur de retour
  
  for (unsigned int i = 0; i < size(); ++i) {
    if (at(i) == '1') listItem.push_back(i + 1);
  }
  
  return listItem;
}



void itemSet::print(ostream& flux) const
{
  if (size() > 0) flux << at(0);
  for (unsigned int i = 1; i < size(); ++i) {
    flux << " " << at(i);
  }
}



ostream& operator<<(ostream& flux, const itemSet& i)
{
  i.print(flux);
  return flux;
}

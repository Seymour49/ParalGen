#include "../include/itemSet.h"


using namespace std;


ItemSet::ItemSet()
{}


ItemSet::ItemSet(const vector< char >& v): vector<char>(v)
{}


ItemSet::ItemSet(const ItemSet& i): vector<char>(i)
{}




vector< int > ItemSet::getListItem() const
{
  vector<int> listItem; // Valeur de retour
  
  for (unsigned int i = 0; i < size(); ++i) {
    if (at(i) == '1') listItem.push_back(i + 1);
  }
  
  return listItem;
}



void ItemSet::print(ostream& flux) const
{
  if (size() > 0) flux << at(0);
  for (unsigned int i = 1; i < size(); ++i) {
    flux << " " << at(i);
  }
}



ostream& operator<<(ostream& flux, const ItemSet& i)
{
  i.print(flux);
  return flux;
}

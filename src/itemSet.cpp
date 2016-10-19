#include "../include/itemSet.h"
#include <time.h>

using namespace std;


ItemSet::ItemSet(): Individual()
{}


ItemSet::ItemSet(const vector< char >& v):Individual(), _bitset(v)
{}


ItemSet::ItemSet(const ItemSet& i):Individual(), _bitset(i._bitset)
{}


void ItemSet::Mutate()
{  

}

Individual& ItemSet::CrossClassic(const Individual& ind, std::size_t pos)
{
  
  ItemSet* res = new ItemSet();
  return *res;
}



vector< int > ItemSet::getListItem() const
{
  vector<int> listItem; // Valeur de retour
  
  for (unsigned int i = 0; i < _bitset.size(); ++i) {
    if (_bitset.at(i) == '1') listItem.push_back(i + 1);
  }
  
  return listItem;
}



void ItemSet::print(ostream& flux) const
{
  Individual::print(flux);
  flux << endl << "Bitset : ";
  
  if (_bitset.size() > 0) flux << _bitset.at(0);
  for (unsigned int i = 1; i < _bitset.size(); ++i) {
    flux << " " << _bitset.at(i);
  }
  
  flux << endl;
}



ostream& operator<<(ostream& flux, const ItemSet& i)
{
  i.print(flux);
  return flux;
}

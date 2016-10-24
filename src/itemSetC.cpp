#include "../include/itemSetC.h"


using namespace std;



ItemSetC::ItemSetC(): Individual(), _nbItems(0)
{
    _bitset = NULL;
}


ItemSetC::ItemSetC(char* v, int nbI):Individual(),_nbItems(nbI)
{
    _bitset = new char[_nbItems];
    for(unsigned i=0; i < _nbItems; ++i){
	_bitset[i] = v[i];
    }
}


ItemSetC::ItemSetC(const ItemSetC& it):Individual(it), _nbItems(it._nbItems)
{
    _bitset = new char[_nbItems];
    for(unsigned i=0; i < _nbItems; ++i){
	_bitset[i] = it.getBitsetAt(i);
    }
}


ItemSetC::~ItemSetC()
{
  delete[] _bitset;
}


void ItemSetC::setBitset(char* BS, unsigned size)
{
    if(BS != NULL){
	_nbItems = size;
	delete _bitset;
	_bitset = new char[size];
	for(unsigned i=0; i < size;++i){
	  _bitset[i] = BS[i]; 
	}
    }
}


vector< int > ItemSetC::getListItem() const
{
  vector<int> listItem; // Valeur de retour
  for (unsigned int i = 0; i < _nbItems; ++i) {
    if (_bitset[i] == '1') listItem.push_back(i + 1);
  }
  return listItem;
}


void ItemSetC::print(ostream& flux) const
{
  Individual::print(flux);
  flux<< "Bitset : ";
  
  if (_nbItems > 0) flux << _bitset[0];
  for (unsigned int i = 1; i < _nbItems; ++i) {
    flux << "" << _bitset[i];
  }
  
  flux << endl;
}


ostream& operator<<(ostream& flux, const ItemSetC& i)
{
  i.print(flux);
  return flux;
}

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


ItemSetC ItemSetC::CrossMultiPoint(const ItemSetC& it, const vector< unsigned int >& pivots) const
{
  ItemSetC res;
  if (pivots.empty()) throw string("Erreur ! La liste de pivots est vide");
  else {
    if (it.getSize() != _nbItems) {
      throw string("Erreur ! Les deux individus du croisement sont de taille différente");
    }
    else {
      char * bitSet = new char[_nbItems];
      unsigned int i = 0, tmp = 0;
      bool b = true; 
      while (i < _nbItems) {
	if (i > (pivots[tmp] - 1)) { 
	  b = (!b);
	  tmp++;
	}
	if (b) bitSet[i] = _bitset[i];
	else bitSet[i] = it.getBitsetAt(i);
	i++;
      }
      res.setBitset(bitSet, _nbItems);
    }
  }
  return res;
}


ItemSetC ItemSetC::CrossUniform(const ItemSetC& it) const
{
  ItemSetC res;
  if (it.getSize() != _nbItems) {
    throw string("Erreur ! Les deux individus du croisement sont de taille différente");
  }
  else {
    char * bitSet = new char[_nbItems];
    for (unsigned int i = 0; i < _nbItems; ++i) {
      int alea = rand()%2;
      if (alea == 0) {
	bitSet[i] = _bitset[i];
      }
      else {
	bitSet[i] = it.getBitsetAt(i);
      }
    }
    res.setBitset(bitSet, _nbItems);
  }
  return res;
}


void ItemSetC::Mutate()
{  
    srand(time(NULL));
    int pivot = rand() % (_nbItems-1);
    
    if(_bitset[pivot] == '0')
	_bitset[pivot] = '1';
    else
	_bitset[pivot] = '0';
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

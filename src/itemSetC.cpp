#include "../include/itemSetC.h"
#include <time.h>
#include <algorithm>

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


void ItemSetC::setBitset(char* BS, unsigned int size)
{
    if(BS != NULL) {
      _bitset = BS;
      _nbItems = size;
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
      bool b = true; // Vrai si l'individu fils récupère les données de l'ItemSetC courant et faux si il récupère les données de it (passé en paramètre)
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


void ItemSetC::setNbItems(int nbI)
{
    _nbItems = nbI;
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


Individual* ItemSetC::CrossClassic(const Individual * ind, std::size_t pos) const
{
  ItemSetC * res = new ItemSetC();
  if (ind != NULL) {
    ItemSetC const * it = dynamic_cast<ItemSetC const *>(ind);
    if (it != NULL) {
      if (it->getSize() != _nbItems) throw string("Erreur ! Les deux individus du croisement sont de taille différente");
      else {
	char* bitSet = new char[_nbItems];
	for (unsigned int i = 0; i < pos; ++i) {
	  bitSet[i] = _bitset[i];
	}
	for (unsigned int i = pos; i < _nbItems; ++i) {
	  bitSet[i] = it->getBitsetAt(i);
	}
	res->setBitset(bitSet, _nbItems);
      }
    }
    else throw string("Erreur lors du cast Individual vers ItemSet !");
  }
  else throw string("Erreur ! Individu à croiser vide");
  return res;
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

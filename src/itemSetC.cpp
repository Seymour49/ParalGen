#include "../include/itemSetC.h"
#include <time.h>

using namespace std;



ItemSetC::ItemSetC(): Individual()
{}


ItemSetC::ItemSetC(char* v, int nbI):Individual(), _bitset(v), _nbItems(nbI)
{}


ItemSetC::ItemSetC(const ItemSetC& i):Individual(i), _bitset(i._bitset), _nbItems(i._nbItems)
{}

void ItemSetC::setBitset(char* BS)
{
    if(BS != NULL) _bitset = BS;
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

Individual* ItemSetC::CrossClassic(const Individual * ind, std::size_t pos)
{
  ItemSetC * res = new ItemSetC();
  if (ind != NULL) {
    ItemSetC const * it = dynamic_cast<ItemSetC const *>(ind);
    if (it != NULL) {
      if (it->getSize() != _nbItems) throw string("Erreur ! Deux ItemSet à croiser de taille différente");
      else {
	char* tmp = new char[_nbItems];
	for (unsigned int i = 0; i < pos; ++i) {
	  tmp[i] = _bitset[i];
	}
	for (unsigned int i = pos; i < _nbItems; ++i) {
	  tmp[i] = it->getBitsetAt(i);
	}
	
	res->setBitset(tmp);
      }
    }
    else throw string("Erreur lors du cast Individual vers ItemSet !");
  }
  else throw string("Erreur ! Pointeur vers NULL");
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

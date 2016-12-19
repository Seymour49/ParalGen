#include "../include/freqPop.h"
#include <algorithm>
#include <utility>

#define toDigit(c) (c-'0')

using namespace std;



FreqPop::FreqPop(DataSet<char> * const data, float density): _data(data), _dataO(NULL), _density(density)
{}


FreqPop::FreqPop(DataSetO<char> * const dataO, float density): _data(NULL), _dataO(dataO), _density(density)
{}


FreqPop::FreqPop(DataSet< char > * const data, DataSetO< char > * const dataO, float density):_data(data), _dataO(dataO), _density(density)
{}


FreqPop::FreqPop(const FreqPop& f): _density(f.getDensity())
{}



/**
 * Fonction de comparaison entre deux paires <entier-float>
 * Renvoie vrai si f1 > f2
 * @author Ugo Rayer 
 */
bool descPair (const pair<int,float>& i, const pair<int,float>& j) { return (i.second > j.second); }



void FreqPop::execute(std::vector< Individual< char >* >& pop)
{
    if (pop.empty()) throw string("Erreur, la population à initialiser est vide !");
  
    else if (_data == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé !");
  
    else if (_data->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide !");
    
    else {
	unsigned line = _data->getNbLine();
	unsigned item = _data->getNbCol();
      
	vector<pair<int, float>> itemOcc;
	
	for(unsigned i=0; i < item; ++i){
	    pair<int,float> tmp(i,0);
	    itemOcc.push_back(tmp);
	    
	    for(unsigned j=0; j < line; ++j){
		itemOcc[i].second += toDigit( _data->getDataAt(j,i));
	    }
	}
      
	sort(itemOcc.begin(), itemOcc.end(), descPair);

	unsigned nbBrik = (item/10);
	int brik[nbBrik] = { };
	unsigned nbCiment = (item/5);
	int ciment[nbCiment] = { };
	int brikP = 0 ; int cimentP = 0;
	for(unsigned int i = 0; i < item; ++i){
	    if(i <= nbBrik){
		brik[brikP] = itemOcc[i].first;
		++brikP;
	    }
	    else if( i > nbBrik && i <= (nbBrik+nbCiment) ){
		ciment[cimentP] = itemOcc[i].first;
		++cimentP;
	    }
	}
	
	int selectedBrik;
	int selectedCiment;
	
	int indBrik;
	int indCiment;
	// Correspond à la densité choisie. 
	int max_bit = _density*100;
	for (unsigned int i = 0; i < pop.size(); ++i) {
	    pop[i]->resize(item);
	    for(unsigned int j = 0; j < item; ++j) (*pop[i])[j] = '0';
	    selectedBrik = rand() % max_bit;
	    selectedCiment = max_bit - selectedBrik;
	  
	    for (int j = 0; j < selectedBrik; ++j){
		indBrik = rand() % (nbBrik -1);
		(*pop[i])[brik[indBrik]] = '1';
	    }
	   
	    for (int j = 0; j < selectedCiment; ++j){
		indCiment = rand() % (nbCiment-1);
		(*pop[i])[ciment[indCiment]] = '1';
	    }
	}
    }
}


void FreqPop::executeO(std::vector< Individual< char >* >& pop)
{
  if (pop.empty()) throw string("Erreur, la population à initialiser est vide !");
  
  else if (_dataO == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé !");
  
  else if (_dataO->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide !");
  
  else {
      unsigned line = _dataO->getNbLine();
      unsigned item = _dataO->getNbCol();
    
      vector<pair<int, float>> itemOcc;
      
      for (unsigned int i = 0; i < item; ++i){
	  pair<int,float> tmp(i,0);
	  itemOcc.push_back(tmp);
	  
	  for(unsigned int j = 0; j < line; ++j){
	      itemOcc[i].second += toDigit( _dataO->getDataAt(j,i));
	  }
      }
    
      sort(itemOcc.begin(), itemOcc.end(), descPair);

      unsigned nbBrik = (item/10);
      int brik[nbBrik] = { };
      unsigned nbCiment = (item/5);
      int ciment[nbCiment] = { };
      int brikP = 0 ; int cimentP = 0;
      for(unsigned int i = 0; i < item; ++i){
	  if(i <= nbBrik){
	      brik[brikP] = itemOcc[i].first;
	      ++brikP;
	  }
	  else if( i > nbBrik && i <= (nbBrik+nbCiment) ){
	      ciment[cimentP] = itemOcc[i].first;
	      ++cimentP;
	  }
      }
      
      int selectedBrik = 0;
      int selectedCiment = 0;
      
      int indBrik = 0;
      int indCiment = 0;
      // Correspond à la densité choisie. 
      int max_bit = _density*100;
      
      for (unsigned int i = 0; i < pop.size(); ++i) {
	
	pop[i]->resize(item);
	for(unsigned int j = 0; j < item; ++j) (*pop[i])[j] = '0';
	selectedBrik = rand() % max_bit;
	selectedCiment = max_bit - selectedBrik;
      
	for(int j = 0; j < selectedBrik; ++j){
	    indBrik = rand() % (nbBrik -1);
	    (*pop[i])[brik[indBrik]] = '1';
	}
	
	for(int j = 0; j < selectedCiment; ++j){
	    indCiment = rand() % (nbCiment-1);
	    (*pop[i])[ciment[indCiment]] = '1';
	}
	
      }
  }
}



FreqPop::~FreqPop()
{
  
}

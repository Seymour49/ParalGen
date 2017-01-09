#include "../include/freqPop.h"

#define toDigit(c) (c-'0')

using namespace std;



FreqPop::FreqPop(DataSet< char >*const data, float sF): _data(data), _dataO(NULL), _seuilF(sF)
{}


FreqPop::FreqPop(DataSetO<char> * const dataO, float sF): _data(NULL), _dataO(dataO), _seuilF(sF)
{}


FreqPop::FreqPop(DataSet< char > * const data, DataSetO< char > * const dataO, float sF):_data(data), _dataO(dataO), _seuilF(sF)
{}


FreqPop::FreqPop(const FreqPop& f): _seuilF(f.getseuilF())
{}



/**
 * Fonction de comparaison entre deux paires <entier-float>
 * Renvoie vrai si f1 > f2
 * @author Ugo Rayer 
 */
bool descPair (const pair<int,float>& i, const pair<int,float>& j) { return (i.second > j.second); }



void FreqPop::execute(std::vector< Individual< char >* >& pop)
{
    if (pop.empty()) throw string("Erreur, la population à initialiser est vide ! (freqPop)");
  
    else if (_data == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé ! (freqPop)");
  
    else if (_data->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide ! (freqPop)");
    
    else {
	unsigned line = _data->getNbLine();
	unsigned item = _data->getNbCol();
      
	vector<pair<int, float>> itemOcc;
	
	for(unsigned i=0; i < item; ++i){
	    pair<int,float> tmp(i,0);
	    
	    for(unsigned j=0; j < line; ++j){
		tmp.second += toDigit( _data->getDataAt(j,i));
	    }
	    if( tmp.second >= _seuilF*line)
		itemOcc.push_back(tmp);
	}
      
	sort(itemOcc.begin(), itemOcc.end(), descPair);
	unsigned nbBrik = (itemOcc.size()/5);
	if (nbBrik == 0) nbBrik = 1;
	int brik[nbBrik] = { };
	unsigned nbCiment = itemOcc.size() - nbBrik;
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
	for (unsigned int i = 0; i < pop.size(); ++i) {
	    pop[i]->resize(item);
	    for(unsigned int j = 0; j < item; ++j) (*pop[i])[j] = '0';
	    int selectedBrik = rand() % nbBrik;
	    int selectedCiment = rand() % nbCiment;
	  
	    for (int j = 0; j < selectedBrik; ++j){
		int indBrik = rand() % (nbBrik -1);
		(*pop[i])[brik[indBrik]] = '1';
	    }
	   
	    for (int j = 0; j < selectedCiment; ++j){
		int indCiment = rand() % (nbCiment-1);
		(*pop[i])[ciment[indCiment]] = '1';
	    }
	}
    }
}


void FreqPop::executeO(std::vector< Individual< char >* >& pop)
{
  if (pop.empty()) throw string("Erreur, la population à initialiser est vide ! (freqPop)");
  
  else if (_dataO == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé ! (freqPop)");
  
  else if (_dataO->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide ! (freqPop)");
  
  else {
      unsigned line = _dataO->getNbLine();
      unsigned item = _dataO->getNbCol();
    
      vector<pair<int, float>> itemOcc;
      
      for (unsigned int i = 0; i < item; ++i){
	  pair<int,float> tmp(i,0);
	  
	  for(unsigned int j = 0; j < line; ++j){
	      tmp.second += toDigit( _dataO->getDataAt(j,i));
	  }
	  if( tmp.second >= _seuilF*line)
	      itemOcc.push_back(tmp);
      }
    
      sort(itemOcc.begin(), itemOcc.end(), descPair);
      unsigned nbBrik = (itemOcc.size() / 5);
      if (nbBrik == 0) nbBrik = 1;
      int brik[nbBrik] = { };
      unsigned nbCiment = itemOcc.size() - nbBrik;
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
      for (unsigned int i = 0; i < pop.size(); ++i) {
	pop[i]->resize(item);
	for(unsigned int j = 0; j < item; ++j) (*pop[i])[j] = '0';
	int selectedBrik = rand() % nbBrik;
	int selectedCiment = rand() % nbCiment;
	for(int j = 0; j < selectedBrik; ++j){
	    int indBrik = rand() % (nbBrik -1);
	    (*pop[i])[brik[indBrik]] = '1';
	}
	for(int j = 0; j < selectedCiment; ++j){
	    int indCiment = rand() % (nbCiment-1);
	    (*pop[i])[ciment[indCiment]] = '1';
	}
      }
  }
}
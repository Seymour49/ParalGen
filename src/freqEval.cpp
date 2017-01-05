#include "../include/freqEval.h"

using namespace std;

FreqEval::FreqEval()
{}


FreqEval::FreqEval(DataSet<char> * const data): _data1(data)
{}


FreqEval::FreqEval(DataSetO<char> * const data):_data2(data)
{}


FreqEval::FreqEval(DataSet<char>* const data1, DataSetO<char>* const data2): _data1(data1), _data2(data2)
{}


FreqEval::FreqEval(const FreqEval& f)
{
  *_data1 = *(f.getData());
  *_data2 = *(f.getDataO());
}



void FreqEval::execute(Individual< char >& ind)
{
    if (_data1 == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé (freqEval)");
    else if (_data1->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide (freqEval)");
    else if( ind.size() != _data1->getNbCol() ) throw string("Erreur, le nombre d'item de l'individu est différent du nombre d'item du jeu de donnée (freqEval)");
    else {
      float result = 0.0;
      bool newO;
      bool empty = true;
      unsigned nbCol = _data1->getNbCol();
      unsigned nbRow = _data1->getNbLine();
      
      for (unsigned int i = 0; i < nbRow; ++i) {
	newO = true;	    
	for (unsigned int j = 0; ((j < nbCol) && newO); ++j) {
	  if (ind[j] != '0') {
	    if (empty) empty = false;
	    if (_data1->getDataAt(i,j) == '0') newO = false;
	  }
	}
	if(newO) ++result;
      }
      if (empty) 
	result = 0.0;
      else 
	result = result / nbRow;
      ind.setScore(result);
    }
}


void FreqEval::executeO(Individual< char >& ind)
{
    if (_data2 == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé (freqEval)");
    else if (_data2->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide (freqEval)");
    else if( ind.size() != _data2->getNbCol() ) throw string("Erreur, le nombre d'item de l'individu est différent du nombre d'item du jeu de donnée (freqEval)");
    else {
	float result = 0.0;
	bool newO;
	bool empty = true;
	unsigned nbCol = _data2->getNbCol();
	unsigned nbRow = _data2->getNbLine();

	
	for (unsigned int i = 0; i < nbRow; ++i){
	  
	    newO = true;	    
	    for(unsigned int j = 0; ((j<nbCol)&&newO); ++j) {
	      
	      if (ind[j] != '0') {
		if (empty) empty = false;
		if (_data2->getDataAt(i, j) == '0') newO = false;
	      }
	    }
	    if (newO) ++result;
	}
	if (empty) 
	  result = 0.0;
	else 
	  result = result / nbRow;
	ind.setScore(result);
    }
}
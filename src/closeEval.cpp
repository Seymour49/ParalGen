#include "../include/closeEval.h"

#define toDigit(c) (c-'0')

using namespace std;


CloseEval::CloseEval(float freq):_freq(freq)
{}

CloseEval::CloseEval(float freq, DataSet<char> * const data): _freq(freq), _data1(data)
{}


CloseEval::CloseEval(float freq, DataSetO<char> * const data):_freq(freq), _data2(data)
{}


CloseEval::CloseEval(float freq, DataSet<char>* const data1, DataSetO<char>* const data2):_freq(freq), _data1(data1), _data2(data2)
{}


CloseEval::CloseEval(const CloseEval& c): _freq(c.getFrequence())
{
  *_data1 = *(c.getData());
  *_data2 = *(c.getDataO());
}


void CloseEval::execute(Individual< char >& ind)
{
  if (_data1 == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé");
  else if (_data1->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide");
  else if( ind.size() != _data1->getNbCol() ) throw string("Erreur, le nombre d'item de l'individu est différent du nombre d'item du jeu de donnée");
  else if (_freq < 0 || _freq > 1) throw string("Erreur, le seuil de fréquence doit être entre 0 et 1");
  else {

    float result = 0.0;
    bool newO;
    unsigned nbCol = _data1->getNbCol();
    unsigned nbRow = _data1->getNbLine();
    
    for (unsigned int i = 0; i < nbRow; ++i){
      
	newO = true;	    
	for (unsigned int j = 0; ((j < nbCol)&&newO); ++j) {
	    if( ((ind[j] == '1') && (_data1->getDataAt(i,j) == '0')) ){
		newO = false;		    
	    }
	}
	if(newO) ++result;
    }
    result = result / nbRow;

    // Traiter la fermeture de l'individu
    
    /* Calcul des items fréquents pour ne tester que les sur-ensembles
      * potentiellement fréquents
      */
    vector<pair<int,float>> itemFreq;
    for (unsigned int i = 0; i < nbCol; ++i) {
      pair<int, float> tmp(i, 0.0);
      
      for (unsigned int j = 0; j < nbRow; ++j) {
	    tmp.second += toDigit( _data1->getDataAt(j,i) );
      }
      
      tmp.second = tmp.second /nbRow;
      if( tmp.second > _freq ){
	  itemFreq.push_back(tmp);
      }
    }
      
    bool isClosed = true;
    float res = 0.0;
    // Tant qu'on a pas détecté de surensemble fréquent on continue
    for (unsigned int i = 0; (i < itemFreq.size()&&isClosed); ++i) {
      
      // Si itemFreq[i] == 0 dans individu, on fixe à 1 dans un clone
      // et on évalue la fréquence
      if( ind[itemFreq[i].first] == '0') {

	vector<char> v = ind.get();

	for (unsigned int j = 0; j < v.size(); ++j) {
	  if (v[j] == '0') v[j] = '1';
	  else v[j] = '0';
	}

	bool occ;
	for (unsigned int j = 0; j < nbRow; ++j) {
  
	  occ = true;	    
	  for (unsigned int k = 0; ((k < nbCol)&&occ); ++k) {
	      if( ((v[k] == '1') && (_data1->getDataAt(j, k) == '0')) ) {
		  occ = false;		    
	      }
	  }
	  if (occ) ++res;
	}
	res = res / nbRow;
	
	// si res > seuil, nonClos, sinon on augmente i
	if ( res > _freq ){
	    isClosed = false;
	}
      }
      
    }

    
    if ( isClosed)
      ind.setScore(result+1.0);
    else
      ind.setScore(result);
  }
}



void CloseEval::executeO(Individual< char >& ind)
{
  if (_data2 == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé");
  else if (_data2->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide");
  else if( ind.size() != _data2->getNbCol() ) throw string("Erreur, le nombre d'item de l'individu est différent du nombre d'item du jeu de donnée");
  else if (_freq < 0 || _freq > 1) throw string("Erreur, le seuil de fréquence doit être entre 0 et 1");
  else {
    float result = 0.0;
    bool newO;
    unsigned nbCol = _data2->getNbCol();
    unsigned nbRow = _data2->getNbLine();
    
    for (unsigned int i = 0; i < nbRow; ++i){
      
	newO = true;	    
	for (unsigned int j = 0; ((j < nbCol)&&newO); ++j) {
	    if( ((ind[j] == '1') && (_data2->getDataAt(i,j) == '0')) ){
		newO = false;		    
	    }
	}
	if(newO) ++result;
    }
    result = result / nbRow;
    
    // Traiter la fermeture de l'individu
    
    /* Calcul des items fréquents pour ne tester que les sur-ensembles
      * potentiellement fréquents
      */
    vector<pair<int,float>> itemFreq;
    for (unsigned int i = 0; i < nbCol; ++i) {
      pair<int, float> tmp(i, 0.0);
      
      for (unsigned int j = 0; j < nbRow; ++j) {
	    tmp.second += toDigit( _data2->getDataAt(j,i) );
      }
      
      tmp.second = tmp.second /nbRow;
      
      if( tmp.second > _freq ){
	  itemFreq.push_back(tmp);
      }
    }
      
      
    bool isClosed = true;
    float res = 0.0;
    // Tant qu'on a pas détecté de surensemble fréquent on continue
    for (unsigned int i = 0; (i < itemFreq.size()&&isClosed); ++i) {
      
      // Si itemFreq[i] == 0 dans individu, on fixe à 1 dans un clone
      // et on évalue la fréquence
      if( ind[itemFreq[i].first] == '0') {
	
	vector<char> v = ind.get();
	for (unsigned int j = 0; j < v.size(); ++j) {
	  if (v[j] == '0') v[j] = '1';
	  else v[j] = '0';
	}
	
	bool occ;
	for (unsigned int j = 0; j < nbRow; ++j) {
  
	  occ = true;	    
	  for (unsigned int k = 0; ((k<nbCol)&&occ); ++k) {
	      if( ((v[k] == '1') && (_data2->getDataAt(j, k) == '0')) ) {
		  occ = false;		    
	      }
	  }
	  if (occ) ++res;
	}
	res = res / nbRow;
	
	// si res > seuil, nonClos, sinon on augmente i
	if ( res > _freq ){
	    isClosed = false;
	}
      }
      
    }
    
    if ( isClosed)
      ind.setScore(result+1.0);
    else
      ind.setScore(result);
  }
}
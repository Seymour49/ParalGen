#include "../include/closeEval.h"
#include <algorithm>
#include <utility>

#define toDigit(c) (c-'0')

using namespace std;


CloseEval::CloseEval(float freq):_freq(freq)
{
}


CloseEval::~CloseEval()
{
}


void CloseEval::execute(ItemSet* ind, DataSet* data)
{
}


void CloseEval::execute(ItemSetC* ind, DataSetC* data)
{
      if( ind->getSize() != data->getNbCol() ){
	  cerr << "Erreur, l'individu ne matche pas les données" << endl;
	  exit(EXIT_FAILURE);      
      }
      else{
	  float result = 0.0;
	  bool newO;
	  unsigned nbCol = data->getNbCol();
	  unsigned nbRow = data->getNbLine();
	  
	  for(unsigned i=0; i < nbRow; ++i){
	    
	      newO = true;	    
	      for(unsigned j=0; ((j<nbCol)&&newO); ++j) {
		
		  if( ((ind->getBitsetAt(j) == '1') && (data->getDataAt(i,j) == '0')) ){
		      newO = false;		    
		  }
	      }
	      if(newO) ++result;
	  }
	  result = result / nbRow;
	  
	  // Traiter la fermeture de l'ItemSetC
	  
	  /* Calcul des items fréquents pour ne tester que les sur-ensembles
	   * potentiellement fréquents
	   */
	  vector<pair<int,float>*> itemFreq;
	  for(unsigned i=0; i < nbCol; ++i){
	      pair<int, float>* tmp = new pair<int,float>(i,0);
	      
	      for(unsigned j=0; j < nbRow; ++j){
		    tmp->second += toDigit( data->getDataAt(j,i) );
	      }
	      
	      tmp->second = tmp->second /nbRow;
	      
	      if( tmp->second > _freq ){
		  itemFreq.push_back(tmp);
	      }
	      else{
		  delete tmp;
	      }
	  }
	   
	   
	  bool isClosed = true;
	  float res = 0.0;
	  // Tant qu'on a pas détecté de surensemble fréquent on continue
	  for(unsigned i=0; (i<itemFreq.size()&&isClosed); ++i){
	      
	      // Si itemFreq[i] == 0 dans individu, on fixe à 1 dans un clone
	      // et on évalue la fréquence
	      if( ind->getBitsetAt(itemFreq[i]->first) == '0'){
		   
		  // Clone de l'individu
		  ItemSetC* tmp = new ItemSetC(*ind);
		  // Flipper le bit d'indice itemFreq[i]->first
		  tmp->flipBit((unsigned)itemFreq[i]->first);
		  
		  bool occ;
		  for(unsigned i=0; i < nbRow; ++i){
	    
		      occ = true;	    
		      for(unsigned j=0; ((j<nbCol)&&occ); ++j) {
		
			  if( ((tmp->getBitsetAt(j) == '1') && (data->getDataAt(i,j) == '0')) ){
			      occ = false;		    
			  }
		      }
		      if(occ) ++res;
		  }
		  res = res / nbRow;
		  
		  // si res > seuil, nonClos, sinon on augmente i
		  if( res > _freq ){
		      isClosed = false;
		  }
		  delete tmp;
	      }
	    
	  }
	  
	  for(unsigned i=0; i < itemFreq.size(); ++i){
	      delete itemFreq[i];
	  }
	  
	  cout << "frequence : " << result << "; clos : " << isClosed << endl;
	  if( isClosed)
	    ind->setScore(result+1.0);
	  else
	     ind->setScore(result);
      }
}

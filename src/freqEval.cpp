#include "../include/freqEval.h"

using namespace std;

FreqEval::FreqEval()
{
}


FreqEval::~FreqEval()
{
}


void FreqEval::execute(ItemSet* ind, DataSet* data)
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
		
		  if( ((ind->getBitset()[j] == '1') && (data->getDataAt(i,j) == '0')) ){
		      newO = false;		    
		  }
	      }
	      if(newO) ++result;
	  }
	  result = result / nbRow;

	  ind->setScore(result);
    }
    
}


void FreqEval::execute(ItemSetC* ind, DataSetC* data)
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
	  
	  ind->setScore(result);
	
      }
}

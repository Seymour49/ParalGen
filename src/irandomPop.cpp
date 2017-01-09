#include "../include/irandomPop.h"

#define toDigit(c) (c-'0')

using namespace std;

IRandomPop::IRandomPop(DataSet< char >*const data):_data(data), _dataO(NULL)
{}


IRandomPop::IRandomPop(DataSetO< char >*const data):_data(NULL),_dataO(data)
{}


IRandomPop::IRandomPop(DataSet< char >*const data, DataSetO< char >*const dataO):
_data(data),_dataO(dataO)
{}

IRandomPop::IRandomPop(const IRandomPop& irp)
{}


void IRandomPop::execute(std::vector< Individual< char >* >& pop)
{
    if (pop.empty()) throw string("Erreur, la population à initialiser est vide ! (irandomPop)");
  
    else if (_dataO == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé ! (irandomPop)");
  
    else if (_dataO->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide ! (irandomPop)");
  
    else {
	unsigned int line = _data->getNbLine();
	unsigned int item = _data->getNbCol();
	
	for(unsigned i=0; i < pop.size(); ++i){
	    int tr = rand() % line;
	    
	    pop[i]->resize(item);
	    for(unsigned j=0; j < item; ++j)
		(*pop[i])[j] = _data->getDataAt(tr,j);
	  
	}      
    }
}


void IRandomPop::executeO(std::vector< Individual< char >* >& pop)
{
    if (pop.empty()) throw string("Erreur, la population à initialiser est vide ! (irandomPop)");
  
    else if (_dataO == NULL) throw string("Erreur, le jeu de donnée n'a pas été initialisé ! (irandomPop)");
  
    else if (_dataO->getNbLine() == 0) throw string("Erreur, le jeu de donnée est vide ! (irandomPop)");
  
    else {
	unsigned int line = _dataO->getNbLine();
	unsigned int item = _dataO->getNbCol();
	
	for(unsigned i=0; i < pop.size(); ++i){
	    int tr = rand() % line;
	    
	    pop[i]->resize(item);
	    for(unsigned j=0; j < item; ++j)
		(*pop[i])[j] = _dataO->getDataAt(tr,j);
	  
	}      
    }
}


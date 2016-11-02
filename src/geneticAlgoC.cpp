#include "../include/geneticAlgoC.h"
#include <algorithm>
#include <array>
#include <utility>

#define toDigit(c) (c-'0')

using namespace std;


GeneticAlgoC::GeneticAlgoC():_nbIteration(10000),_taillePop(100), _seuilFrequence(0.6)
{
   _population = new vector<ItemSetC*>();
}


GeneticAlgoC::GeneticAlgoC(unsigned int it, unsigned int pop, float seuilfrequence, Mutator* mut, Cross* cross, Evaluate* eval, InitPop* init):
  _nbIteration(it), _taillePop(pop), _seuilFrequence(seuilfrequence), _mutator(mut), _cross(cross), _eval(eval), _init(init)
{
  _population = new vector<ItemSetC*>();
}


GeneticAlgoC::~GeneticAlgoC()
{
  for(unsigned int i=0; i < _population->size(); ++i){
      delete _population->at(i);
  }
  _population->clear();
  _population->shrink_to_fit();
  delete _population;
}


void GeneticAlgoC::setData(DataSetC* input){
    _data = input;
}

void GeneticAlgoC::EvalPop()
{
  for(unsigned i=0; i < _population->size(); ++i)
    _eval->execute(_population->at(i), _data);
}


void GeneticAlgoC::initPop()
{
    if(_init == NULL){
	cerr << "Erreur, initPop null" << endl;
	exit(EXIT_FAILURE);
    }
    else{
	_init->execute(_population,_taillePop);
    }
}


ItemSetC* GeneticAlgoC::doMutation(unsigned ind)
{
    if( _population->size() == 0 ){
	cerr << "Erreur population vide" << endl;
	exit(EXIT_FAILURE);
    }
    else if( _mutator == NULL){
	cerr << "Méthode de mutation null" << endl;
	exit(EXIT_FAILURE);
    }
    else if( ind > (_population->size()-1) ){
	cerr << "Erreur sur indice" << endl;
	exit(EXIT_FAILURE); 
    }
    else{
	ItemSetC* child = new ItemSetC(*_population->at(ind));
	child = _mutator->execute(child);
	return child;
    }
}


void GeneticAlgoC::incAgePop()
{
    for (unsigned int i = 0; i < _population->size(); ++i) {
      _population->at(i)->incAge();
    }
}


bool GeneticAlgoC::isPartOfPop(ItemSetC* ind)
{
    bool result = false;
    bool simil;
    unsigned i = 0;
    while( (result != true) && ( i < _population->size()) ){
	simil = true;
	
	for(unsigned j=0; (j<_data->getNbCol() && simil);++j){
	    if(_population->at(i)->getBitsetAt(j) != ind->getBitsetAt(j) ){
		simil = false;
	    }
	}
	
	if(simil == true){
	    result = true;
	}
	else{
	    ++i;
	}
    }
    
    return result;
}


bool AgeDesc(pair<unsigned,unsigned>* p1, pair<unsigned,unsigned>* p2){
    return (p1->second > p2->second);
}


bool ScoreAsc(pair<unsigned,float>* p1, pair<unsigned,float>* p2){
    return (p1->second < p2->second);
}


bool ScoreIndDesc(ItemSetC* i1, ItemSetC* i2){ 
    return (i1->getScore() > i2->getScore());
}


void GeneticAlgoC::run()
{
    // Initialisation de la population
    initPop();
    
    // Evaluation de la population
    EvalPop();
    
    int alea;
    int selectedItem;
    // Début de la boucle centrale
    for(unsigned i=0; i < _nbIteration; ++i){
	
	// Incrémentation de l'âge de la population
	incAgePop();
	
	alea = rand()%100;
	ItemSetC* child;
	// 1% de chance qu'un individu aléatoire mute
	if( alea == 0){
	    selectedItem = rand()% _population->size();
	    child = doMutation(selectedItem);
	}
	// Sinon, on sélectionne deux groupes de 3
	else{
	    unsigned indice[_population->size()];
	    for(unsigned i=0; i < _population->size(); ++i) indice[i] = i;
	    
	    random_shuffle(&indice[0], &indice[_population->size()-1]);
	    
	    // Sélection de 6 valeurs différentes au sein de 2 groupes de 3
	    int limite = _population->size();
	    array<int,3> p1;
	    array<int,3> p2;
	    int select;
	    for(unsigned j=0; j < 3; ++j){
		select = rand()% limite;
		p1[j] = indice[select];
		indice[select] = indice[limite-1];
		indice[limite-1] = p1[j];
		--limite;
	    }
	    
	    for(unsigned j=0; j < 3; ++j){
		select = rand()% limite;
		p2[j] = indice[select];
		indice[select] = indice[limite-1];
		indice[limite-1] = p2[j];
		--limite;
	    }
	    
	    // Récupération du meilleur individu de chaque groupe.
	    unsigned b1 = p1[0];
	    unsigned b2 = p2[0];
	    
	    for(unsigned i = 1; i < 3; ++i){
		if( _population->at(p1[i])->getScore() > _population->at(b1)->getScore() ){
		    b1 = p1[i];
		}
		if( _population->at(p2[i])->getScore() > _population->at(b2)->getScore() ){
		    b2 = p2[i];
		}
	    }
	    
	    child = _cross->execute(_population->at(b1),_population->at(b2));
	    
	    select = rand()%1000;
	    if( select < 500)
		child = _mutator->execute(child);
	}
	
	// Vérifier si child n'appartient pas déjà à la population
	if( !isPartOfPop(child) ){
	    _eval->execute(child,_data);
	    
	    // Sélection du moins bon parmi les 80% les plus vieux
	    vector<pair<unsigned,unsigned> *> ageBoard;
	    for(unsigned i=0; i < _population->size(); ++i){
		pair<unsigned,unsigned>* tmp = new pair<unsigned,unsigned>(i,_population->at(i)->getAge());
		ageBoard.push_back(tmp);
	    }
	    
	    sort(ageBoard.begin(), ageBoard.end(), AgeDesc);
	    
	    vector< pair<unsigned, float>*> scoreBoard;
	    unsigned limit = 0.8* _population->size();
	    for(unsigned i=0; i < limit; ++i){
		pair<unsigned, float>*tmp = new pair<unsigned, float>(
		  ageBoard.at(i)->first, _population->at(ageBoard.at(i)->first)->getScore() );
	      
		scoreBoard.push_back(tmp);
	    }
	    
	    sort(scoreBoard.begin(), scoreBoard.end(), ScoreAsc);    
	    
	    // Suppression de l'individu le moins bon parmi les 80%
	    delete _population->at(scoreBoard[0]->first);
	    _population->erase(_population->begin() + scoreBoard[0]->first);
	    
	    // Ajout du nouvel individu
	    _population->push_back(child);
	    
	    // Libération de la mémoire temporaire allouée
	    for(unsigned i=0; i < ageBoard.size(); ++i)
		delete ageBoard[i];
	    for(unsigned i=0; i < scoreBoard.size(); ++i)
		delete scoreBoard[i];
	}
    }
    
    sort(_population->begin(), _population->end(), ScoreIndDesc);
  
}


void GeneticAlgoC::displayPopulationAt(unsigned int ind)
{
    if( _population->size() == 0 ){
	cerr << "Erreur population vide" << endl;
	exit(EXIT_FAILURE);
    }
    else if( ind > (_population->size()-1) ){
	cerr << "Erreur sur indice" << endl;
	exit(EXIT_FAILURE); 
    }
    else{
	cout << *_population->at(ind);
    }
}

void GeneticAlgoC::displayPopulation() {
    cout << "La population actuelle est la suivante : " << endl;
    
    for(unsigned i=0; i<_population->size(); ++i){
	cout << *_population->at(i);
    }
}

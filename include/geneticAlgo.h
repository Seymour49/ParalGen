#ifndef GENETICALGO_H
#define GENETICALGO_H

#include "individual.h"
#include "itemSet.h"
#include "itemSetO.h"
#include "dataSet.h"
#include "dataSetO.h"
#include "mutator.h"
#include "cross.h"
#include "indelPolicy.h"
#include "selectPolicy.h"
#include "evaluate.h"
#include "initPop.h"

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h> 
#include <fstream>
#include <algorithm>


/**
 * Cette classe implémente un algorithme génétique
 * pour la recherche d'itemset fréquent. Elle gère une
 * population constante d'individus qu'elle croise et
 * fait muter pendant un nombre d'itérations passé en 
 * paramètre.
 */

template <typename T>
class GeneticAlgo {
  
private:
  
    Mutator<T> * _mutator;
    Cross<T> * _cross;
    Evaluate<T> * _eval;
    InitPop<T> * _initPop;
    SelectPolicy<T> * _select;
    IndelPolicy<T> * _insert;
    
    /* Modèle en îles */
    float* _tabMig;			// Tableau de _nbIsland float représentant les probabilité de migration
    SelectPolicy<T>* _selectMig;
    IndelPolicy<T>* _indelMig;
    
    /* Fin IM */
    unsigned int _tPop;
    unsigned int _nbIteration;
    float _probaM;
    float _probaC;
    std::vector<Individual<T>*> _population;
        
    unsigned int _typeFlag;
    
    /* Reprise du modèle en île */
    
    
    unsigned int _nbIsland;		// Nombre d'iles 
    unsigned int _idIsland;		// Position de l'ile sur la map
    std::string _unitaryName;		// Nom générique d'une ile (ex "Node") -> Utile pour le filesystem
    unsigned _stepM;			// Nombre de générations entre deux migrations
    
    unsigned _nbMigrants;
    
    
    /* Gestion des résultats */
    
    
public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur prenant un nombre d'itérations, une taille de population, 
  * un seuil de fréquence et un opérateur de mutation et de croisement
  * en paramètres.
  * @param ind : Type d'individu à manipuler
  * @param mut : opérateur de mutation
  * @param cross : opérateur de croisement
  * @param init : opérateur d'initialisation de la population
  * @param select : politique de sélection des individu pour le croisement
  * @param insert : politique de suppression d'un individu en faveur d'un autre individu résultant d'un croisement
  * @param taillePop : Taille de la population à manipuler
  * @param it : nombre d'itérations de l'algorithme
  * @param seuilFrequence : seuil minimum de fréquence
  * @param probaM : probabilité de mutation
  * @param probaC : probabilité de croisement
  * @author Ugo Rayer, Johan Defaye
  */
  GeneticAlgo(Individual<T> * const ind, Mutator<T>* const mut, Cross<T> * const cross, 
	      Evaluate<T> * const eval, InitPop<T> * const init, SelectPolicy<T> * const select,
	      IndelPolicy<T> * const insert, float* tM,SelectPolicy<T> * const migS, IndelPolicy<T>* const migID,
	      unsigned int taillePop = 100, unsigned int it = 10000,
	      float pm = 0.005, float pc = 0.8, unsigned int nbI = 1, unsigned int id = 1,
	      std::string name = "Node", unsigned int step = 10, unsigned int nbMig = 2)
  :_mutator(mut), _cross(cross), _eval(eval), _initPop(init), _select(select), _insert(insert),_tabMig(tM),
   _selectMig(migS), _indelMig(migID),_tPop(taillePop), _nbIteration(it),_probaM(pm), _probaC(pc),
  _population(taillePop),_nbIsland(nbI), _idIsland(id), _unitaryName(name), _stepM(step),_nbMigrants(nbMig)
  {
    if (ind != NULL) {
      ItemSet<T> * itemset = dynamic_cast<ItemSet<T> *>(ind);
      ItemSetO<T> * itemsetO = dynamic_cast<ItemSetO<T> *>(ind);
      
      if (itemset != NULL) {
	for (unsigned int i = 0; i < taillePop; ++i) {
	  _population[i] = new ItemSet<T>;
	}
	_typeFlag = 0;
      }
      else if (itemsetO != NULL){
	for (unsigned int i = 0; i < taillePop; ++i) {
	  _population[i] = new ItemSetO<T>;
	}
	_typeFlag = 1;
      }
      
    }
  }
  
  /* * * * * * * * * 
   *   DESTRUCTOR  *
   * * * * * * * * */
  ~GeneticAlgo()
  {
    for (unsigned int i = 0; i < _population.size(); ++i) {
      delete _population[i];
    }
  }
  
  /* * * * * * * * * 
   *  ACCESSEURS   *
   * * * * * * * * */
  unsigned int getNbIteration() const { return _nbIteration; }
  
  unsigned int getTaillePop() const { return _population.size(); }
      
      
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  std::vector< std::string > explode(const std::string& str){
    std::istringstream split(str);
    std::vector<std::string > tokens;

    for(std::string each; std::getline(split, each, ' '); tokens.push_back( each.c_str()) );
    return tokens;
  }
  
  int processDir(){
      // Déterminer le nom du dossier
      std::string dirname= _unitaryName;
      dirname.append(std::to_string(_idIsland));

      // Ouverture du dossier
      DIR *dir = opendir(dirname.c_str());
      struct dirent *d;
      
      if( dir == NULL){ // Not a directory or doesn't exist
	std::cout << "Pas de dossier/ dossier vide" << std::endl;  
	return -1;
      }
      while( (d = readdir(dir)) != NULL) {
	  if( !strcmp(d->d_name, ".") || !strcmp(d->d_name, "..") )
	  {}
	  else{
	      std::cout << "processing file : " << d->d_name << std::endl;
	      std::string filepath = dirname+"/"+d->d_name;
	      
	      // Traitement du fichier courant
	      
	      std::ifstream f(filepath.c_str());
	      
	      if(!f) throw std::string("Erreur lors de l'ouverture du fichier " + filepath + "!");
	      else{
		  std::string line;
		  
		  while( std::getline(f,line)){		     
		      
		      if(!line.empty()) {
			  std::vector<std::string> tokens;
			  // extraction du bitset depuis le fichier
			  tokens = explode(line);
			  std::vector<T> bitset;
			  for(unsigned int i=0; i < tokens.size(); ++i)
			      bitset.push_back(*tokens[i].c_str()); // TODO typage de l'individu
			  
			  // DEBUG DISPLAY
			  std::cout << "Bitset :";
			  for(unsigned int i=0; i < bitset.size(); ++i)
			      std::cout <<" " <<bitset[i];
			  std::cout << std::endl;
			  // END DD
			  
			  // Création de l'individu
			  Individual<T>* newcomer = NULL;
			  if( _typeFlag == 0){
			      newcomer = new ItemSet<T>(bitset);
			  }
			  else {
			      newcomer = new ItemSetO<T>(bitset);
			  }
			   _population.push_back(newcomer);
		      }		      
		  }
		  f.close();
		  // Suppression du fichier après traitement
		  if( std::remove(filepath.c_str()) != 0)		      
			throw std::string("Suppression impossible");
		  
	      }	      
	  }
      }
	
      closedir(dir);
      
      return 0;
  }


/**
 * Méthode effectuant une mutation sur un individu de la population.
 * Prend en paramètre l'indice de l'individu dans la population.
 * Renvoie une erreur si l'indice n'est pas dans la population
 * @param int indice de l'individu à muter
 * @author Ugo Rayer
 */
  void doMutationFor(unsigned ind)
  {
    if (ind > (_population.size() - 1) || ind < 0) throw std::string("Erreur, indice de l'individu à muter hors de la population");
    else _mutator->execute(*_population[ind]);
  }

  
/**
 * Méthode effectuant un croisement sur deux individus de la population.
 * Prend en paramètre les deux indices des individus parents
 * Renvoie une erreur si les indices sont en dehors de la population.
 * @param indParent1 : indice du premier parent
 * @param indParent2 : indice du deuxième parent
 * @param ind  : enfant
 * @author Ugo Rayer
 */
  void doCrossFor(unsigned int indParent1, unsigned int indParent2, Individual<T> & ind)
  {
    if( (indParent1 < 0) || (indParent2 < 0) || (indParent1 > (_population.size() - 1)) || (indParent2 > (_population.size() - 1)) )
      throw std::string("Erreur, indices des parents hors de la population");
    else 
      _cross->execute(*(_population[indParent1]), *(_population[indParent2]), ind);
  }

  
/**
  * Méthode permettant d'incrémenter l'âge de toute la population
  * @author Johan Defaye
  */
  void incAgePop()
  {
    for (unsigned int i = 0; i < _population.size(); ++i) {
      _population[i]->incAge();
    }
  }
  
  
  /**
   * Intialise la population en appelant la méthode d'exécution de l'attribut initPop
   * @author Johan Defaye
   */
  void populate()
  {
    try{
      _initPop->executeO(_population);
      
    }
    catch(std::string E1){
	try{
	  _initPop->execute(_population);  
	}
	catch(std::string Excep){
	    std::cerr << E1 << " then " << Excep << std::endl;
	}
    }
  }
  
  /**
   * Évalue toute la population en mettant à jour les score de chaque individu
   * @author Johan Defaye
   */
  void evalPop()
  {
    
    for (unsigned int i = 0; i < _population.size(); ++i) {
      try {
	  _eval->executeO(*(_population[i]));
      }
      catch(std::string E1){
	  try{
	      _eval->execute(*(_population[i]));
	  }
	  catch(std::string Excep){
	      std::cerr << E1 << " then " << Excep << std::endl;
	  }
      }
    }
  }
  
  
  /**
   * Ecrit dans un fichier dont le nom est passé en paramètre le score moyen des n meilleurs individus de la population
   * @param fileName : Nom du fichier ou les résultats sont écrits
   * @param n: nombre d'indivus à faire la moyenne
   * @param generation: numéro de la génération
   * @author Johan Defaye
   */
  void writeBestScoreAverage(const std::string & fileName, unsigned int n, unsigned int generation) const 
  {
    if ((n > _population.size()) || (n == 0)) throw std::string("Erreur, nombre d'individu incorrecte");
    else {
      std::ofstream file(fileName, std::ios::out | std::ios::app);
      if (file) {
	std::vector<float> bestScore(n);
	for (unsigned int i = 0; i < n; ++i) bestScore[i] = _population[i]->getScore();
	std::sort(bestScore.begin(), bestScore.end(), [](float a, float b) {return (a > b);});
	for (unsigned int i = n; i < _population.size(); ++i) {
	  float newScore = _population[i]->getScore();
	  unsigned int j = n - 1;
	  if (newScore > bestScore[0]) j = 0;
	  else {
	    while (newScore > bestScore[j]) {
	      j--;
	    }
	    j++;
	  }
	  if ((j >= 0) && (j < n)) {
	   
	    bestScore.insert(bestScore.begin()+j, newScore);
	    bestScore.pop_back();
	    
	  }
	}
	float average = 0.0;
	for (unsigned int i = 0; i < n; ++i) average += bestScore[i];
	average = average/n;
	file << generation << " " << average << std::endl;
      }
      else throw std::string("Erreur, impossible d'ouvrir le fichier " + fileName);
    }
  }
  
  
/**
 * Méthode principale de la classe. Lance l'algorithme génétique avec un nombre d'itération 
 * et une taille de population définit dans le constructeur.
 * @author Johan Defaye, Ugo Rayer
 */
  void run()
  {
      float _results[_nbIteration];
      try{
	
	  /* Gestion résultats */
	  for(unsigned int i=0; i < _nbIteration; ++i)
	      _results[i] = 0;
	
	  // Initialisation de la population
	  populate();
	  
	  // Evaluation de la population
	  evalPop();
	  char tmp = _idIsland + '0';
	  int al = rand() % 3333 + 25;
	  int al2 = rand() % 245547+ 5788;
	  
	  std::string resultFileName = "results/"+_unitaryName+tmp+"_"+std::to_string(al*al2)+".txt";
	  
	  //writeBestScoreAverage(resultFileName, 10, 0);
	  // Début de la boucle centrale
	  unsigned i=0;
	      int pass = 0;
	  while( i < _nbIteration ){
	      
	
	      // Gestion du modèle en îles
	      if( _nbIsland > 1 && (i%_stepM) == 0 && i > 0){
		  std::cout << "test passage " << pass << ". iteration : " << i << ". nbMigrants : " << _nbMigrants << std::endl;
		  ++pass;
		  // on effectue _nbMigrants selections
		  std::vector<std::vector<int>> migMat; 
		  for(unsigned i = 0; i < _nbIsland; ++i){
		      std::vector<int> migIle;
		      migMat.push_back(migIle);
		  }
		  
		  for(unsigned i = 0; i < _nbMigrants; ++i){
		      std::pair<int,int> selected( _selectMig->execute(_population));
		      // Sélection de l'île
		      int alea = rand() % 1000;
		      int tmp = _tabMig[0] * 1000;
		      
		      int j = 0;
		      while( tmp <= alea ){
			  ++j;
			  tmp += (_tabMig[j]*1000);			  
		      }
		      
		      // Indice de l'île dans la variable j, individu dans selected.first
		      std::cout << "Individu à migrer " << selected.first << " sur l'île " << j+1 << std::endl ;
		      migMat[j].push_back(selected.first);
		      
		      // TODO RETIRER l'INDIVIDU DE LA POPULATION
		      _population.erase(_population.begin()+selected.first);
		  }
		
		  for( unsigned k=0; k < migMat.size(); ++k){
		    
		      if(migMat[k].size() > 0 && (k+1) != _idIsland ){
			  // filename 
			  std::string filepath = _unitaryName;
			  filepath.append(std::to_string(k+1));
			  filepath.append("/");
			  
			  for(unsigned l=0; l < migMat[k].size(); ++l){
			      std::cout <<" " << migMat[k][l] ;
			  }
			  std::cout << std::endl;
			  
			  time_t timer = time(NULL);
			  int al1 = rand() % 1111 + 10000;
			  int al2 = rand() % 3333 + 2000;
			  int al3 = al1*al2;
			  timer -= al3;
			  
			  filepath.append("fromNode"+std::to_string(_idIsland)+"_");
			  filepath.append(std::to_string(timer));
			  std::cout << "migration sur l'ile " << k+1 << std::endl;
			  std::cout << "filename : " << filepath << std::endl;
			  
			  for(unsigned t=0; t < _population[0]->size(); ++t){
			    std::cout << " " << (*_population[migMat[k][0]])[t];
			  }
			  std::cout << std::endl;
			  
			  /*	TODO
			   * Reprendre ici, il reste à écrire les individus dans un stream
			   * puis le stream dans le fichier			   * 
			   */
			  std::ofstream outfile (filepath,std::ofstream::binary);
			  if(!outfile) throw std::string("Erreur lors de l'ouverture du fichier "+filepath);
			  else{
			      for(unsigned x=0; x < migMat[k].size() ; ++x){
				  
				  for(unsigned t=0; t < _population[0]->size(); ++t){
				      outfile << (*_population[migMat[k][x]])[t] << " ";
				  }
				  outfile << std::endl;
			      }
			  
			      outfile.close();
			  }
		      }
		      else if(migMat[k].size() == 0 && (k+1) != _idIsland){
			  std::cout << "Pas de migration sur ile " << (k+1) << std::endl;
			  
		      }
		      else if((k+1)==_idIsland){
			  std::cout << "Pas de mouvement, on reste sur l'ile "<<k+1 << std::endl;
			
		      }
			  
			
		      
		  }
		  
		  
		  // Traitement du dossier pour insertion
		  try{
		    processDir();
		  }
		  catch( std::string Excep){
		      std::cerr << Excep << std::endl;
		  }
	      }
	      
	      Individual<T>* os1 = NULL;
	      Individual<T>* os2 = NULL;
	      
	      Individual<T>* tmp1 = NULL;
	      Individual<T>* tmp2 = NULL;
	      
	      if( _typeFlag == 0){
		  os1 = new ItemSet<T>();
		  os2 = new ItemSet<T>();
		  tmp1 = new ItemSet<T>();
		  tmp2 = new ItemSet<T>();
	      }
	      else if(_typeFlag == 1){
		  os1 = new ItemSetO<T>();
		  os2 = new ItemSetO<T>();
		  tmp1 = new ItemSet<T>();
		  tmp2 = new ItemSet<T>();
	      }
	      
	      std::pair<int,int> parents(_select->execute(_population));
	      
	      int alea = rand()% 1000;
	      
	      if( alea < _probaC*1000){
		  _cross->execute(*_population[parents.first], *_population[parents.second], *tmp1);
		  _cross->execute(*_population[parents.second],*_population[parents.first], *tmp2);
	      }
	      else{
		  *tmp1 = *_population[parents.first]; 
		  *tmp2 = *_population[parents.first];
	      }
	      
	      alea = rand()%1000;
	      if(alea < _probaM*1000){
		  _mutator->execute(*tmp1);
		  *os1 = *tmp1;
		  
		  _mutator->execute(*tmp2);
		  *os2 = *tmp2;
	      }
	      else{
		  *os1 = *tmp1;
		  *os2 = *tmp2;
	      }
	      
	      delete tmp1;
	      delete tmp2;
	      
	      // Evaluation des offsprings
	      
	      try{
		  _eval->executeO(*os1);
		  _eval->executeO(*os2);
	      }
	      catch(std::string Ex1){
		try{
		    _eval->execute(*os1);
		    _eval->execute(*os2);
		}
		catch(std::string Ex2){
		    std::cerr << Ex1 << " then " << Ex2 << std::endl;
		}
	      }
	      
	      _insert->execute(*os1, _population);
	      _insert->execute(*os2, _population);
	      
	      
	      delete os1;
	      delete os2;
	      incAgePop();
	      ++i;
	      
	      // extraction du meilleur individus de la population
	      std::vector<float> bestScore(_population.size());
	      for (unsigned int i = 0; i < _population.size(); ++i) bestScore[i] = _population[i]->getScore();
	      std::sort(bestScore.begin(), bestScore.end(), [](float a, float b) {return (a > b);});
	      _results[i] = bestScore[0];
	  
	      
	     // writeBestScoreAverage(resultFileName, 10, i);
	  }
	  
	  exportResults(_results);
      }
      catch(std::string Exception){
	  std::cerr << Exception << std::endl;	
      }
      
    
  }
  
void exportResults(float* _results){
    
    std::string filename = _unitaryName;
    filename.append(std::to_string(_idIsland));
    filename.append("/result_");
    time_t timer = time(NULL);
    int al1 = rand() % 1111 + 10000;
    int al2 = rand() % 3333 + 2000;
    int al3 = al1*al2;
    timer -= al3;
    filename.append(std::to_string(timer));
    
    std::ofstream outfile(filename, std::ofstream::binary);
    if(!outfile) throw std::string("Erreur lors de l'ouverture du fichier "+filename);
    else{
	for(unsigned i=0; i < _nbIteration; ++i)
	    outfile << i << " " << _results[i] << std::endl;
      
	outfile.close();
    }
}  
  
/**
 * Méthode d'affichage de la population utile pendant le dev.
 * @author Ugo Rayer
 */
  void displayPopulation()
  {
    std::cout << "La population actuelle est la suivante : " << std::endl;
    for (unsigned int i = 0; i < _population.size(); ++i) {
      std::cout << *(_population[i]) << std::endl;
    }
  }



};

#endif
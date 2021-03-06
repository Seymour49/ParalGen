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
#include <fstream>
#include <algorithm>

#define verbose 0

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
    
    std::string _resultFileName;
    
    /* Fin IM */
    unsigned int _tPop;
    unsigned int _nbIteration;
    float _probaM;
    float _probaC;
    std::vector<Individual<T>*> _population;
        
    std::string _typeInd;
    
    /* Reprise du modèle en île */
    
    
    unsigned int _nbIsland;		// Nombre d'iles 
    unsigned int _idIsland;		// Position de l'ile sur la map
    std::string _unitaryName;		// Nom générique d'une ile (ex "Node") -> Utile pour le filesystem
    unsigned _stepM;			// Nombre de générations entre deux migrations
    
    unsigned _nbMigrants;
    
    float * _scores;			// Score d'individu    
    
public:
  
  
  /* * * * * * * * * 
   * CONSTRUCTORS  *
   * * * * * * * * */
  
/** 
  * Constructeur prenant un nombre d'itérations, une taille de population, 
  * un seuil de fréquence et un opérateur de mutation et de croisement
  * en paramètres.
  * @param typeInd : Type d'individu à manipuler
  * @param mut : opérateur de mutation
  * @param cross : opérateur de croisement
  * @param eval : fonction d'évaluation
  * @param init : opérateur d'initialisation de la population
  * @param select : politique de sélection des individu pour le croisement
  * @param insert : politique de suppression d'un individu en faveur d'un autre individu résultant d'un croisement
  * @param tM : tableau de probabilité de migration
  * @param migS : politique de sélection d'un individu
  * @param migID : politique de suppression d'un individu
  * @param resultFileName : nom du fichier ou écrire les résultats à la fin de l'algorithme
  * @param taillePop : Taille de la population à manipuler
  * @param it : nombre d'itérations de l'algorithme
  * @param pm : probabilité de mutation
  * @param pc : probabilité de croisement
  * @param nbI : nombre d'îles
  * @param id : identifiant de l'île
  * @param name : nom de l'île
  * @param step : nombre de générations avant migration d'individus vers une autre île
  * @param nbMig : nombre de migration
  * @author Ugo Rayer, Johan Defaye
  */
  GeneticAlgo(const std::string & typeInd, Mutator<T>* const mut, Cross<T> * const cross, 
	      Evaluate<T> * const eval, InitPop<T> * const init, SelectPolicy<T> * const select,
	      IndelPolicy<T> * const insert, float* tM, SelectPolicy<T> * const migS, IndelPolicy<T>* const migID, 
	      const std::string & resultFileName, unsigned int taillePop = 100, unsigned int it = 100,
	      float pm = 0.005, float pc = 0.8, unsigned int nbI = 1, unsigned int id = 1,
	      const std::string & name = "Node", unsigned int step = 10, unsigned int nbMig = 2)
  :_mutator(mut), _cross(cross), _eval(eval), _initPop(init), _select(select), _insert(insert),_tabMig(tM),
   _selectMig(migS), _indelMig(migID), _resultFileName(resultFileName), _tPop(taillePop), _nbIteration(it), _probaM(pm), _probaC(pc),
  _population(taillePop),_nbIsland(nbI), _idIsland(id), _unitaryName(name), _stepM(step),_nbMigrants(nbMig)
  {
    if (typeInd == "itemSet") {
      _typeInd = typeInd;
      for (unsigned int i = 0; i < taillePop; ++i) {
	  _population[i] = new ItemSet<T>;
      }
    }
    else {
      _typeInd = "itemSetO";
      for (unsigned int i = 0; i < taillePop; ++i) {
	  _population[i] = new ItemSetO<T>;
      }
    }
    _scores = new float[_nbIteration];
  }
  
  /* * * * * * * * * 
   *   DESTRUCTOR  *
   * * * * * * * * */
  ~GeneticAlgo()
  {
    for (unsigned int i = 0; i < _population.size(); ++i) {
      delete _population[i];
    }
    delete [] _scores;
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
	      if (verbose) std::cout << "processing file : " << d->d_name << std::endl;
	      std::string filepath = dirname+"/"+d->d_name;
	      
	      // Traitement du fichier courant
	      
	      std::ifstream f(filepath.c_str());
	      
	      if(!f) throw std::string("Erreur lors de l'ouverture du fichier " + filepath + "!"+" (geneticAlgo))");
	      else{
		std::cout << "Extraction des itemset du fichier " << filepath << std::endl;
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
			  if (verbose){
			    std::cout << "Bitset :";
			    for(unsigned int i=0; i < bitset.size(); ++i)
				std::cout <<" " <<bitset[i];
			    std::cout << std::endl;
			    // END DD
			  }
			  
			  // Création de l'individu
			  Individual<T>* newcomer = NULL;
			  if (_typeInd == "itemSet"){
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
			throw std::string("Suppression impossible (geneticAlgo))");
		  
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
    if (ind > (_population.size() - 1) || ind < 0) throw std::string("Erreur, indice de l'individu à muter hors de la population (geneticAlgo))");
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
      throw std::string("Erreur, indices des parents hors de la population (geneticAlgo)");
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
    if (_typeInd == "itemSet") {
      _initPop->execute(_population);
    }
    else _initPop->executeO(_population);
  }
  
  /**
   * Évalue toute la population en mettant à jour les score de chaque individu
   * @author Johan Defaye
   */
  void evalPop()
  {
    if (_typeInd == "itemSet") {
      for (unsigned int i = 0; i < _population.size(); ++i) {
	  _eval->execute(*(_population[i]));
      }
    }
    else {
      for (unsigned int i = 0; i < _population.size(); ++i) {
	  _eval->executeO(*(_population[i]));
      }
    }
  }
  
  
  /**
   * Ecrit dans un fichier dont le nom est passé en paramètre le score moyen des n meilleurs individus de la population pour chaque génération
   * @param fileName : Nom du fichier ou les résultats sont écrits
   * @author Johan Defaye
   */
  void writeBestScoreAverage(const std::string & fileName) const 
  {
    std::ofstream file(fileName, std::ios::out | std::ios::trunc);
    if (file) {
      for (unsigned int i = 0; i < _nbIteration; ++i) file << i + 1 << " " << _scores[i] << std::endl;
      file.close();
    }
    else throw std::string("Erreur, impossible d'ouvrir le fichier " + fileName+" (geneticAlgo)" );
  }
  
  /**
   * Renvoi la moyenne des score des n meilleurs individu de la population
   * @param n: nombre d'indivus à faire la moyenne
   * @author Johan Defaye
   */
  float getBestScoreAverage(unsigned int n) const 
  {
    float average = 0.0;
    if ((n > _population.size()) || (n == 0)) throw std::string("Erreur, nombre d'individu incorrect (geneticAlgo)");
    else {
      std::vector<float> bestScore(n);
      for (unsigned int i = 0; i < n; ++i) bestScore[i] = _population[i]->getScore();
      std::sort(bestScore.begin(), bestScore.end(), [](float a, float b) {return (a > b);});
      for (unsigned int i = n; i < _population.size(); ++i) {
	float newScore = _population[i]->getScore();
	unsigned int j = n - 1;
	if (newScore > bestScore[0]) j = 0;
	else {
	  while (newScore > bestScore[j]) j--;
	  j++;
	}
	if ((j >= 0) && (j < n)) {
	  bestScore.insert(bestScore.begin()+j, newScore);
	  bestScore.pop_back();
	}
      }
      
      for (unsigned int i = 0; i < n; ++i) average += bestScore[i];
      average = average/n;
    }
    return average;
  }
  
  
/**
 * Méthode principale de la classe. Lance l'algorithme génétique avec un nombre d'itération 
 * et une taille de population définit dans le constructeur.
 * @author Johan Defaye, Ugo Rayer
 */
  void run()
  {
      try{
	
	  // Initialisation de la population
	  populate();
	  // Evaluation de la population
	  evalPop();
	  char tmp = _idIsland + '0';
	  
	  std::string resultFileName = "results/"+_unitaryName+tmp+".gpd";
	  
	  // Début de la boucle centrale
	  
	  unsigned int i = 0;
	  int pass = 0;
	  _scores[0] = getBestScoreAverage(10);
	  while( i < _nbIteration ){
	    _scores[i] = getBestScoreAverage(1);
	      // Gestion du modèle en îles

	      if( (_nbIsland > 1) && ((i%_stepM) == 0) && (i > 0) && (_population.size() > (_tPop/2))){
		  if (verbose) std::cout << "test passage " << pass << ". iteration : " << i << ". nbMigrants : " << _nbMigrants << std::endl;
		  
		  // on effectue _nbMigrants selections
		  std::vector<std::vector<int>> migMat(_nbIsland);
		  std::cout << "Taille avant ecriture dans l'autre dossier pour l'itération " << i << " = " << _population.size() << std::endl;
		  for(unsigned k = 0; k < _nbMigrants; ++k){
		      std::pair<int,int> selected( _selectMig->execute(_population));
		      // Sélection de l'île
		      int alea = rand() % 1000;
		      int tmp = _tabMig[0] * 1000;
		      
		      unsigned int j = 0;
		      while( tmp <= alea ){
			  ++j;
			  tmp += (_tabMig[j]*1000);			  
		      }
		      
		      // Indice de l'île dans la variable j, individu dans selected.first

		      if (verbose) std::cout << "Individu à migrer " << selected.first << " sur l'île " << j+1 << std::endl ;
		      migMat[j].push_back(selected.first);
		      if ((j + 1) != _idIsland) _population.erase(_population.begin()+selected.first);
		  }
		
		  float scoretmp = 0;
		  int outsider = 0;
		  for (unsigned k = 0; k < migMat.size(); ++k){
		      // Les individus quittent l'île
		      if(migMat[k].size() > 0 && ((k+1) != _idIsland) ){

			  // filename 
			  std::string filepath = _unitaryName;
			  filepath.append(std::to_string(k+1));
			  filepath.append("/");
			  
			  if(verbose){
			      for(unsigned l=0; l < migMat[k].size(); ++l){
				  std::cout <<" " << migMat[k][l] ;
			      }
			      std::cout << std::endl;
			  }

			  time_t timer = time(NULL);
			  int al1 = rand() % 1111 + 10000;
			  int al2 = rand() % 3333 + 2000;
			  int al3 = al1*al2;
			  timer -= al3;
			  
			  filepath.append("fromNode"+std::to_string(_idIsland)+"_");
			  filepath.append(std::to_string(timer));

			  if (verbose) std::cout << "migration sur l'ile " << k+1 << std::endl;
			  if (verbose) std::cout << "filename : " << filepath << std::endl;
			  
			  std::ofstream outfile (filepath,std::ofstream::binary);
			  if(!outfile) throw std::string("Erreur lors de l'ouverture du fichier "+filepath);
			  else{
			      for(unsigned x=0; x < migMat[k].size() ; ++x){
				  
				  outsider += 1;
				  scoretmp += _population[migMat[k][x]]->getScore();
				  
				  for(unsigned int t = 0; t < _population[0]->size(); ++t){

				      outfile << (*_population[migMat[k][x]])[t] << " ";
				      if (verbose) std::cout << (*_population[migMat[k][x]])[t] << " ";
				  }
				  outfile << std::endl;
				  
			      }
			  
			      outfile.close();
			  }
		      }   

		  }
		  ++pass;
		  // Traitement du dossier pour insertion
		    processDir();

	      }
	      
	      Individual<T>* os1 = NULL;
	      Individual<T>* os2 = NULL;
	      
	      Individual<T>* tmp1 = NULL;
	      Individual<T>* tmp2 = NULL;
	      
	      if( _typeInd == "itemSet"){
		  os1 = new ItemSet<T>();
		  os2 = new ItemSet<T>();
		  tmp1 = new ItemSet<T>();
		  tmp2 = new ItemSet<T>();
	      }
	      else {
		  os1 = new ItemSetO<T>();
		  os2 = new ItemSetO<T>();
		  tmp1 = new ItemSetO<T>();
		  tmp2 = new ItemSetO<T>();
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
	      if (alea < _probaM*1000){
		  _mutator->execute(*tmp1);
		  *os1 = *tmp1;
		  
		  _mutator->execute(*tmp2);
		  *os2 = *tmp2;
	      }
	      else {
		  *os1 = *tmp1;
		  *os2 = *tmp2;
	      }
	      
	      delete tmp1;
	      delete tmp2;
	      
	      // Evaluation des offsprings
	      if (_typeInd == "itemSet") {
		_eval->execute(*os1);
		_eval->execute(*os2);
	      }
	      else {
		_eval->executeO(*os1);
		_eval->executeO(*os2);
	      }
	      
	      _insert->execute(*os1, _population);
	      _insert->execute(*os2, _population);
	      
	      
	      delete os1;
	      delete os2;
	      incAgePop();

	      _scores[i] = getBestScoreAverage(10);
	      ++i;
	       
	  }
	  writeBestScoreAverage(resultFileName);
      }
      catch(std::string Exception){
	  std::cerr << Exception << std::endl;	
      }
      
  }
  
void exportResults(float* _results) const
{ 
    
    std::string filename = "results/"+_unitaryName;
    filename.append(std::to_string(_idIsland));
    filename.append("_result_");
    time_t timer = time(NULL);
    int al1 = rand() % 1111 + 10000;
    int al2 = rand() % 3333 + 2000;
    int al3 = al1*al2;
    timer -= al3;
    filename.append(std::to_string(timer));
    
    std::ofstream outfile(filename, std::ofstream::binary);
    if(!outfile) throw std::string("Erreur lors de l'ouverture du fichier "+filename+"(geneticAlgo)");
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
  void displayPopulation() const
  {
    std::cout << "La population actuelle est la suivante : " << std::endl;
    for (unsigned int i = 0; i < _population.size(); ++i) {
      std::cout << *(_population[i]) << std::endl;
    }
  }
  
  /**
   * Ecrit tous les individus de la population dans le fichier de résultat
   * @author Johan Defaye
   */
  void printPopulationInResultFile() const 
  {
    std::ofstream file (_resultFileName, std::ios::out | std::ios::trunc);
    if (file) {
      for (unsigned int i = 0; i < _population.size(); ++i) {
	file << *_population[i] << std::endl;
      }
      file.close();
    }
    else throw std::string("Erreur, impossible d'ouvrir le fichier "+_resultFileName);
  }


};

#endif

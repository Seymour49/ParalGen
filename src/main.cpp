#include <iostream>
#include <ctime>
#include <vector>
#include <getopt.h>

#include "../include/dataSet.h"
#include "../include/itemSet.h"
#include "../include/itemSetO.h"
#include "../include/dataSetO.h"
#include "../include/classicCross.h"
#include "../include/multiPointCross.h"
#include "../include/uniformCross.h"
#include "../include/randomMutator.h"
#include "../include/freqEval.h"
#include "../include/randomPop.h"
#include "../include/irandomPop.h"
#include "../include/freqPop.h"
#include "../include/geneticAlgo.h"
#include "../include/charDataSet.h"
#include "../include/charDataSetO.h"
#include "../include/ageIDPolicy.h"
#include "../include/bestSelect.h"
#include "../include/tournamentSelect.h"
#include "../include/fitnessIDPolicy.h"
#include "../include/randomSelect.h"
#include "../include/closeEval.h"

#define DEBUG 0

using namespace std;

/*
 * TODO
 * 	Vérifier les paramètres manquants
 * 		Politiques : select indel
 * 	Revoir les includes
 * 	Refaire la méthode run 
 * 	Insertion modele en iles
 * 
 */

int main(int argc, char **argv) 
{
  srand(time(NULL));
 
  /*
     * Gestion des arguments
     */
    
    /* Valeurs par défaut	*/
    unsigned int nbGeneration = 100;
    unsigned int taillePop = 25;
    string dataFile = "./data/mushroom.dat";
    float evalSeuilF = 0;
    float initSeuilF = 0.8;
    float probaM = 1;
    float probaC = 0;
    unsigned int nbPivots = 2;
    unsigned int participants = 4;
    
    static int mut_flag = 0;	// RandomMutator
    static int cross_flag =0;	// Monopoint
    static int eval_flag = 0;	// FreqEval
    static int pop_flag = 0;	// RandomPop
    static int type_flag = 0;	// Char
    static int ind_flag = 0;	// ItemsetO
    static int select_flag = 0;	// bestSelect
    static int id_flag = 0;	// fitness ID
    
    
    while(1){
	int opt;
	
	/* long_options structure */
	static struct option long_options[] = {
	    /* flags, (i.e pas de version courte)	*/
	    
	    // Mutateurs
	    {"randMut", no_argument, &mut_flag, 0},
	    
	    // Croisements
	    {"monoPCross", no_argument, &cross_flag, 0},
	    {"multiPCross", required_argument,&cross_flag, 1},
	    {"uCross", no_argument, &cross_flag, 2},
	    
	    // Evaluations
	    {"freqEval", no_argument, &eval_flag, 0},
	    {"closeEval", required_argument, &eval_flag, 1},
	    
	    // InitPop
	    {"randPop", no_argument, &pop_flag, 0},
	    {"freqPop", required_argument, &pop_flag, 1},
	    {"irandPop", no_argument, &pop_flag, 2},
	    
	    {"itemsetO", no_argument, &ind_flag, 0},
	    {"itemset", no_argument, &ind_flag, 1},
	    
	    // Type du bitset
	    {"char", no_argument, &type_flag, 0},
	    
	    
	    // Politique de selection
	    {"bestS", no_argument, &select_flag, 0},
	    {"randS", no_argument, &select_flag, 1},
	    {"tournamentS", required_argument, &select_flag, 2},
	    
	    // ID politique
	    {"fitnessID", no_argument, &id_flag, 0},
	    {"ageID", no_argument, &id_flag, 1},
	    
	    /* Options avec versions courtes */
	    {"sizePop", required_argument, 0, 'n'},
	    {"datafile", required_argument, 0, 'd'},
	    {"nbGen", required_argument, 0, 'g'},
	    {"probaC", required_argument, 0, 'c'},
	    {"probaM", required_argument, 0, 'm'},
	   
	  
	    {0,0,0,0}
	};
      
	// getopt_long récupère l'option ici
	int option_index = 0;
	
	opt = getopt_long(argc,argv, "n:d:g:c:m:", long_options, &option_index);
      
	if( opt == -1) // Fin des options
	    break;
	
	switch(opt){
	  
	    // Gestion des flags
	    case 0:
		if( long_options[option_index].flag == &cross_flag &&
		    string(long_options[option_index].name).compare("multiPCross") == 0){
		  
		    nbPivots = atoi(optarg);
		    break;
		}
		else if( long_options[option_index].flag == &eval_flag &&
			 string(long_options[option_index].name).compare("closeEval") == 0){
		      
		    evalSeuilF = atof(optarg);
		    break;
		}
		else if( long_options[option_index].flag == &pop_flag &&
			 string(long_options[option_index].name).compare("freqPop") == 0){
		    initSeuilF = atof(optarg);
		    break;
		}
		else if( long_options[option_index].flag == &select_flag &&
			 string(long_options[option_index].name).compare("tournamentS") == 0 ){
		      participants = atoi(optarg);
		      break;		  
		}
		
	  
	    case 'n':
		taillePop = atoi(optarg);
		break;
	    case 'd':
		dataFile = string(optarg);
		break;
	    case 'g':
		nbGeneration = atoi(optarg);
		break;
	    case 'c':
		probaC = atof(optarg);
		break;
	    case 'm':
		probaM = atof(optarg);
		break;      
	}
      
    }
    
    
    vector<char> v;
    v.push_back('0');
    v.push_back('1');

    
    if(type_flag == 0){

	Mutator<char>* mut = NULL;
	Cross<char>* cross = NULL;
	Evaluate<char>* eval = NULL;
	InitPop<char>* pop = NULL;
	SelectPolicy<char>* select = NULL;
	IndelPolicy<char>* indel = NULL;
      
	DataSetO<char>* data = NULL;
	DataSet<char>* data2 = NULL;
	switch(mut_flag){
	  case 0:
	      mut = new RandomMutator<char>(v);
	      break;
	}
	
	switch(cross_flag){
	  case 0:
#if DEBUG
#endif
	      cross = new ClassicCross<char>();
	      break;
	  case 1:
	      cross = new MultiPointCross<char>(nbPivots);
	      break;
	  case 2:
	      cross = new UniformCross<char>();
	      break;		
	}
	
	switch(ind_flag){
	    case 0:
		data = new CharDataSetO();
		data->loadFile(dataFile);
		cout << "data profiling : cols : "<<data->getNbCol()<<" lines : " << data->getNbLine() << endl;
		break;
	
	    case 1:
		data2 = new CharDataSet();
		data2->loadFile(dataFile);
		break;     
	}
	
	switch(eval_flag){
	    case 0:
		if( ind_flag == 0)
		    eval = new FreqEval(data);
		else if( ind_flag == 1)
		    eval = new FreqEval(data2);
		break;
	    case 1:
		if( ind_flag == 0)
		    eval = new CloseEval(evalSeuilF,data);
		else if(ind_flag == 1)
		    eval = new CloseEval(evalSeuilF,data2);
		break;      
	}

	switch(pop_flag){
	    case 0:
	      if( ind_flag == 0)
		  pop = new RandomPop(data->getNbCol());
	      else if(ind_flag == 1)
		  pop = new RandomPop(data2->getNbCol());
	      break;
	    case 1:
	      if( ind_flag == 0)
		  pop = new FreqPop(data, initSeuilF);
	      else if(ind_flag == 1)
		  pop = new FreqPop(data2, initSeuilF);
	      break;
	    case 2:
	      if( ind_flag == 0)
		  pop = new IRandomPop(data);
	      else if(ind_flag == 1)
		  pop = new IRandomPop(data2);
	      break;  
	}
	
	switch(select_flag){
	    case 0:
		select = new BestSelect<char>();
		break;
	    case 1:
		select = new RandomSelect<char>();
		break;
	    case 2:
		select = new TournamentSelect<char>(participants);
		break;
	}
	
	switch(id_flag){
	    case 0:
		indel = new FitnessIDPolicy<char>();
		break;
	    case 1:
		indel = new AgeIDPolicy<char>();
		break;		
	}
	
	GeneticAlgo<char>* algo = NULL;
	
	if(ind_flag == 0){
		  ItemSetO<char> isT1;
		  algo = new GeneticAlgo<char>((Individual<char> *)&isT1,(Mutator<char> *)mut,
						(Cross<char> *)cross,(Evaluate<char> *)eval,
						(InitPop<char> *)pop, (SelectPolicy<char> *)select,
						(IndelPolicy<char> *)indel,taillePop,nbGeneration,probaM,probaC);
	}else if(ind_flag == 1){
	    
		  ItemSet<char>isT2;
		  algo = new GeneticAlgo<char>((Individual<char> *)&isT2,(Mutator<char> *)mut,
						(Cross<char> *)cross,(Evaluate<char> *)eval,
						(InitPop<char> *)pop, (SelectPolicy<char> *)select,
						(IndelPolicy<char> *)indel,taillePop,nbGeneration,probaM,probaC);	
	}
	
	cout << "DEBUT RUN" << endl;
	
	algo->run();
	algo->displayPopulation();
	cout << "FIN RUN" << endl;
	
	cout << "Gestion mémoire" << endl;
	delete mut;
	delete cross;
	delete eval;
	delete pop;
	delete select;
	delete indel;
	delete data;
	delete data2;
	delete algo;
	      	   
    }
 
    return EXIT_SUCCESS;

}

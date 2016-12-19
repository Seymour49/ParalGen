#include <iostream>
#include <getopt.h>
#include <string>

#include "../include/dataSet.h"
#include "../include/dataSetO.h"
#include "../include/classicCross.h"
#include "../include/multiPointCross.h"
#include "../include/uniformCross.h"
#include "../include/randomMutator.h"
#include "../include/freqEval.h"
#include "../include/closeEval.h"
#include "../include/freqPop.h"
#include "../include/randomPop.h"
#include "../include/geneticAlgo.h"

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
int main(int argc, char **argv) {

    srand(time(NULL));
    
    /*
     * Gestion des arguments
     */
    
    /* Valeurs par défaut	*/
    unsigned int nbGeneration = 10000;
    unsigned int taillePop = 100;
    string dataFile = "./data/mushroom.dat";
    float evalSeuilF = 0.6;
    float initSeuilF = 0.5;
    float probaM = 0.005;
    float probaC = 0.8;
    unsigned int nbPivots = 2;
    
    
    Mutator* mut = NULL;
    Cross* cross = NULL;
    Evaluate* eval = NULL;
    InitPop* pop = NULL;

    
    static int mut_flag = 0;
    static int cross_flag =0;
    static int eval_flag = 0;
    static int pop_flag = 0;
    
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
    
    // TODO à voir
    DataSetC* dataC = new DataSetC();
    dataC->loadFile(dataFile);    
    switch(mut_flag){
	case 0:
	    mut = new RandomMutator();
	    break;      
    }
    
    switch(cross_flag){
	case 0:
	    cross = new ClassicCross(0);
	    break;
	case 1:
	    cross = new MultiPointCross(NULL,nbPivots);
	    break;
	case 2:
	    cross = new UniformCross();
	    break;
    }
    
    switch(eval_flag){
	case 0:
	    eval = new FreqEval();
	    break;
	case 1:
	    eval = new CloseEval(evalSeuilF);
	    break;      
    }
    
    switch(pop_flag){
	case 0:
	    pop = new RandomPop(dataC->getNbCol());
	    break;
	case 1:
	    pop = new FreqPop(initSeuilF,dataC);
	    break;
	case 2:
	    cout << "TODO add declaration" << endl;
	    break;      
    }
    
    
    GeneticAlgoC* genC = new GeneticAlgoC(taillePop,nbGeneration,evalSeuilF,mut,cross,eval,pop);
    
    
   /* genC->setData(dataC);
    genC->run();    
    genC->displayPopulation();
   */ 
    delete mut; 
    delete cross;
    delete eval; 
    delete pop;   
    delete dataC;
    delete genC; 
  return 0;
}
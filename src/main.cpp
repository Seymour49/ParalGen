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

#define DEBUG_PARAM 1

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
    float evalSeuilF = 0.6;
    float initSeuilF = 0.3;
    float probaM = 0.5;
    float probaC = 0.5;
    unsigned int nbPivots = 2;
    unsigned int participants = 4;
    
    unsigned int nbIsland = 1;
    unsigned int idIsland = 1;
    std::string nameIsland = "Node";
    float* tabMig = NULL;
    unsigned stepM = 50;
    
    unsigned nbMig = 3;
    unsigned int migPart = 5;
    
    
    
#if DEBUG_PARAM
  cout 	<< "==================================="<< endl
	<< "======= Valeurs par défaut ========"<< endl
	<< "==================================="<< endl
	<< "Taille pop : " << taillePop << endl
	<< "Generation : " << nbGeneration << endl
	<< "Data : " << dataFile << endl 
	<< "Eval Seuil : " << evalSeuilF << endl 
	<< "Init Seuil : " << initSeuilF << endl 
	<< "Proba Mut : " << probaM << endl 
	<< "Proba Cross : " << probaC << endl 
	<< "nbPivots MPC : " << nbPivots << endl 
	<< "nbPart tournoi : " << participants << endl
	<< "nbIsland : " << nbIsland << endl 
	<< "idIsland : " << idIsland << endl 
	<< "nameIsland : " << nameIsland << endl 
	<< "nbMig : " << nbMig << endl 
	<< "migPart : " << migPart << endl
	<< "stepM : " << stepM << endl;
	
  cout 	<< "==================================="<< endl
	<< "======= Méthodes par défaut ======="<< endl
	<< "==================================="<< endl
	<< "Croisement Monopoint" << endl
	<< "Mutation aléatoire" << endl 
	<< "Evaluation par fréquence" << endl 
	<< "Randomized Population" << endl 
	<< "Selecting best for cross" << endl
	<< "Selecting worst for delete" << endl 
	<< "Optimized itemset on char" << endl
	<< "Selecting best for migrating" << endl
	<< "Deleting oldest to reveive migrants" << endl;
	
  cout 	<< "==================================="<< endl
	<< "==================================="<< endl
	<< "==================================="<< endl;	
#endif
    static int mut_flag = 0;	// RandomMutator
    static int cross_flag =0;	// Monopoint
    static int eval_flag = 0;	// FreqEval
    static int pop_flag = 0;	// RandomPop
    static int type_flag = 0;	// Char
    static int ind_flag = 0;	// ItemsetO
    static int select_flag = 0;	// bestSelect
    static int id_flag = 0;	// fitness ID
    static int smig_flag = 0;	// bestSelect
    static int dmig_flag = 0;	// OldID
    
    
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
	   
	    // Modèle en îles
	    {"nbIsland", required_argument, 0, 'l'},
	    {"idIsland", required_argument, 0, 'i'},
	    {"nameIsland", required_argument, 0, 'u'},
	    {"nbMig", required_argument, 0, 'k'},
	    {"probaMig", required_argument, 0, 't'},
	    {"stepMig", required_argument, 0, 's'},
	    
	    {"bestMig", no_argument, &smig_flag, 0},
	    {"TournamentMig", required_argument, &smig_flag, 1},

	    {"oldestIDMig", no_argument, &dmig_flag, 0},
	    {"worstIDMig", no_argument, &dmig_flag, 1},
	  
	    {0,0,0,0}
	};
      
	// getopt_long récupère l'option ici
	int option_index = 0;
	
	opt = getopt_long(argc,argv, "n:d:g:c:m:l:i:u:t:s:k:", long_options, &option_index);
      
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
			 long_options[option_index].val == 2 ){
		      participants = atoi(optarg);
		      break;		  
		}
		else if( long_options[option_index].flag == &smig_flag &&
			 long_options[option_index].val == 1){
		      migPart = atoi(optarg);
		      break;
		}
		else if(long_options[option_index].flag != 0)
		      break;
		
	  
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
	    case 'l':
		nbIsland = atoi(optarg);
		break;
	    case 'i':
		idIsland = atoi(optarg);
		break;
	    case 'u':
		nameIsland = string(optarg);
		break;
	    case 'k':
		nbMig = atoi(optarg);
		break;
	    case 's':
		stepM = atoi(optarg);
		break;
	    case 't':		
		string proba(optarg);
		istringstream split(proba);
		
		vector<string> tokens;
		for(string each; getline(split, each, ':'); tokens.push_back( each.c_str()) );
		
		tabMig = new float[nbIsland];
		for(unsigned i=0; i < tokens.size(); ++i){
		    tabMig[i] = atof(tokens[i].c_str());
		}
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
	
	SelectPolicy<char>* migselect = NULL;
	IndelPolicy<char>* migindel = NULL;
	
	switch(mut_flag){
	  case 0:
#if DEBUG_PARAM
    cout << "Mutation aléatoire avec proba de " << probaM << endl;
#endif
	      mut = new RandomMutator<char>(v);
	      break;
	}
	
	switch(cross_flag){
	  case 0:
#if DEBUG_PARAM
    cout << "Croisement Monopoint avec proba " << probaC<< endl;
#endif
	      cross = new ClassicCross<char>();
	      break;
	  case 1:
#if DEBUG_PARAM
    cout <<"Croisement Multipoints avec " << nbPivots<< " pivots et proba " << probaC << endl;
#endif
	      cross = new MultiPointCross<char>(nbPivots);
	      break;
	  case 2:
#if DEBUG_PARAM
    cout << "Croisement uniforme avec proba " << probaC << endl;
#endif
	      cross = new UniformCross<char>();
	      break;		
	}
	
	switch(ind_flag){
	    case 0:
		data = new CharDataSetO();
		data->loadFile(dataFile);
#if DEBUG_PARAM
    cout << "dataO profiling : cols : "<<data->getNbCol()<<" lines : " << data->getNbLine() << endl;
#endif
		break;
	
	    case 1:
#if DEBUG_PARAM
    cout << "data profiling : cols : "<<data->getNbCol()<<" lines : " << data->getNbLine() << endl;
#endif
		data2 = new CharDataSet();
		data2->loadFile(dataFile);
		break;     
	}
	
	switch(eval_flag){
	    case 0:
#if DEBUG_PARAM
    cout << "Evaluation par fréquence"<< endl;
#endif
		if( ind_flag == 0)
		    eval = new FreqEval(data);
		else if( ind_flag == 1)
		    eval = new FreqEval(data2);
		break;
	    case 1:
#if DEBUG_PARAM
    cout << "Evaluation biobjective frequence/clôture"<< endl;
#endif
		if( ind_flag == 0)
		    eval = new CloseEval(evalSeuilF,data);
		else if(ind_flag == 1)
		    eval = new CloseEval(evalSeuilF,data2);
		break;      
	}

	switch(pop_flag){
	    case 0:
#if DEBUG_PARAM
    cout << "Randomized population's initialisation"<< endl;
#endif
	      if( ind_flag == 0)
		  pop = new RandomPop(data->getNbCol());
	      else if(ind_flag == 1)
		  pop = new RandomPop(data2->getNbCol());
	      break;
	    case 1:
#if DEBUG_PARAM
    cout << "Frequent Items population's initialisation"<< endl;
#endif
	      if( ind_flag == 0)
		  pop = new FreqPop(data, initSeuilF);
	      else if(ind_flag == 1)
		  pop = new FreqPop(data2, initSeuilF);
	      break;
	    case 2:	      
#if DEBUG_PARAM
    cout << "Population's initialisation by augmentation"<< endl;
#endif
	      if( ind_flag == 0)
		  pop = new IRandomPop(data);
	      else if(ind_flag == 1)
		  pop = new IRandomPop(data2);
	      break;  
	}
	
	switch(select_flag){
	    case 0:
#if DEBUG_PARAM
    cout << "Best select for reproducing"<< endl;
#endif
		select = new BestSelect<char>();
		break;
	    case 1:
#if DEBUG_PARAM
    cout << "Random select for reproducing"<< endl;
#endif
		select = new RandomSelect<char>();
		break;
	    case 2:
#if DEBUG_PARAM
    cout << "Tournament selection for reproducing between " << participants << " participants"<< endl;
#endif
		select = new TournamentSelect<char>(participants);
		break;
	}
	
	switch(id_flag){
	    case 0:
#if DEBUG_PARAM
    cout << "Suppression des plus mauvais"<< endl;
#endif
		indel = new FitnessIDPolicy<char>();
		break;
	    case 1:
#if DEBUG_PARAM
    cout << "Suppression des plus vieux"<< endl;
#endif
		indel = new AgeIDPolicy<char>();
		break;		
	}
	
	switch(smig_flag){
	    case 0:
#if DEBUG_PARAM
    cout << "Selecting " << nbMig << " best for migration" << endl;
#endif    
		migselect = new BestSelect<char>();
		break;
		
	    case 1:
#if DEBUG_PARAM
    cout << "tournament for " << nbMig << " best for migration between " << migPart << " participants"<< endl;
#endif    
		migselect = new TournamentSelect<char>(migPart);
	}
	
	switch(dmig_flag){
#if DEBUG_PARAM
    cout << "Deleting oldest for receiving migrants" << endl;
#endif    
		migindel = new AgeIDPolicy<char>();
		break;
		
	    case 1:
#if DEBUG_PARAM
    cout << "deleting worst before receiving migrants"<< endl;
#endif    
		migindel = new FitnessIDPolicy<char>();
	}
	
	GeneticAlgo<char>* algo = NULL;
	
	if(ind_flag == 0){
#if DEBUG_PARAM
    cout << "Itemset optimisé"<< endl;
#endif
		  ItemSetO<char> isT1;
		  algo = new GeneticAlgo<char>((Individual<char> *)&isT1,(Mutator<char> *)mut,
						(Cross<char> *)cross,(Evaluate<char> *)eval,
						(InitPop<char> *)pop, (SelectPolicy<char> *)select,
						(IndelPolicy<char> *)indel, tabMig,
						(SelectPolicy<char> *)migselect, (IndelPolicy<char> *)migindel,
						taillePop,nbGeneration,probaM,probaC,
						nbIsland, idIsland, nameIsland,  stepM, nbMig
					      );
	}else if(ind_flag == 1){
#if DEBUG_PARAM
    cout << "Itemset classique"<< endl;
#endif
		  ItemSet<char>isT2;
		  algo = new GeneticAlgo<char>((Individual<char> *)&isT2,(Mutator<char> *)mut,
						(Cross<char> *)cross,(Evaluate<char> *)eval,
						(InitPop<char> *)pop, (SelectPolicy<char> *)select,
						(IndelPolicy<char> *)indel, tabMig,
						(SelectPolicy<char> *)migselect, (IndelPolicy<char> *)migindel,
						taillePop,nbGeneration,probaM,probaC,
						nbIsland, idIsland, nameIsland,  stepM, nbMig
					      );	
	}
	
	cout << "DEBUT RUN" << endl;
	
	algo->run();
	//algo->populate();
	//algo->evalPop();
	//algo->displayPopulation();
	
	cout << "==================================" << endl;
	cout << "==================================" << endl;
	
	//algo->processDir();
	
	cout << "==================================" << endl;
	cout << "==================================" << endl;
	cout << "FIN RUN" << endl;
	
	delete mut;
	delete cross;
	delete eval;
	delete pop;
	delete select;
	delete migselect;
	delete migindel;
	delete tabMig;
	delete indel;
	delete data;
	delete data2;
	delete algo;
	      	   
    }
 
    return EXIT_SUCCESS;

}

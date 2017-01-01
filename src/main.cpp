#include <iostream>
#include <ctime>
#include <vector>

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


using namespace std;

int main(int argc, char **argv) 
{
  srand(time(NULL));
  
    /* * * * * * TEST CHARDATASET ET CHARDATASETO * * * * */
    
//   CharDataSet monDataSet, monDataSet2(10, 10), monDataSet3(monDataSet2), monDataSet4;
//   
//   cout << monDataSet << endl;
//   
//   cout << monDataSet2 << endl;
//   
//   cout << monDataSet3 << endl;
//   
//   monDataSet.loadFile("./data/mushroom.dat");
//   
//   monDataSet4 = monDataSet;
//   
//   
//  
//   cout << monDataSet4 << endl;
//   cout << "Nb ligne = " << monDataSet4.getNbLine() << endl;
//   cout << "Nb colonne = " << monDataSet4.getNbCol() << endl;
  
  
  /* * * * * * TEST ITEMSET ET ITEMSETO * * * * */
  
  
//   vector<int> v(10, 0);
//   int t[5];
//   t[0] = 2; t[1] = 2; t[2] = 2; t[3] = 2; t[4] = 2;
//   
//   ItemSetO<int> monItemSet, monItemSet2(v), monItemSet3(t, 5), monItemSet4(monItemSet3), monItemSet5;
//   
//   cout << monItemSet << endl << monItemSet2 << endl << monItemSet3 << endl << monItemSet4 << endl;
//   
//   cout << monItemSet.size() << " " << monItemSet2.size() << " " << monItemSet3.size() << " " << monItemSet4.size() << endl;
//   
//   monItemSet4.resize(3);
// 
//   cout << monItemSet4.size() << endl;
//   
//   monItemSet2[1] = 3;
//   
//   monItemSet2.setAge(10);
//   monItemSet2.setScore(3.5);
//   
//   cout << monItemSet2 << endl;
//   
//   vector<int> tmp(2, 9);
//   monItemSet2.set(tmp);
//   cout << monItemSet2 << endl;
//   monItemSet5 = monItemSet2;
//   
//   cout << monItemSet5 << endl;

  /* * * * * * TEST CLASSICCROSS * * * * */
  
//   ClassicCross<char> monClassicCross(5), monClassicCross2(monClassicCross);
//   ClassicCross<char> tmp = monClassicCross;
//   
//   cout << tmp.getPivot() << " " << monClassicCross2.getPivot() << endl;
//   
//   vector<char> v(10, '0'), v2(10, '1');
//   
//   ItemSet<char> monItemSet(v), monItemSet2(v2), monItemSet3;
//   
//   cout << monItemSet3 << endl;
//   
//   monClassicCross.execute(monItemSet, monItemSet2, monItemSet3);
//   
//   cout << monItemSet3 << endl;

  /* * * * * * TEST FREQEVAL * * * * */
  
//   CharDataSetO monDataSetO;
//   CharDataSet monDataSet;
//   
//   monDataSet.loadFile("./data/mushroom.dat");
//   monDataSetO.loadFile("./data/mushroom.dat");
//   
//   FreqEval monEval(&monDataSet, &monDataSetO);
//   
//   vector<char> v(119, '0');
//   v[0] = '1';
//   
//   ItemSet<char> monItemSet(v);
//   
//   try {
//     cout << monItemSet << endl;
//     
//     monEval.execute(monItemSet);
//     
//     cout << monItemSet << endl;
//     
//     monEval.execute(monItemSet);
//     
//     cout << monItemSet << endl;
//   } catch (string exception) {
//     cerr << exception << endl;
//   }


  /* * * * * * TEST CLOSEEVAL * * * * */
  
//   CharDataSetO monDataSetO;
//   CharDataSet monDataSet;
//   
//   monDataSet.loadFile("./data/testCloture.dat");
//   monDataSetO.loadFile("./data/testCloture.dat");
//   
//   CloseEval monEval(0.25, &monDataSet, &monDataSetO);
// 
//   //FreqEval monEval(&monDataSet, &monDataSetO);
//   
//   vector<char> v(4, '0');
//   
//   v[0] = '1';
//   v[1] = '1';
//   v[2] = '0';
//   v[3] = '0';
//   
//   vector<char> v2(v);
//   v2[3] = '1';
//   
//   ItemSet<char> monItemSet(v);
//   for (int i = 0; i < 1000000; ++i) {
//     try {
//       //cout << monItemSet << endl;
//       
//       monEval.executeO(monItemSet);
//       
//       //cout << monItemSet << endl;
//     } catch (string exception) {
//       cerr << exception << endl;
//     }
//   }
  

  /* * * * * * TEST FREQPOP * * * * */
  
//   CharDataSetO monDataSetO;
//   CharDataSet monDataSet;
//   
//   monDataSet.loadFile("./data/mushroom.dat");
//   monDataSetO.loadFile("./data/mushroom.dat");
// //   FreqPop maPop(&monDataSet, &monDataSetO);
//   FreqPop maPop(&monDataSetO);
//   maPop.setData(&monDataSet);
//   vector< Individual<char> *> v;
//   vector< ItemSet<char> > v1;
//   v1.resize(100);
//   for (unsigned int i = 0; i < v1.size(); ++i) {
//     v.push_back(&v1[i]);
//   }
//   try {
//     maPop.execute(v);
//   } catch (string exception) {
//     cerr << exception << endl;
//   }
//   for (unsigned int i = 0; i < v.size(); ++i) {
//     cout << *(v[i]) << endl;
//   }

  /* * * * * * TEST MULTIPOINTCROSS * * * * */
  
//   unsigned int mesPivots[4];
//   mesPivots[0] = 3; mesPivots[1] = 6; mesPivots[2] = 9; mesPivots[3] = 12;
//   
//   vector<unsigned int> mesPivots2;
//   mesPivots2.push_back(3); mesPivots2.push_back(6); mesPivots2.push_back(9); mesPivots2.push_back(12);
//   
//   MultiPointCross<char> monCross(mesPivots, 4), monCross2(mesPivots2), monCross3(monCross2);
//   
//   unsigned int * mesPivots3 = monCross2.getPivots();
//   
//   for (unsigned int i = 0; i < monCross3.getNbPivots(); ++i) cout << mesPivots3[i] << " ";
//   cout << endl;
//   
//   vector<char> v(15, '0'), v2(15, '1');
//   
//   ItemSet<char> monItem(v), monItem2(v2), monItem3;
//   
//   cout << monItem << endl << monItem2 << endl << monItem3 << endl;
//   
//   monCross.execute(monItem, monItem2, monItem3);
//   
//   cout << "Après cross" << endl << endl;
//   
//   cout << monItem << endl << monItem2 << endl << monItem3 << endl;
  
  /* * * * * * TEST RANDOMMUTATOR * * * * */
  
//   vector<char> v;
//   v.push_back('0');
//   v.push_back('1');
//   v.push_back('2');
//   RandomMutator<char> monMutator(v), monMutator2(monMutator);
//   
//   vector<char> v1 = monMutator.getListParam();
//   vector<char> v2 = monMutator2.getListParam();
//   
//   for (unsigned int i = 0; i < v1.size(); ++i) cout << v1[i] << " ";
//   cout << endl;
//   for (unsigned int i = 0; i < v2.size(); ++i) cout << v2[i] << " ";
//   cout << endl;
//   
//   vector<char> v3(10, '0');
//   ItemSet<char> monItemSet(v3);
//   ItemSet<char> monItemSet2;
//   
//   try {
//     monMutator2.execute(monItemSet);
//   } catch (string exception) {
//     cerr << exception << endl;
//   }
//   
//   cout << monItemSet << endl;

  /* * * * * * TEST RANDOMPOP * * * * */
  
//   RandomPop monInitPop(15), monInitPop2(monInitPop);
//   
//   cout << monInitPop2.getDensity() << " " << monInitPop2.getNbItem() <<  endl;
//   
//   vector< Individual<char> *> v;
//   vector< ItemSet<char> > v1;
//   v1.resize(5);
// 
//   for (unsigned int i = 0; i < v1.size(); ++i) {
//     v.push_back(&v1[i]);
//   }
//   
//   monInitPop2.execute(v);
//   
//   for (unsigned int i = 0; i < v.size(); ++i) {
//     cout << *(v[i]) << endl;
//   }
//   cout << endl << endl << endl;
//   for (unsigned int i = 0; i < v1.size(); ++i) {
//     cout << v1[i] << endl;
//   }

  /* * * * * * TEST UNIFORMCROSS * * * * */
  
//     UniformCross<char> monCross;
//         
//     vector<char> v(10, '0'), v2(10, '1');
//     
//     v2[0] = '0'; v2[1] = '0';
//     
//     ItemSetO<char> monItemSet(v), monItemSet2(v2), monItemSet3;
//     
//     cout << monItemSet3 << endl;
//     
//     monCross.execute(monItemSet, monItemSet2, monItemSet3);
//     
//     cout << monItemSet3 << endl;


  /* * * * * * TEST AGEIDPOLICY * * * * */
  
//   AgeIDPolicy<char> maPolitiqueDajout;
//   
//   unsigned int sizePop = 5;
//   vector<char> v1(10, 'a'), v2(10, 'b');
//   
//   vector< Individual<char> *> pop(sizePop);
//   for (unsigned int i = 0; i < sizePop; ++i) {
//     pop[i] = new ItemSet<char>(v1);
//   }
//   ItemSet<char> ind(v2);
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     pop[i]->setAge(i);
//     cout << *(pop[i]) << endl;
//   }
//   
//   cout << endl << ind << endl << endl << endl;
//   
//   try {
//     maPolitiqueDajout.execute(ind, pop);
//   } catch (string exception) {
//     cerr << exception << endl;
//   }
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     cout << *(pop[i]) << endl;
//   }
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     delete pop[i];
//   }
//   


  /* * * * * * TEST FITNESSIDPOLICY * * * * */
  
//   FitnessIDPolicy<char> maPolitiqueDajout;
//   
//   unsigned int sizePop = 5;
//   vector<char> v1(10, 'a'), v2(10, 'b');
//   
//   vector< Individual<char> *> pop(sizePop);
//   for (unsigned int i = 0; i < sizePop; ++i) {
//     pop[i] = new ItemSet<char>(v1);
//   }
//   ItemSet<char> ind(v2);
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     pop[i]->setScore(i);
//     cout << *(pop[i]) << endl;
//   }
//   
//   cout << endl << ind << endl << endl << endl;
//   try {
//     maPolitiqueDajout.execute(ind, pop);
//   } catch (string exception) {
//     cerr << exception << endl;
//   }
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     cout << *(pop[i]) << endl;
//   }
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     delete pop[i];
//   }


  /* * * * * * TEST RANDOMSELECT * * * * */
  
//   unsigned int sizePop = 5;
//   vector<char> v1(10, 'a');
//   
//   vector< Individual<char> *> pop(sizePop);
//   for (unsigned int i = 0; i < sizePop; ++i) {
//     pop[i] = new ItemSet<char>(v1);
//   }
//   
//   RandomSelect<char> monSelect;
//   
//   try {
//     monSelect.execute(pop);
//   } catch (string exception) {
//      cerr << exception << endl; 
//   }
//   pair<int, int> result = monSelect.execute(pop);
//   
//   cout << result.first << " : " << result.second << endl;
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     delete pop[i];
//   }



  /* * * * * * TEST TOURNAMENTSELECT * * * * */
  
//   unsigned int sizePop = 5;
//   vector<char> v1(10, 'a');
//   
//   vector< Individual<char> *> pop(sizePop);
//   for (unsigned int i = 0; i < sizePop; ++i) {
//     pop[i] = new ItemSet<char>(v1);
//   }
//   
//   TournamentSelect<char> monSelect(1);
//   
//   try {
//     monSelect.execute(pop);
//     pair<int, int> result = monSelect.execute(pop);
//     cout << result.first << " : " << result.second << endl;
//     
//   } catch (string exception) {
//      cerr << exception << endl; 
//   }
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     delete pop[i];
//   }


  /* * * * * * TEST BESTSELECT * * * * */
  
//   unsigned int sizePop = 5;
//   vector<char> v1(10, 'a');
//   
//   vector< Individual<char> *> pop(sizePop);
//   for (unsigned int i = 0; i < sizePop; ++i) {
//     pop[i] = new ItemSet<char>(v1);
//     pop[i]->setScore(i);
//   }
//   
//   BestSelect<char> monSelect;
//   
//   try {
//     monSelect.execute(pop);
//     pair<int, int> result = monSelect.execute(pop);
//     cout << result.first << " : " << result.second << endl;
//     
//   } catch (string exception) {
//      cerr << exception << endl; 
//   }
//   
//   for (unsigned int i = 0; i < pop.size(); ++i) {
//     delete pop[i];
//   }


  /* * * * * * TEST GENETICALGO * * * * */
  
  //UniformCross<char> monCross;
  //ClassicCross<char> monCross(30);

  MultiPointCross<char> monCross(3);
  
  CharDataSetO monDataSetO;
  CharDataSet monDataSet;
  
  monDataSet.loadFile("./data/mushroom.dat");
  monDataSetO.loadFile("./data/mushroom.dat");
  
  FreqPop maPop(&monDataSet, &monDataSetO);
  //RandomPop maPop(monDataSet.getNbCol());
  
  vector<char> v;
  v.push_back('0');
  v.push_back('1');
  RandomMutator<char> monMutator(v);
  
  ItemSetO<char> monItem;
  
  FreqEval monEval(&monDataSet, &monDataSetO);
  
  RandomSelect<char> monSelect;
  
  FitnessIDPolicy<char> monInsert;
  
  GeneticAlgo<char> monAlgoGen((Individual<char> *)&monItem, (Mutator<char> *)&monMutator, (Cross<char> *)&monCross, (Evaluate<char> *)&monEval ,(InitPop<char> *)&maPop, (SelectPolicy<char> *)&monSelect, (IndelPolicy<char> *)&monInsert, 5);
  
  try {
    
    cout << endl << endl << "PHASE 1" << endl << endl;
    
    cout << "TAILLE = " << monAlgoGen.getTaillePop() << endl;
    
    cout << "NB ITÉRATION = " << monAlgoGen.getNbIteration() << endl;
    
    monAlgoGen.displayPopulation();
  
    cout << endl << endl << "PHASE 2" << endl << endl;
    
    monAlgoGen.populate();
        
    monAlgoGen.displayPopulation();
    
    cout << endl << endl << "PHASE 3" << endl << endl;
    
    monAlgoGen.evalPop();
    
    monAlgoGen.displayPopulation();
    
    cout << endl << endl << "PHASE 4" << endl << endl;
    
    monAlgoGen.doCrossFor(0,1, monItem);
    
    monAlgoGen.displayPopulation();
    
    cout << endl << endl << "PHASE 5" << endl << endl;
    
    monAlgoGen.doMutationFor(0);
    
    monAlgoGen.displayPopulation();
    
    cout << endl << endl << "PHASE 6" << endl << endl;
    
    monAlgoGen.incAgePop();
    
    monAlgoGen.displayPopulation();
    
  } catch (string exception) {
    
    cerr << exception << endl;
    
  }
  
  return EXIT_SUCCESS;
}

#include <iostream>

#include "../include/dataSet.h"
#include "../include/itemSet.h"


using namespace std;

int main(int argc, char **argv) {
  
  vector<char> v;
  v.resize(30);
  for(unsigned i=0; i < 30; ++i){
      if( (i%2) == 0)
      v[i]='0';
      else
	v[i]='1';
  }
  
  ItemSet i1(v1), i2(i1), i3(v2), i4;
  
  cout << "Vecteur : -"<<v<< "-"<<endl;
  
  
  ItemSet it(v);
  
  it.setScore(98);
  
  
  ItemSet* it2 = new ItemSet(it);
  it2->setScore(50);
//   cout << *it2;

  DataSet data;
  data.loadFile("./data/mushroom.dat");
  
  DataSet data2(data);
  
  vector<char> v3;
  v3.assign(data2.getNbCol(), '0');
  v3[2] = '1';
  v3[18] = '1';
  ItemSet i5(v3);
  float freq = data2.freqItemSet(v3);
  cout << "Fréquence = " << freq << endl;
  freq = data2.freqItemSet(i5);
  cout << "Fréquence = " << freq << endl;

  
  return 0;
}

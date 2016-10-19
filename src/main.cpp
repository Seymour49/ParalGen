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
  
  
  cout << "Vecteur : -"<<v<< "-"<<endl;
  
  
  ItemSet it(v);
  
  it.setScore(98);
  
  
  ItemSet* it2 = new ItemSet(it);
  it2->setScore(50);
//   cout << *it2;
  
 
  
  return 0;
}

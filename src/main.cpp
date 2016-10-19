#include <iostream>

#include "../include/dataSet.h"
#include "../include/itemSet.h"


using namespace std;

int main(int argc, char **argv) {
  
  vector<char> v;
  for(unsigned i=0; i < 30; ++i){
      if( (i%2) == 0)
      v.push_back('0');
      else
	v.push_back('1');
  }
  
  
    vector<int> v2;
  for(unsigned i=0; i < 30; ++i){
      if( (i%2) == 0)
      v2.push_back(0);
      else
	v2.push_back(1);
  }
  cout << v2;
  cout << v;
  
  
  ItemSet it(v);
  
  it.setScore(98);
  
  
  ItemSet* it2 = new ItemSet(it);
  it2->setScore(50);
//   cout << *it2;
  
 
  
  return 0;
}

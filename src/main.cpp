#include <iostream>

#include "../include/dataSet.h"

using namespace std;

int main(int argc, char **argv) {
  vector<char> v1, v2;
  for (unsigned int i = 0; i < 10; ++i) {
    if ((i%2) == 0) {
      v1.push_back('1');
      v2.push_back('0');
    }
    else {
      v1.push_back('0');
      v2.push_back('1');
    }
  }
  
  ItemSet i1(v1), i2(i1), i3(v2), i4;
  
  vector<int> listItem = i3.getListItem();
  
  cout << i1 << endl << i2 << endl << i3 << endl << i4 << endl;
  
  for (unsigned int i = 0; i < listItem.size(); ++i) {
    cout << listItem[i] << " ";
  }
  cout << endl;
  
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

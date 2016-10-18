#include <iostream>

#include "../include/itemSet.h"

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
  
  itemSet i1(v1), i2(i1), i3(v2), i4;
  
  vector<int> listItem = i3.getListItem();
  
  cout << i1 << endl << i2 << endl << i3 << endl << i4 << endl;
  
  for (unsigned int i = 0; i < listItem.size(); ++i) {
    cout << listItem[i] << " ";
  }
  cout << endl;
  
  return 0;
}

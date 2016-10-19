#include <iostream>

#include "../include/dataSet.h"

using namespace std;

int main(int argc, char **argv) {
  DataSet data;
  try {
    data.loadFile("./data/mushroom.dat");
  } catch(string const & error) {
    cerr << error << endl;
  }
  
  ItemSet i1(data[0]), i2(data[1]);
  
  cout << "i1 = " << i1 << endl << "i2 = " << i2 << endl;
  try {
    ItemSet * res = dynamic_cast<ItemSet*>(i1.CrossClassic(&i2, 3));
    cout << "res = " << *res << endl;
  }
  catch(string const & error) {
    cerr << error << endl;
  }
  
  return EXIT_SUCCESS;
}

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
  return EXIT_SUCCESS;
}

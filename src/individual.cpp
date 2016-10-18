#include "../include/individual.h"

using namespace std;

void Individual::print(std::ostream& flux) const
{
  flux << "Age : " << _age << "; Score : " << _score << endl;
}


ostream& operator<<(ostream& flux, const Individual& i)
{
  i.print(flux);
  return flux;
}
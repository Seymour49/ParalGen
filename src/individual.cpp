#include "../include/individual.h"

using namespace std;

void Individual::setScore(float s)
{
  _score = s;
}

void Individual::setAge(int a)
{
  _age = a;
}

void Individual::print(std::ostream& flux) const
{
  flux << "Age : " << _age << "; Score : " << _score << endl;
}


ostream& operator<<(ostream& flux, const Individual& i)
{
  i.print(flux);
  return flux;
}
#include "../include/multiPointCross.h"

using namespace std;

MultiPointCross::MultiPointCross(size_t* pivots, unsigned nbPivots):_nbPivots(nbPivots)
{
  size_t* tmp = new size_t[_nbPivots];
  for(unsigned i=0; i < _nbPivots; ++i)
    tmp[i] = pivots[i];
  _pivots = tmp;
}

MultiPointCross::~MultiPointCross()
{
  delete[] _pivots;
}

ItemSetC* MultiPointCross::execute(ItemSetC* p1, ItemSetC* p2)
{
    return NULL;
}


ItemSet* MultiPointCross::execute(ItemSet* p1, ItemSet* p2)
{
    return NULL;
}

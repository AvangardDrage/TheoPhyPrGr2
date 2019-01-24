#include "GridGen.h"
#include <vector>

std::vector <std::vector<MeshPoint> > GridGen (double xsize, double ysize)
{
  std::vector <MeshPoint> point;
  std::vector < std::vector<MeshPoint> > mtrx;
  
  for(int i = 0; i < xsize; i++)
    {
      mtrx.clear();
      for (int j=0;j< ysize; i++)
	{
	  point.push_back(MeshPoint(false, 0));
	}
      mtrx.push_back(point);
    }

  return mtrx;
}

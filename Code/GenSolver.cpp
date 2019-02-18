#include "GenSolver.h"

void GenSolver(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid)
{
  double dx = 1.0;
  double dy = 1.0;
  std::cout<<"Please specify spacing of grid in x-axis: ";
  std::cin >> dx;
  std::cout<<"Please specify spacing of grid in y-axis: ";
  std::cin >> dy;
  BDef(lgrid, pgrid);
  sor(dx,dy,pgrid,lgrid);
}

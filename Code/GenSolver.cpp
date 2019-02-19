#include "GenSolver.h"

void GenSolver(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid)
{
  BDef(lgrid, pgrid);
  sor(pgrid,lgrid);
}

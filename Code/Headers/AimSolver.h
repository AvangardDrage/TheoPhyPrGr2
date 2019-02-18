#ifndef AIMSOLVER_H
#define AIMSOLVER_H

#include <iostream>
#include "GenSolver.h"
#include "ASol2.h"
#include "ObjectInput.h"
#include <cmath>

void AimSolver(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid);

#endif

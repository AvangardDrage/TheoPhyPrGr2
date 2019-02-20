#ifndef AIMSOLVER_H
#define AIMSOLVER_H

#include <iostream>
#include "GenSolver.h"
#include "ASol2.h"
#include "ASol1.h"
#include "ObjectInput.h"
#include <cmath>

void AimSolver1(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid);


void AimSolver2(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid);

#endif

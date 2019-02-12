#ifndef GENSOLVER_H
#define GENSOLVER_H

#include <iostream>
#include <Eigen/Dense>
#include "ObjectInput.h"
#include "Boundary.h"
#include "EigenSor.h"
#include "BDef.h"

void GenSolver(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid);


#endif

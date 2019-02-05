#ifndef BDEF_H
#define BDEF_H

#include <iostream>
#include <Eigen/Dense>
#include "Boundary.h"
#include "ObjectInput.h"


void BDef(Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid);


#endif

#ifndef SMSD_H
#define SMSD_H

#include <iostream>
#include <Eigen/Dense>
#include "ObjectInput.h"
#include "Boundary.h"
#include "EigenSor.h"
#include "BDef.h"

void SMSD(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid);


#endif 

#ifndef ASOL_H
#define ASOL_H

#include <Eigen/Dense>
#include <cmath>
#include <fstream>
#include "ObjectInput.h"

void ASol(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& asol, Circle& cobj, Plate& pplate, Plate& nplate);

#endif 

#ifndef ASOL2_H
#define ASOL2_H

#include <Eigen/Dense>
#include <cmath>
#include <fstream>
#include <ctime>
#include "ObjectInput.h"

void ASol2(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Circle& cobj, Plate& pplate, Plate& nplate);

#endif 

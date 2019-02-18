#ifndef ASOL_H
#define ASOL_H

#include <Eigen/Dense>
#include <cmath>
#include <fstream>
#include <ctime>
#include "ObjectInput.h"

void ASol(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Circle& cobj, Plate& pplate, Plate& nplate);

#endif 

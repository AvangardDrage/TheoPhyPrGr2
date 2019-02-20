#ifndef ASOL1_H
#define ASOL1_H

#include <Eigen/Dense>
#include <cmath>
#include <fstream>
#include <ctime>
#include "ObjectInput.h"

void ASol1(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& asol, Circle cobj, Shell sobj);

#endif 

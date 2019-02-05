#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <Eigen/Dense>
#include <vector>
#include "ObjectInput.h"

void BGD (Eigen::Matrix<bool, 10, 10>& grid, Box obj);
void BPD (Eigen::Matrix<double, 10, 10>& grid, Box obj);
void CGD (Eigen::Matrix<bool, 10, 10>& grid, Circle obj);
void CPD (Eigen::Matrix<double, 10, 10>& grid, Circle obj);
void PGD (Eigen::Matrix<bool, 10, 10>& grid, Plate obj);
void PPD (Eigen::Matrix<double, 10, 10>& grid, Plate obj);


#endif

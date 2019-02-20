#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include "ObjectInput.h"

void BGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid, Box obj);
//void BPD (Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& grid, Box obj);
void CGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid, Circle obj);
//void CPD (Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& grid, Circle obj);
void PGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid,  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid, Plate obj);
//void PPD (Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& grid, Plate obj);
void SGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid, Shell obj);


#endif

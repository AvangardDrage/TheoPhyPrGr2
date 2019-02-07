#ifndef GAUSS_H
#define GAUSS_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>


void gauss(double dx, double dy, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid);

#endif

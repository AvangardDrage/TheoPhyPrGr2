#ifndef EIGENSOR_H
#define EIGENSOR_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>

void sor(double dx, double dy, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid);


#endif

#ifndef GAUSS_H
#define GAUSS_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>


int gauss(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid);

#endif

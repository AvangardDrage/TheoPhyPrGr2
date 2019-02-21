#ifndef JAC_H
#define JAC_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>


int jac(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid);

#endif

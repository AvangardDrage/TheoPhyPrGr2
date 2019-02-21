#ifndef EIGENSOR_H
#define EIGENSOR_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>
#include <ctime>

int sor(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid);


#endif

#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include "GenSolver.h"
#include "AimSolver.h"
#include "SMSD.h"
int main(int argc, char *argv[])
{
  int n,m, mode;

  char gs;

  // dimensions for the square grid
  m = atoi(argv[1]);
  n = m;

  Eigen::Matrix <bool,Eigen::Dynamic,Eigen::Dynamic> lgrid(m,n); // logic grid
  Eigen::Matrix <double,Eigen::Dynamic,Eigen::Dynamic> pgrid(m,n); // potential grid

  for(int i=0; i<lgrid.rows();i++)
    {
      for(int j=0; j<lgrid.cols(); j++)
	{
	  lgrid(i,j) = true;
	  pgrid(i,j) = 0;
	}
    }

  std::cout << "Which mode would you like to run:" << std::endl;
  std::cout << "[1]: Precision solver based on 1st analytical problem" << std::endl;
  std::cout << "[2]: Precision solver based on 2nd analytical problem" << std::endl;
  std::cout << "[3]: Solve Silicon Microstrip Detector Problem " << std::endl;
  std::cout << "[4]: General solver" << std::endl;
  std::cout <<"Please enter the corresponding number: ";
  std::cin >> mode;

    switch(mode){


    case 1:
      AimSolver1(lgrid, pgrid);
      break;

    case 2 :
      AimSolver2(lgrid, pgrid);
      break;

    case 3:
      SMSD(lgrid, pgrid);
      break;

    case 4 :
      GenSolver(lgrid, pgrid);
      break;

    default :
      std::cout << "You have selected a non-existing mode."<<std::endl<<" Exiting program."<<std::endl<<" Please try again."<<std::endl;
    }

    return 0;
}

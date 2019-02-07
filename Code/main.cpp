#include <iostream>
#include <Eigen/Dense>
#include "ObjectInput.h"
#include "Boundary.h"
#include "EigenSor.h"
#include "BDef.h"

int main()
{
  int n;
  std::cout<< "Enter row and column number: ";
  std::cin >> n;
  Eigen::Matrix <bool,Eigen::Dynamic,Eigen::Dynamic> lgrid(n,n); // logic grid
  Eigen::Matrix <double,Eigen::Dynamic,Eigen::Dynamic> pgrid(n,n); // potential grid
  
  for(int i=0; i<lgrid.rows();i++)
    {
      for(int j=0; j<lgrid.cols(); j++)
	{
	  lgrid(i,j) = true;
	  pgrid(i,j) = 0;
	}
    }

  BDef(lgrid, pgrid);
  
  // std::cout << "Logic grid" << std::endl;
  // std::cout << lgrid << std::endl;
  // std::cout << std::endl;
  // std::cout << "Potential grid" << std::endl;
  // std::cout << pgrid << std::endl;
      

      sor(1, 1, pgrid, lgrid);




  return 0;
}

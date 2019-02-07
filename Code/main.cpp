#include <iostream>
#include <Eigen/Dense>
#include "ObjectInput.h"
#include "Boundary.h"
#include "EigenSor.h"
#include "BDef.h"

int main()
{
  int n,m;
  std::cout<< "Enter number of rows: ";
  std::cin >> m;
  std::cout << "Enter number of columns: ";
  std::cin >> n;
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

  // std::cout << "Logic grid" << std::endl;
  // std::cout << lgrid << std::endl;
  // std::cout << std::endl;
  // std::cout << "Potential grid" << std::endl;
  // std::cout << pgrid << std::endl;
  
  std::cout << "break" << std::endl;

  BDef(lgrid, pgrid);
  
  std::cout << "Logic grid" << std::endl;
  std::cout << lgrid << std::endl;
  std::cout << std::endl;
  std::cout << "Potential grid" << std::endl;
  std::cout << pgrid << std::endl;
      

  sor(1, 1, pgrid, lgrid);




  return 0;
}

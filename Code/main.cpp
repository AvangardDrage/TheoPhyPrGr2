#include <iostream>
#include <Eigen/Dense>
#include "GenSolver.h"
#include "AimSolver.h"
int main()
{
  int n,m, mode;
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

  std::cout << "Which mode would you like to run:" << std::endl;
  std::cout << "[1]: Precision solver based on 2nd analytical problem" << std::endl;
  std::cout << "[2]: General solver" << std::endl<<"Please enter the corresponding number: ";
  std::cin >> mode;

    switch(mode){
      
    case 1 :
      AimSolver(lgrid, pgrid);
      char gs;
      std::cout << "Would you like to proceed to use general solver mode?[(y)es or (n)o]: ";
      std::cin >> gs;
      if(gs=='n')
	{
	  break;
	}
      else if(gs!='y')
	{
	  std::cout << "Wrong input. Exiting Program" << std::endl;
	  break;
	}
    case 2 :
      // reinitialisation of matrix in case [1]->[2]
      for(int i=0; i<lgrid.rows();i++)
	{
	  for(int j=0; j<lgrid.cols(); j++)
	    {
	      lgrid(i,j) = true;
	      pgrid(i,j) = 0;
	    }
	}

      GenSolver(lgrid, pgrid);
      break;
    default :
      std::cout << "You have selected a non-existing mode."<<std::endl<<" Exiting program."<<std::endl<<" Please try again."<<std::endl;
    }



  // std::cout << "Logic grid" << std::endl;
  // std::cout << lgrid << std::endl;
  // std::cout << std::endl;
  // std::cout << "Potential grid" << std::endl;
  // std::cout << pgrid << std::endl;
  
  //std::cout << "break" << std::endl;

  // BDef(lgrid, pgrid);
  
  // std::cout << "Logic grid" << std::endl;
  // std::cout << lgrid << std::endl;
  // std::cout << std::endl;
  // std::cout << "Potential grid" << std::endl;
  // std::cout << pgrid << std::endl;
      

  // sor(1, 1, pgrid, lgrid);




  return 0;
}

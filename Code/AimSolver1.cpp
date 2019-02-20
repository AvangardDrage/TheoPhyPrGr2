#include "AimSolver.h"
#include <fstream>
#include <iomanip>

void AimSolver1(Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid)
{
  std::ofstream edat;
  
  edat.open("a_sol_err.dat");
  
  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> nsol(pgrid.rows(),pgrid.cols());
  nsol = pgrid; // copy pgrid matrix into a separate numerical solution matrix

  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> asol(pgrid.rows(),pgrid.cols());
  asol = pgrid;

 Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> err(pgrid.rows(),pgrid.cols());

  Circle cobj; // centre cylinder
  Shell sobj;  // Outer Shell

  int rcircle;
  int rinner;
  int router;
  double ptntl;
  

  /* Centre Cylinder */
  cobj.centre[0] = static_cast<int>((lgrid.rows()-1)/2);
  cobj.centre[1] = static_cast<int>((lgrid.cols()-1)/2);

  std::cout << "Please specify radius of the centre cylinder: ";
  std::cin >> rcircle;
  cobj.radius = rcircle;
  cobj.potential = 0;
  CGD(lgrid, nsol, cobj);

  /* Outer Shell */ 
  std::cout << "Please specify the inner radius of the outer shell: ";
  std::cin >> rinner;
  std::cout << "Please specify the outer radius of the outer shell: ";
  std::cin >> router;
  std::cout << "Please specify the potential of the outer shell: ";
  std::cin >> ptntl;
 
  sobj.centre[0] = static_cast<int>((lgrid.rows()-1)/2);
  sobj.centre[1] = static_cast<int>((lgrid.cols()-1)/2);

  sobj.iradius = rinner;
  sobj.oradius = router;
  sobj.potential = ptntl;

  SGD(lgrid, nsol, sobj);
  

  asol = nsol; // copy pgrid matrix into a separate numerical solution matrix

  /* Calculations */ 
  
  // numerical
  sor(nsol, lgrid);

  // analtical
  ASol1(asol, cobj, sobj);

  for(int i=0;i<lgrid.rows();i++)
    {
      for(int j=0;j<lgrid.cols();j++)
	{
	  if(lgrid(i,j))
	    {
	      err(i,j)= sqrt(pow((asol(i,j)-nsol(i,j)),2));
	    }		    
	  else
	    {
	      err(i,j) = 0;
	    }
	}
    }
  
  double nze = 0.0;
  double nzs = 0.0;

  for(int i=0;i<err.rows();i++)
    {
      for(int j=0;j<err.cols();j++)
	{
	  if(lgrid(i,j) || (j!=cobj.centre[0]))
	    {
	      nzs = nzs+err(i,j);
	      nze++;
	    }
	  edat << j << " " << i << " " << err(i,j) << std::endl;
	}
    }

  std::cout << "Precision of the Eigen SOR method used in general solver: " << nzs/nze << " +- " << err.maxCoeff()-(nzs/nze) << std::endl;

}

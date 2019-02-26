#include "AimSolver.h"
#include <fstream>
#include <iomanip>

void AimSolver1(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid)
{
  std::ofstream edat;

  edat.open("a_sol_err.dat");

  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> asol(pgrid.rows(),pgrid.cols());

  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> nsol(pgrid.rows(),pgrid.cols());
  nsol = pgrid; // copy pgrid matrix into a separate numerical solution matrix

  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> err(pgrid.rows(),pgrid.cols());
  err  = pgrid; // create an error matrix based on pgrid matrix

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


  asol = nsol; // copy nsol matrix into a separate numerical solution matrix

  /* Calculations */

  sor(nsol, lgrid);  // numerical
  ASol1(asol, cobj, sobj);   // analytical



  //error
  double err_sum = 0;

  for(int i=0;i<lgrid.rows();i++)
	{
	  for(int j=0;j<lgrid.cols();j++)
		{

	   err(i,j)= fabs(asol(i,j)-nsol(i,j));
	   err_sum += err(i,j);

	   edat << j << " " << i << " " << err(i,j) << std::endl;

		}
	}

  double avg_err = err_sum/(err.rows()*err.cols());

  std::cout << "Average error per grid point of the SOR method: " << avg_err << " [+" << err.maxCoeff()-avg_err << ", - " << avg_err-err.minCoeff() << "]"<< std::endl;

  edat.close();
}

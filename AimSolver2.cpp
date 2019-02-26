#include "AimSolver.h"
#include <fstream>
#include <iomanip>

void AimSolver2(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid)
{
 std::ofstream edat;

 edat.open("a_sol_err.dat");

 Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> asol(pgrid.rows(),pgrid.cols());

 Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> nsol(pgrid.rows(),pgrid.cols());
 nsol = pgrid; // copy pgrid matrix into a separate numerical solution matrix

 Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> err(pgrid.rows(),pgrid.cols());
 err  = pgrid; // create an error matrix based on pgrid matrix

 Circle cobj;  // centre wire
 Plate pplate; // positive plate
 Plate nplate; // negative plate
 int r;
 int dist;
 double ptntl; // potential
 int endp;

 /* Centre Cylinder */

 cobj.centre[0] = static_cast<int>((lgrid.rows()-1)/2);
 cobj.centre[1] = static_cast<int>((lgrid.cols()-1)/2);


 std::cout << "Please specify radius of the centre circle: ";
 std::cin >> r;
 cobj.radius = r;
 cobj.potential = 0;
 CGD(lgrid, nsol,cobj);

   /* Side Plates */
 std::cout << "Please specify the distance between two plates: ";
 std::cin >> dist;
 std::cout << "Please specify the potential of the plates (absolute value): ";
 std::cin >> ptntl;


 endp = static_cast<int>((lgrid.cols()-1-dist)/2);

 pplate.centre[0] = endp;
 pplate.direction[0] = true; // vertical
 pplate.direction[1] = false; // to the left
 pplate.potential = ptntl;
 PGD(lgrid, nsol, pplate);

 nplate.centre[0] = lgrid.cols()-1-endp;
 nplate.direction[0] = true; // vertical
 nplate.direction[1] = true; // to the right
 nplate.potential = -ptntl;
 PGD(lgrid, nsol, nplate);

 asol = nsol; // copy nsol matrix into a separate analytical solution matrix

 /* Calculations */

 sor(nsol,lgrid); // numerical method
 ASol2(asol,cobj,pplate,nplate); // analytical method



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

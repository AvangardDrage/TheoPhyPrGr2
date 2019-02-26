#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include "AimSolver.h"

int main(int argc, char **argv) {

  std::ofstream outfile;
  outfile.open("err_compar2.dat");

  int rows = atoi(argv[1]), cols = atoi(argv[2]), r, dist, endp;
  double ptntl;
  int i, j, n, half_sweep, isw, jsw;
  int iter = 1;
  int max_iter = 20000;
  double tol = 1e-6;
  double resid, rnorm, avg_norm;

  Circle cobj;  // centre wire
  Plate pplate; // positive plate
  Plate nplate; // negative plate

  std::cout << "Please specify radius of the centre circle: ";
  std::cin >> r;
    /* Side Plates */
  std::cout << "Please specify the distance between two plates: ";
  std::cin >> dist;
  std::cout << "Please specify the potential of the plates (absolute value): ";
  std::cin >> ptntl;


  Eigen::Matrix <bool,Eigen::Dynamic,Eigen::Dynamic> lgrid(rows,cols); // logic grid
  Eigen::Matrix <double,Eigen::Dynamic,Eigen::Dynamic> pgrid(rows,cols); // potential grid
  double dx = 1/static_cast<double>(pgrid.cols());
  double dy = 1/static_cast<double>(pgrid.rows());

  for(int i=0; i<lgrid.rows();i++)
    {
      for(int j=0; j<lgrid.cols(); j++)
  {
    lgrid(i,j) = true;
    pgrid(i,j) = 0;
  }
    }

  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> asol(pgrid.rows(),pgrid.cols());

  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> nsol(pgrid.rows(),pgrid.cols());
  nsol = pgrid; // copy pgrid matrix into a separate numerical solution matrix

  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> err(pgrid.rows(),pgrid.cols());
  err  = pgrid; // create an error matrix based on pgrid matrix

  /* Centre Cylinder */

  cobj.centre[0] = static_cast<int>((lgrid.rows()-1)/2);
  cobj.centre[1] = static_cast<int>((lgrid.cols()-1)/2);

  cobj.radius = r;
  cobj.potential = 0;
  CGD(lgrid, nsol,cobj);

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

  ASol2(asol,cobj,pplate,nplate); // analytical method


  // Spectral radius p of the Jacobi iteration for a rectangular (rows) x (cols) grid
  // and optimal value for the relaxation parameter w
  double p = (cos(M_PI/cols) + pow((dx/dy),2) * cos(M_PI/rows)) / (1.0 + pow((dx/dy),2));
  double w = 2.0 / (1 + sqrt(1-p*p));

 // Iterate until convergence or until the maximum number of iterations is encountered
  for (n = 0; n < max_iter; n++)
    {
      rnorm = 0.0;
      avg_norm = 0.0;
      isw = 0;

      // Red-black ordering SOR
      for (half_sweep = 1; half_sweep < 3; half_sweep++)
	    {
	  	  jsw=isw;

		  for (i = 0; i < rows; i++)
		    {
		      for (j = jsw; j < cols; j+=2)
			    {

				  // Apply the scheme for non-boundary points; boundary points are left unchanged
				  if (lgrid(i,j))
					{

				      /*
					Since the SOR scheme cannot modify the points at
					each side of the grid, leaving them unchanged
					would be equivalent to closing the system in a box
					set at ground. Therefore, computing approximations
					for them by considering the average of the available
					surrounding points will simulate free space
				      */

				      // Compute approximations for corner points
              if (i == 0 && j == 0)
					{
					  resid = 0.25*(nsol(i+1,j) + nsol(i,j) + nsol(i,j+1) + nsol(i,j) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);
					}
				      else if (i == 0 && j == cols-1)
					{
					  resid = 0.25*(nsol(i+1,j) + nsol(i,j) + nsol(i,j) + nsol(i,j-1) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);
					}
				      else if (i == rows-1 && j == 0)
					{
					  resid = 0.25*(nsol(i,j) + nsol(i-1,j) + nsol(i,j+1) + nsol(i,j) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);
					}
				      else if (i == rows-1 && j == cols-1)
					{
					  resid = 0.25*(nsol(i,j) + nsol(i-1,j) + nsol(i,j) + nsol(i,j-1) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);

					  // Compute approximations for points on the grid sides
					}
				      else if (i == 0)
					{
					  resid = 0.25*(nsol(i+1,j) + nsol(i,j) + nsol(i,j+1) + nsol(i,j-1) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);
					}
				      else if (i == rows-1)
					{
					  resid = 0.25*(nsol(i,j) + nsol(i-1,j) + nsol(i,j+1) + nsol(i,j-1) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);
					}
				      else if (j == 0)
					{
					  resid = 0.25*(nsol(i+1,j) + nsol(i-1,j) + nsol(i,j+1) + nsol(i,j) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);
					}
				      else if (j == cols-1)
					{
					  resid = 0.25*(nsol(i+1,j) + nsol(i-1,j) + nsol(i,j) + nsol(i,j-1) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);

					  // Compute approximations for inner points
					}
				      else
					{
					  resid = 0.25*(nsol(i+1,j) + nsol(i-1,j) + nsol(i,j+1) + nsol(i,j-1) - 4.0 * nsol(i,j));
					  nsol(i,j) += w * resid;
					  rnorm += fabs(resid);
					}

					}
			    }
	        // Change sweep ordering
	        jsw = 1-jsw;
		    }
		isw = 1-isw;
		}

	  // Test convergence with norm of the residual per grid point
	  avg_norm = rnorm / (cols * rows);

  if (avg_norm >= tol)
	{
    //error
    double err_sum = 0;

    for(int i=0;i<lgrid.rows();i++)
    {
      for(int j=0;j<lgrid.cols();j++)
      {

       err(i,j)= fabs(asol(i,j)-nsol(i,j));
       err_sum += err(i,j);

      }
    }

    double avg_err = err_sum/(err.rows()*err.cols());

    outfile << iter << " " << avg_err << std::endl;

	  iter++;


	  if (iter > max_iter)
	    {
		   std::cout << "Method does not converge in " << max_iter << " iterations" << w << std::endl;
		   break;
		}
	}
      else
	{
	  std::cout << "Method converges in " << iter << " iterations and w = " << w << std::endl;

	  break;
	}
  }


  outfile.close();
  return 0;
}

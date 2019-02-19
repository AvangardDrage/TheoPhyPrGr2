#include "EigenSor.h"

//using namespace std;
// using namespace Eigen;

void sor(double dx, double dy, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid)
{

	/*
		Application of successive over relaxation to the Laplace equation
		with red-black ordering and Chebyshev acceleration.
		The function requires an initial guess u (usually zero) of the solution,
		with size [xsize, ysize], and fixed boundaries bound from external code.
	*/

  std::ofstream outfile;
  outfile.open("n_SOR.dat");
  
  int i, j, n, half_sweep, isw, jsw;
  int iter = 1;
  int max_iter = 20000;
  int ysize = pgrid.rows(), xsize = pgrid.cols();
  double tol = 1e-6;		// The tolerance sets the digits precision of the solution
  double resid, rnorm, avg_norm, Ex, Ey;

  // Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(xsize, 0, xsize*dx);
  // Eigen::VectorXd y = Eigen::VectorXd::LinSpaced(ysize, 0, ysize*dy);

  Eigen::MatrixXd grad= Eigen::MatrixXd::Zero(ysize,xsize);

  // Spectral radius of the Jacobi iteration for a rectangular (xsize) x (ysize) grid
  double p = (cos(M_PI/xsize) + (dx/dy)*(dx/dy) * cos(M_PI/ysize)) / (1.0 + (dx/dy)*(dx/dy));
  double w = 1.0;		// Assume the relaxation parameter is one
  
  int bp_s=clock();
 
 // Iterate until convergence
  for (n = 0; n < max_iter; n++)
    {
    
      rnorm = 0.0;
      avg_norm = 0.0;
      isw = 0;
    
      
      // Red-black ordering SOR
      for (half_sweep = 1; half_sweep < 3; half_sweep++)
	{
	  jsw=isw;
      
	  for (i = 0; i < ysize; i++)
	    {
	      for (j = jsw; j < xsize; j+=2)
		{
	  
		  // Apply the scheme for non-boundary points
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
			  resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
			} 
		      else if (i == 0 && j == xsize-1)
			{
			  resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
			}
		      else if (i == ysize-1 && j == 0)
			{
			  resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
			} 
		      else if (i == ysize-1 && j == xsize-1)
			{
			  resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
			  
			  // Compute approximations for points on the grid sides
			}
		      else if (i == 0)
			{
			  resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
			} 
		      else if (i == ysize-1)
			{
			  resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
			}
		      else if (j == 0)
			{
			  resid = pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
			}
		      else if (j == xsize-1)
			{
			  resid = pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
	      
			  // Compute approximations for inner points
			}
		      else
			{
			  resid = pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
			  pgrid(i,j) += w * resid * 0.25;
			  rnorm += fabs(resid);
			}
		      
	    
		  //     // Leave boundary points unchanged
		    }
		  // else 
		  //   {
		  //     pgrid(i,j) = bound(i,j);
		  //   }
		}
	      // Change sweep ordering
	      jsw = 1-jsw;
	    }
	  isw = 1-isw;
	  
	  // Improve value of w towards optimal value
	  if (n == 0  &&  half_sweep == 1)
	    {
	      w = 1.0 / (1.0 - 0.5 * p*p);
	    }
	  else
	    {
	      w = 1.0 / (1.0 - 0.25 * p*p * w);
	    }
	}
    
      // Test convergence with norm of the residual per grid point
      avg_norm = rnorm / (xsize * ysize);
      
      if (avg_norm >= tol)
	{
	  iter++;
	}
      else
	{
	  int ep_s = clock();
	  std::cout << "Method converges in " << iter << " iterations and w = " << w << std::endl;
	  std::cout << "Execution time: " << (ep_s - bp_s)/double(CLOCKS_PER_SEC)*1000 << " microseconds" << std::endl;
	  break;
	}
    }
  


  /*
    Compute electric field components by central difference approximation.
    No calculation needed for points on the sides of the grid, since E=0
    outside capacitors and grad is initialised to zero.
  */
  
  for (i = 1; i < ysize-1; i++)
    {
      for (j = 1; j < xsize-1; j++)
	{
	  
	  Ex= 0.5*(pgrid(i,j+1)-pgrid(i,j-1))/dx;
	  Ey= 0.5*(pgrid(i+1,j)-pgrid(i-1,j))/dy;
	  grad(i,j)= sqrt( pow(Ex, 2) + pow(Ey, 2));
	  
	}
    }
  
  // Appends data to file for plotting
  
  for (i = 0; i < ysize; i++ )
    {
      for (j = 0; j < xsize; j++) 
	{
	  outfile << j << " " << i << " " << pgrid(i,j) << " " << grad(i,j) << std::endl;
	}
    }
  
  outfile.close();

}

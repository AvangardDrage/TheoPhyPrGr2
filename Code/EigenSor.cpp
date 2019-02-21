#include "EigenSor.h"


int sor(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid)
{

	/*
		Application of successive over relaxation (SOR) to the Laplace equation
		with red-black ordering.

		The function requires an initial guess pgrid (usually zero) of the solution,
		that also contains the potential values for any specified objects
		(internal boundary points), and a logic grid lgrid that represents the object
		position within pgrid as False boolean data type.
	*/

  std::ofstream outfile1;
  std::ofstream outfile2;
  outfile1.open("n_SOR.dat");
  outfile2.open("n_SOR_quiver.dat");


  int i, j, n, half_sweep, isw, jsw;
  int iter = 1;
  int max_iter = 20000;
  int rows = pgrid.rows(), cols = pgrid.cols();

  double dx = 1/static_cast<double>(pgrid.cols());
  double dy = 1/static_cast<double>(pgrid.rows());
  double tol = 1e-6;
  double resid, rnorm, avg_norm;


  Eigen::MatrixXd grad = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd Ex = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd Ey = Eigen::MatrixXd::Zero(rows,cols);


  // Spectral radius p of the Jacobi iteration for a rectangular (rows) x (cols) grid
  // and optimal value for the relaxation parameter w
  double p = (cos(M_PI/cols) + pow((dx/dy),2) * cos(M_PI/rows)) / (1.0 + pow((dx/dy),2));
  double w = 2.0 / (1 + sqrt(1-p*p));


  int bp_s=clock();

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
					  resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
					  pgrid(i,j) += w * resid * 0.25;
					  rnorm += fabs(resid);
					}
				      else if (i == 0 && j == cols-1)
					{
					  resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
					  pgrid(i,j) += w * resid * 0.25;
					  rnorm += fabs(resid);
					}
				      else if (i == rows-1 && j == 0)
					{
					  resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
					  pgrid(i,j) += w * resid * 0.25;
					  rnorm += fabs(resid);
					}
				      else if (i == rows-1 && j == cols-1)
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
				      else if (i == rows-1)
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
				      else if (j == cols-1)
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
	  iter++;

	  if (iter > max_iter)
	    {
		   std::cout << "Method does not converge in " << max_iter << " iterations" << w << std::endl;
		   break;
		}
	}
      else
	{
	  int ep_s = clock();
	  std::cout << "Method converges in " << iter << " iterations and w = " << w << std::endl;
	  std::cout << "Execution time: " << (ep_s - bp_s)/double(CLOCKS_PER_SEC) << " seconds" << std::endl;
	  break;
	}
  }



  /*
    Compute electric field components by central difference approximation.
    No calculation needed for points on the sides of the grid, since E=0
    outside capacitors and grad is initialised to zero.
  */

  for (i = 1; i < rows-1; i++)
    {
      for (j = 1; j < cols-1; j++)
	{

	  Ex(i,j) = - 0.5 * (pgrid(i,j+1) - pgrid(i,j-1)) / dx;
	  Ey(i,j) = - 0.5 * (pgrid(i+1,j) - pgrid(i-1,j)) / dx;
	  grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));

	}
    }


  // Append data to file for plotting
  for (i = 0; i < rows; i++)
    {
      for (j = 0; j < cols; j++)
	{
	  outfile1 << j << " " << i << " " << pgrid(i,j) << " " << grad(i,j) << std::endl;
	}
    }

  // Append smaller amount of data for quiver plot
  for (i = 0; i < rows; i += static_cast<int>(0.05*rows))
	{
	  for (j = 0; j < cols; j += static_cast<int>(0.05*cols))
    {
	  outfile2 << j << " " << i << " " << Ex(i,j) << " " << Ey(i,j) << std::endl;
    }
	}

  outfile1.close();
  outfile2.close();

  return iter;

}

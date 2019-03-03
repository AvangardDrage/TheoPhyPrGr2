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


  Eigen::MatrixXd grad = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd Ex = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd Ey = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd resid = Eigen::MatrixXd::Zero(rows,cols);

  // Spectral radius p of the Jacobi iteration for a rectangular (rows) x (cols) grid
  // and optimal value for the relaxation parameter w
  double p = (cos(M_PI/cols) + pow((dx/dy),2) * cos(M_PI/rows)) / (1.0 + pow((dx/dy),2));
  double w = 2.0 / (1 + sqrt(1-p*p));


  int bp_s=clock();

 // Iterate until convergence or until the maximum number of iterations is encountered
  for (n = 0; n < max_iter; n++)
    {
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
					  resid(i,j) = (pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j))/2;
					  pgrid(i,j) += w * resid(i,j);
					}
				      else if (i == 0 && j == cols-1)
					{
					  resid(i,j) = (pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j))/2;
					  pgrid(i,j) += w * resid(i,j);
					}
				      else if (i == rows-1 && j == 0)
					{
					  resid(i,j) = (pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j))/2;
					  pgrid(i,j) += w * resid(i,j);
					}
				      else if (i == rows-1 && j == cols-1)
					{
					  resid(i,j) = (pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j))/2;
					  pgrid(i,j) += w * resid(i,j);

					  // Compute approximations for points on the grid sides
					}
				      else if (i == 0)
					{
					  resid(i,j) = (pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j))/3;
					  pgrid(i,j) += w * resid(i,j);
					}
				      else if (i == rows-1)
					{
					  resid(i,j) = (pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j))/3;
					  pgrid(i,j) += w * resid(i,j);
					}
				      else if (j == 0)
					{
					  resid(i,j) = (pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j))/3;
					  pgrid(i,j) += w * resid(i,j);
					}
				      else if (j == cols-1)
					{
					  resid(i,j) = (pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j))/3;
					  pgrid(i,j) += w * resid(i,j);

					  // Compute approximations for inner points
					}
				      else
					{
					  resid(i,j) = 0.25*(pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j));
					  pgrid(i,j) += w * resid(i,j);
					}

					}
			    }
	        // Change sweep ordering
	        jsw = 1-jsw;
		    }
		isw = 1-isw;
		}

	  // Test convergence with norm of the resid(i,j)ual per grid point

      if (fabs(resid.maxCoeff()) >= tol)
	{
	  iter++;

	  if (iter > max_iter)
	    {
		   std::cout << "Method does not converge in " << max_iter << " iterations" << std::endl;
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
  for (i = 0; i < rows; i++)
	{
	  for (j = 0; j < cols; j++)
	    {
		  if (!lgrid(i,j))      //boundaries
		{
		  grad(i,j) = 0;
		}
      else if (i == 0 && j == 0)    //corners
       {
         Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j))/dx;
   		   Ey(i,j) = -(pgrid(i+1,j) - pgrid(i,j))/dy;
   		   grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
       }
           else if (i == 0 && j == cols-1)
       {
         Ex(i,j) = -(pgrid(i,j) - pgrid(i,j-1))/dx;
   		   Ey(i,j) = -(pgrid(i+1,j) - pgrid(i,j))/dy;
   		   grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
       }
           else if (i == rows-1 && j == 0)
       {
         Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j))/dx;
   		   Ey(i,j) = -(pgrid(i,j) - pgrid(i-1,j))/dy;
   		   grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
       }
           else if (i == rows-1 && j == cols-1)
       {
         Ex(i,j) = -(pgrid(i,j) - pgrid(i,j-1))/dx;
   		   Ey(i,j) = -(pgrid(i,j) - pgrid(i-1,j))/dy;
   		   grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }
        else if (i == 0)    //sides
      {
        Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j-1))/(2*dx);
        Ey(i,j) = -(pgrid(i+1,j) - pgrid(i,j))/dy;
        grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }
          else if (i == rows-1)
      {
        Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j-1))/(2*dx);
        Ey(i,j) = -(pgrid(i,j) - pgrid(i-1,j))/dy;
        grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }
          else if (j == 0)
      {
        Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j))/dx;
        Ey(i,j) = -(pgrid(i+1,j) - pgrid(i-1,j))/(2*dy);
        grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }
          else if (j == cols-1)
      {
        Ex(i,j) = -(pgrid(i,j-1) - pgrid(i,j))/dx;
        Ey(i,j) = -(pgrid(i+1,j) - pgrid(i-1,j))/(2*dy);
        grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }
          else if (i == 1)      //2nd sides
      {
        Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j-1))/(2*dx);
        Ey(i,j) = -(pgrid(i+1,j) - pgrid(i-1,j))/(2*dy);
        grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }
          else if (i == rows-2)
      {
        Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j-1))/(2*dx);
        Ey(i,j) = -(pgrid(i+1,j) - pgrid(i-1,j))/(2*dy);
        grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }
          else if (j == 1)
      {
        Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j-1))/(2*dx);
        Ey(i,j) = -(pgrid(i+1,j) - pgrid(i-1,j))/(2*dy);
        grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }
          else if (j == cols-2)
      {
        Ex(i,j) = -(pgrid(i,j+1) - pgrid(i,j-1))/(2*dx);
        Ey(i,j) = -(pgrid(i+1,j) - pgrid(i-1,j))/(2*dy);
        grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
      }

  		  else    //interior
		{

		  Ex(i,j) = -(-pgrid(i,j+2) + 8*pgrid(i,j+1) - 8*pgrid(i,j-1) + pgrid(i,j-2))/(12*dx);
		  Ey(i,j) = -(-pgrid(i+2,j) + 8*pgrid(i+1,j) - 8*pgrid(i-1,j) + pgrid(i-2,j))/(12*dy);
		  grad(i,j) = sqrt(pow(Ex(i,j), 2) + pow(Ey(i,j), 2));
		}
	    }
	}



  // Append data to file for plotting
  for (i = 0; i < rows; i++)
    {
      for (j = 0; j < cols; j++)
	{
	  outfile1 << j << " " << i << " " << pgrid(i,j) << " " << grad(i,j) << " " << Ex(i,j) << " " << Ey(i,j) << std::endl;
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

#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include "ObjectInput.h"
#include "Boundary.h"
#include "BDef.h"
#include "EigenSor.h"
#include "AimSolver.h"

int main(void){

    std::ofstream outfile;
    outfile.open("grid_err1.dat");

    for (int N = 11; N <=401; N += 3) {

      Eigen::Matrix <bool,Eigen::Dynamic,Eigen::Dynamic> lgrid(N,N); // logic grid
      Eigen::Matrix <double,Eigen::Dynamic,Eigen::Dynamic> pgrid(N,N); // potential grid

      for(int i=0; i<lgrid.rows();i++)
        {
          for(int j=0; j<lgrid.cols(); j++)
            {
              lgrid(i,j) = true;
              pgrid(i,j) = 0;
            }
        }

      int i, j, n, half_sweep, isw, jsw;
      int iter = 1;
      int max_iter = 20000;
      int rows = pgrid.rows(), cols = pgrid.cols();

      double dx = 1/static_cast<double>(pgrid.cols());
      double dy = 1/static_cast<double>(pgrid.rows());
      double tol = 1e-6;
      double resid, rnorm, avg_norm;

      Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> asol(pgrid.rows(),pgrid.cols());

      Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> nsol(pgrid.rows(),pgrid.cols());
      nsol = pgrid; // copy pgrid matrix into a separate numerical solution matrix

      Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> err(pgrid.rows(),pgrid.cols());
      err  = pgrid; // create an error matrix based on pgrid matrix

      Circle cobj; // centre cylinder
      Shell sobj;  // Outer Shell

      int rcircle=static_cast<int>(20*N/201);
      int rinner=static_cast<int>(85*N/201);
      int router=static_cast<int>(95*N/201);
      double ptntl=20;


      /* Centre Cylinder */
      cobj.centre[0] = static_cast<int>((lgrid.rows()-1)/2);
      cobj.centre[1] = static_cast<int>((lgrid.cols()-1)/2);

      cobj.radius = rcircle;
      cobj.potential = 0;
      CGD(lgrid, nsol, cobj);

      sobj.centre[0] = static_cast<int>((lgrid.rows()-1)/2);
      sobj.centre[1] = static_cast<int>((lgrid.cols()-1)/2);

      sobj.iradius = rinner;
      sobj.oradius = router;
      sobj.potential = ptntl;

      SGD(lgrid, nsol, sobj);


      asol = nsol; // copy nsol matrix into a separate numerical solution matrix
      ASol1(asol, cobj, sobj);   // analytical

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

        outfile << N << " " <<  avg_err << std::endl;

    }

    outfile.close();
    return 0;
}

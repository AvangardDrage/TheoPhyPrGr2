#include <iostream>
#include <cstdlib>
#include <fstream>
#include <Eigen/Dense>
#include "ObjectInput.h"
#include "Boundary.h"
#include "BDef.h"

int main() {

	std::ofstream outfile1, outfile2, outfile3;
	outfile1.open("time1.dat");
  outfile2.open("time2.dat");
  outfile3.open("time3.dat");

	Plate pplate; // positive plate
	Plate nplate; // negative plate

  for (int N=50;N<=250;N+=5){

	    Eigen::Matrix <bool,Eigen::Dynamic,Eigen::Dynamic> lgrid(N,N); // logic grid
	    Eigen::Matrix <double,Eigen::Dynamic,Eigen::Dynamic> pgrid(N,N); // potential grid
      Eigen::Matrix <double,Eigen::Dynamic,Eigen::Dynamic> u1(N,N);

	    for(int i=0; i<lgrid.rows();i++) {
	    	for(int j=0; j<lgrid.cols(); j++) {
		  		lgrid(i,j) = true;
		  		pgrid(i,j) = 0;
			}
	    }

		// Create a system of two parallel plates capacitor
		pplate.centre[0] = 0;  // on the left side
		pplate.direction[0] = true;  // vertical
		pplate.direction[1] = false;  // to the left
		pplate.potential = 10;
		PGD(lgrid, pgrid, pplate);

		nplate.centre[0] = pgrid.cols()-1;  // on the right side
		nplate.direction[0] = true;  // vertical
		nplate.direction[1] = true;  // to the right
		nplate.potential = -10;
		PGD(lgrid, pgrid, nplate);

    int i, j, n, half_sweep, isw, jsw;
    int iter = 1;
    int max_iter = 50000;
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

        //int ep_s=0;
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
      outfile1 << N << " " << (ep_s - bp_s)/double(CLOCKS_PER_SEC) << std::endl;

      break;
    }
    }

    for(int i=0; i<lgrid.rows();i++) {
        for(int j=0; j<lgrid.cols(); j++) {
          lgrid(i,j) = true;
          pgrid(i,j) = 0;
      }
      }

    // Create a system of two parallel plates capacitor
    pplate.centre[0] = 0;  // on the left side
    pplate.direction[0] = true;  // vertical
    pplate.direction[1] = false;  // to the left
    pplate.potential = 10;
    PGD(lgrid, pgrid, pplate);

    nplate.centre[0] = pgrid.cols()-1;  // on the right side
    nplate.direction[0] = true;  // vertical
    nplate.direction[1] = true;  // to the right
    nplate.potential = -10;
    PGD(lgrid, pgrid, nplate);
    iter = 0;

    int bp_s1=clock();
    for (n = 0; n < max_iter; n++)  {

      rnorm = 0.0;
      avg_norm = 0.0;
      u1 = pgrid;


        for (i = 0; i < rows; i++) {
          for (j = 0; j < cols; j++) {

            if (lgrid(i,j)) {

              if (i == 0 && j == 0) {
                resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
                pgrid(i,j) += resid * 0.25;
                rnorm += fabs(resid);
              } else if (i == 0 && j == cols-1) {
                  resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
                  pgrid(i,j) += resid * 0.25;
                  rnorm += fabs(resid);
              } else if (i == rows-1 && j == 0) {
                  resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
                  pgrid(i,j) += resid * 0.25;
                  rnorm += fabs(resid);
              } else if (i == rows-1 && j == cols-1) {
                  resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
                  pgrid(i,j) += resid * 0.25;
                  rnorm += fabs(resid);

              } else if (i == 0) {
                  resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
                  pgrid(i,j) += resid * 0.25;
                  rnorm += fabs(resid);
              } else if (i == rows-1) {
                  resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
                  pgrid(i,j) += resid * 0.25;
                  rnorm += fabs(resid);
              } else if (j == 0) {
                  resid = pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
                  pgrid(i,j) += resid * 0.25;
                  rnorm += fabs(resid);
              } else if (j == cols-1) {
                  resid = pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
                  pgrid(i,j) += resid * 0.25;
                  rnorm += fabs(resid);

              } else {
                  resid = u1(i+1,j) + pgrid(i-1,j) + pgrid(i,j+1) + u1(i,j-1) - 4.0 * u1(i,j);
                  pgrid(i,j) += resid * 0.25;
                  rnorm += fabs(resid);
              }

            }
          }
        }

      avg_norm = rnorm / (cols * rows);

      if (avg_norm >= tol)
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
        int ep_s1 = clock();
        std::cout << "Method converges in " << iter << " iterations" << std::endl;
        outfile2 << N << " " << (ep_s1 - bp_s1)/double(CLOCKS_PER_SEC) << std::endl;
        break;
      }
    }

    for(int i=0; i<lgrid.rows();i++) {
        for(int j=0; j<lgrid.cols(); j++) {
          lgrid(i,j) = true;
          pgrid(i,j) = 0;
      }
      }

    // Create a system of two parallel plates capacitor
    pplate.centre[0] = 0;  // on the left side
    pplate.direction[0] = true;  // vertical
    pplate.direction[1] = false;  // to the left
    pplate.potential = 10;
    PGD(lgrid, pgrid, pplate);

    nplate.centre[0] = pgrid.cols()-1;  // on the right side
    nplate.direction[0] = true;  // vertical
    nplate.direction[1] = true;  // to the right
    nplate.potential = -10;
    PGD(lgrid, pgrid, nplate);
    iter = 0;
    int bp_s2=clock();
  	// Iterate until convergence
  	for (n = 0; n < max_iter; n++)  {

  		rnorm = 0.0;
  		avg_norm = 0.0;
  		u1 = pgrid;

  			for (i = 0; i < rows; i++) {
  				for (j = 0; j < cols; j++) {

  					// Apply the scheme for non-boundary points
  					if (lgrid(i,j)) {

  						// Compute approximations for corner points
  						if (i == 0 && j == 0) {
  							resid = u1(i+1,j) + u1(i,j) + u1(i,j+1) + u1(i,j) - 4.0 * u1(i,j);
  							pgrid(i,j) = u1(i,j) + resid * 0.25;
  							rnorm += fabs(resid);
  						} else if (i == 0 && j == cols-1) {
  							resid = u1(i+1,j) + u1(i,j) + u1(i,j) + u1(i,j-1) - 4.0 * u1(i,j);
  							pgrid(i,j) = u1(i,j) + resid * 0.25;
  							rnorm += fabs(resid);
  						} else if (i == rows-1 && j == 0) {
  							resid = u1(i,j) + u1(i-1,j) + u1(i,j+1) + u1(i,j) - 4.0 * u1(i,j);
  							pgrid(i,j) = u1(i,j) + resid * 0.25;
  							rnorm += fabs(resid);
  						} else if (i == rows-1 && j == cols-1) {
  							resid = u1(i,j) + u1(i-1,j) + u1(i,j) + u1(i,j-1) - 4.0 * u1(i,j);
  							pgrid(i,j) = u1(i,j) + resid * 0.25;
  							rnorm += fabs(resid);

  						// Compute approximations for points on the grid sides
  						} else if (i == 0) {
  							resid = u1(i+1,j) + u1(i,j) + u1(i,j+1) + u1(i,j-1) - 4.0 * u1(i,j);
  							pgrid(i,j) = u1(i,j) + resid * 0.25;
  							rnorm += fabs(resid);
  						} else if (i == rows-1) {
  							resid = u1(i,j) + u1(i-1,j) + u1(i,j+1) + u1(i,j-1) - 4.0 * u1(i,j);
  							pgrid(i,j) = u1(i,j) + resid * 0.25;
  							rnorm += fabs(resid);
  					 	} else if (j == 0) {
  							resid = u1(i+1,j) + u1(i-1,j) + u1(i,j+1) + u1(i,j) - 4.0 * u1(i,j);
  							pgrid(i,j) = u1(i,j) + resid * 0.25;
  							rnorm += fabs(resid);
  						} else if (j == cols-1) {
  							resid = u1(i+1,j) + u1(i-1,j) + u1(i,j) + u1(i,j-1) - 4.0 * u1(i,j);
  							pgrid(i,j) = u1(i,j) + resid * 0.25;
  							rnorm += fabs(resid);

  						// Compute approximations for inner points
  								} else {
  										resid = u1(i+1,j) + u1(i-1,j) + u1(i,j+1) + u1(i,j-1) - 4.0 * u1(i,j);
  										pgrid(i,j) = (4 * u1(i,j) + resid) * 0.25;
  										rnorm += fabs(resid);
  									}

  								}
  							}
  						}


  		// Test convergence with norm of the residual per grid point
  		avg_norm = rnorm / (cols * rows);

  		if (avg_norm >= tol)
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
        int ep_s2 = clock();
        std::cout << "Method converges in " << iter << " iterations" << std::endl;
        outfile3 << N << " " << (ep_s2 - bp_s2)/double(CLOCKS_PER_SEC) << std::endl;
        break;
      }
  	}
  }


	outfile1.close();
	outfile2.close();
  outfile3.close();

    return 0;
}

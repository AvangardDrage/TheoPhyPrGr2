#include "gauss.h"

 void gauss(double dx, double dy, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid) {

 	/**
 		Application of Gauss-Seidel method to the Laplace equation.The function requires an initial guess u (usually zero) of the solution,
 		with size [xsize, ysize], and fixed boundaries bound from external code.
 	*/


  std::ofstream outfile;
 	outfile.open("gauss_solution.dat");

 	int i, j, n;
 	int iter = 1;
 	int max_iter = 20000;
  int ysize = pgrid.rows(), xsize = pgrid.cols();
 	double tol = 1e-6;		// The tolerance sets the digits precision of the solution
 	double resid, rnorm, avg_norm, Ex, Ey;

  Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(xsize, 0, xsize*dx);
  Eigen::VectorXd y = Eigen::VectorXd::LinSpaced(ysize, 0, ysize*dy);

  Eigen::MatrixXd grad= Eigen::MatrixXd::Zero(ysize,xsize);

  // Iterate until convergence
  for (n = 0; n < max_iter; n++)  {

    rnorm = 0.0;
    avg_norm = 0.0;


      for (i = 0; i < ysize; i++) {
        for (j = 0; j < xsize; j++) {

          // Apply the scheme for non-boundary points
          if (lgrid(i,j)) {

            // Compute approximations for corner points
            if (i == 0 && j == 0) {
              resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
              pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);
            } else if (i == 0 && j == xsize-1) {
              resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
              pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);
            } else if (i == ysize-1 && j == 0) {
              resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
              pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);
            } else if (i == ysize-1 && j == xsize-1) {
              resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
              pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);

            // Compute approximations for points on the grid sides
            } else if (i == 0) {
                          resid = pgrid(i+1,j) + pgrid(i,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
                          pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);
                      } else if (i == ysize-1) {
                          resid = pgrid(i,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
                          pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);
            } else if (j == 0) {
                          resid = pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j) - 4.0 * pgrid(i,j);
                          pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);
            } else if (j == xsize-1) {
                          resid = pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
                          pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);

            // Compute approximations for inner points
                      } else {
              resid = pgrid(i+1,j) + pgrid(i-1,j) + pgrid(i,j+1) + pgrid(i,j-1) - 4.0 * pgrid(i,j);
              pgrid(i,j) += resid * 0.25;
              rnorm += fabs(resid);
            }

        }
      }


    // Test convergence with norm of the residual per grid point
    avg_norm = rnorm / (xsize * ysize);

    if (avg_norm >= tol) {
      iter++;
    } else {
      cout << "Method converges in " << iter << " iterations" << std::endl;
      break;
    }
  }

 	/*
 		Compute electric field components by central difference approximation.
 		No calculation needed for points on the sides of the grid, since E=0
 		outside capacitors and grad is initialised to zero.
 	*/

 	for (i = 1; i < ysize-1; i++) {
 		for (j = 1; j < xsize-1; j++) {

 			Ex= 0.5*(pgrid(i,j+1)-pgrid(i,j-1))/dx;
 			Ey= 0.5*(pgrid(i+1,j)-pgrid(i-1,j))/dx;
 			grad(i,j)= sqrt( pow(Ex, 2) + pow(Ey, 2));

 	    }
 	}

 	// Appends data to file for plotting
 	for (i = 0; i < ysize; i++ ) {
 		for (j = 0; j < xsize; j++) {
 			outfile << x(j) << " " << y(i) << " " << pgrid(i,j) << " " << grad(i,j) << std::endl;
 		}
 	}

   	outfile.close();

 }

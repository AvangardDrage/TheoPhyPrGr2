#include "jac.h"

int jac(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid) {

	std::ofstream outfile;
	outfile.open("n_SOR.dat");

  int i, j, n;
  int iter = 1;
  int max_iter = 50000;
  int rows = pgrid.rows(), cols = pgrid.cols();
  double tol = 1e-6, resid, rnorm, avg_norm;
	double dx = 1/static_cast<double>(pgrid.cols());
	double dy = 1/static_cast<double>(pgrid.rows());

  Eigen::MatrixXd grad= Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd Ex = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd Ey = Eigen::MatrixXd::Zero(rows,cols);
	Eigen::MatrixXd u1 = Eigen::MatrixXd::Zero(rows,cols);

	int bp_s=clock();

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
      int ep_s = clock();
      std::cout << "Method converges in " << iter << " iterations" << std::endl;
      std::cout << "Execution time: " << (ep_s - bp_s)/double(CLOCKS_PER_SEC) << " seconds" << std::endl;
      break;
    }
	}

	for (i = 1; i < rows-1; i++) {
		for (j = 1; j < cols-1; j++) {

			Ex(i,j) = -0.5*(pgrid(i,j+1)-pgrid(i,j-1))/dx;
			Ey(i,j) = -0.5*(pgrid(i+1,j)-pgrid(i-1,j))/dx;
			grad(i,j) = sqrt( pow(Ex(i,j), 2) + pow(Ey(i,j), 2));

	    }
	}

  // Appends data to file for plotting

  for (i = 0; i < rows; i++ )
    {
      for (j = 0; j < cols; j++)
			{
	  outfile << j << " " << i << " " << pgrid(i,j) << " " << grad(i,j) << std::endl;
	}
    }

outfile.close();

return iter;
}

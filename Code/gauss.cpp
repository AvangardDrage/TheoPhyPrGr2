#include "gauss.h"

int gauss(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& pgrid, Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid) {

 	std::ofstream outfile;
 	outfile.open("n_gauss.dat");

 	int i, j, n;
 	int iter = 1;
 	int max_iter = 50000;
  int rows = pgrid.rows(), cols = pgrid.cols();

 	double tol = 1e-6;
 	double resid, rnorm, avg_norm;

  double dx = 1/static_cast<double>(cols);
  double dy = 1/static_cast<double>(rows);


  Eigen::MatrixXd grad = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd Ex = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd Ey = Eigen::MatrixXd::Zero(rows,cols);
  Eigen::MatrixXd u1 = Eigen::MatrixXd::Zero(rows,cols);

  int bp_s=clock();

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
      int ep_s = clock();
      std::cout << "Method converges in " << iter << " iterations" << std::endl;
      std::cout << "Execution time: " << (ep_s - bp_s)/double(CLOCKS_PER_SEC) << " seconds" << std::endl;
      break;
    }
  }

 	for (i = 1; i < rows-1; i++) {
 		for (j = 1; j < cols-1; j++) {

 			Ex(i,j)= 0.5*(pgrid(i,j+1)-pgrid(i,j-1))/dx;
 			Ey(i,j)= 0.5*(pgrid(i+1,j)-pgrid(i-1,j))/dx;
 			grad(i,j)= sqrt( pow(Ex(i,j), 2) + pow(Ey(i,j), 2));

 	    }
 	}

 	for (i = 0; i < rows; i++ ) {
 		for (j = 0; j < cols; j++) {
 			outfile << j << " " << i << " " << pgrid(i,j) << " " << grad(i,j) << std::endl;
 		}
 	}

   	outfile.close();

	return iter;

}

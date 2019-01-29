#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "linspace.h"

using namespace std;

void sor(int xsize, int ysize, vector< vector<double> > &u, vector< vector<double> > &bound) {

	/**
		Application of successive over relaxation to the Laplace equation
		with red-black ordering and Chebyshev acceleration.
		The function requires an initial guess u (usually zero) of the solution,
		with size [xsize, ysize], and fixed boundaries bound from external code.
	*/


	ofstream outfile;
	outfile.open("solution.dat");

	int i, j, n, half_sweep, isw, jsw;
	int iter = 1;
	int max_iter = 10000;

	double dx = 10 / xsize;
	double dy = 10 / ysize;
	double tol = 1e-6;		// The tolerance sets the digits precision of the solution

	double resid, rnorm, avg_norm, Ex, Ey;

	vector<double> x = linspace(0, xsize * dx, xsize);
	vector<double> y = linspace(0, ysize * dy, ysize);
	vector< vector<double> > grad(y.size(), vector<double> (x.size(), 0));


	// Spectral radius of the Jacobi iteration for a rectangular (xsize) x (ysize) grid
	double p = (cos(M_PI / xsize) + (dx/dy)*(dx/dy)*cos(M_PI / ysize)) / (1.0 + (dx/dy)*(dx/dy));
	double w = 1.0;		// Assume the relaxation parameter is one



	// Iterate until convergence
	for (n = 0; n < max_iter; n++)  {

		rnorm = 0.0;
		avg_norm = 0.0;
		isw = 1;

		// Red-black ordering SOR
		for (half_sweep = 1; half_sweep < 3; half_sweep++) {
			jsw=isw;

			for (i = 1; i < ysize-1; i++) {
				for (j = jsw; j < xsize-1; j+=2) {

					// Apply the scheme for non-boundary points
					if (bound[i][j] == 0) {

						// Compute the residual, its norm and the potential
						resid = u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1] - 4.0 * u[i][j];
						u[i][j] += w * resid * 0.25;
						rnorm += fabs(resid);

					// Leave boundary points unchanged
					} else {
						u[i][j] = bound[i][j];
					}
				}
				// Change sweep ordering
				jsw = 3-jsw;
			}
			isw = 3-isw;

			// Improve value of w towards optimal value
			if (n == 0  &&  half_sweep == 1) {
				w = 1.0 / (1.0 - 0.5 * p*p);
			} else {
				w = 1.0 / (1.0 - 0.25 * p*p * w);
			}
		}

		// Test convergence with norm of the residual per grid point
		avg_norm = rnorm / (xsize * ysize);

		if (avg_norm >= tol) {
			iter++;
		} else {
			cout << "Method converges in " << iter << " iterations and w = " << w << endl;
			break;
		}
	}

	// Compute electric field components by central difference approximation
	// and electric field magnitude
	for (i = 1; i < ysize-1; i++) {
		for (j = 1; j < xsize-1; j++) {

			Ex= 0.5*(u[i][j+1]-u[i][j-1])/dx;
			Ey= 0.5*(u[i+1][j]-u[i-1][j])/dx;
			grad[i][j]= sqrt( pow(Ex, 2) + pow(Ey, 2));

	    }
	}

	// Appends data to file for plotting
	for (i = 0; i < ysize; i++ ) {
		for (j = 0; j < xsize; j++) {
			outfile << x[j] << " " << y[i] << " " << u[i][j] << " " << grad[i][j] << endl;
		}
	}

  	outfile.close();

}

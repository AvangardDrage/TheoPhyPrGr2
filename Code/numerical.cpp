#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "linspace.h"

using namespace std;

void sor(int xsize, int ysize, double dx, double dy, vector< vector<double> > &u, vector< vector<double> > &bound) {

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
	int max_iter = 20000;

	double tol = 1e-6;		// The tolerance sets the digits precision of the solution
	double resid, rnorm, avg_norm, Ex, Ey;

	vector<double> x = linspace(0, xsize * dx, xsize);
	vector<double> y = linspace(0, ysize * dy, ysize);
	vector< vector<double> > grad(ysize, vector<double> (xsize, 0));


	// Spectral radius of the Jacobi iteration for a rectangular (xsize) x (ysize) grid
	double p = (cos(M_PI/xsize) + (dx/dy)*(dx/dy) * cos(M_PI/ysize)) / (1.0 + (dx/dy)*(dx/dy));
	double w = 1.0;		// Assume the relaxation parameter is one



	// Iterate until convergence
	for (n = 0; n < max_iter; n++)  {

		rnorm = 0.0;
		avg_norm = 0.0;
		isw = 0;

		// Red-black ordering SOR
		for (half_sweep = 1; half_sweep < 3; half_sweep++) {
			jsw=isw;

			for (i = 0; i < ysize; i++) {
				for (j = jsw; j < xsize; j+=2) {

					// Apply the scheme for non-boundary points
					if (bound[i][j] == 0) {

						/*
							Since the SOR scheme cannot modify the points at
							each side of the grid, leaving them unchanged
							would be equivalent to closing the system in a box
							set at ground. Therefore, computing approximations
							for them by considering the average of the available
							surrounding points will simulate free space
						*/

						// Compute approximations for corner points
						if (i == 0 && j == 0) {
							resid = u[i+1][j] + u[i][j] + u[i][j+1] + u[i][j] - 4.0 * u[i][j];
							u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);
						} else if (i == 0 && j == xsize-1) {
							resid = u[i+1][j] + u[i][j] + u[i][j] + u[i][j-1] - 4.0 * u[i][j];
							u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);
						} else if (i == ysize-1 && j == 0) {
							resid = u[i][j] + u[i-1][j] + u[i][j+1] + u[i][j] - 4.0 * u[i][j];
							u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);
						} else if (i == ysize-1 && j == xsize-1) {
							resid = u[i][j] + u[i-1][j] + u[i][j] + u[i][j-1] - 4.0 * u[i][j];
							u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);

						// Compute approximations for points on the grid sides
						} else if (i == 0) {
	                        resid = u[i+1][j] + u[i][j] + u[i][j+1] + u[i][j-1] - 4.0 * u[i][j];
	                        u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);
	                    } else if (i == ysize-1) {
	                        resid = u[i][j] + u[i-1][j] + u[i][j+1] + u[i][j-1] - 4.0 * u[i][j];
	                        u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);
						} else if (j == 0) {
	                        resid = u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j] - 4.0 * u[i][j];
	                        u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);
						} else if (j == xsize-1) {
	                        resid = u[i+1][j] + u[i-1][j] + u[i][j] + u[i][j-1] - 4.0 * u[i][j];
	                        u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);

						// Compute approximations for inner points
	                    } else {
							resid = u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1] - 4.0 * u[i][j];
							u[i][j] += w * resid * 0.25;
							rnorm += fabs(resid);
						}


					// Leave boundary points unchanged
					} else {
						u[i][j] = bound[i][j];
					}
				}
				// Change sweep ordering
				jsw = 1-jsw;
			}
			isw = 1-isw;

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

	/*
		Compute electric field components by central difference approximation.
		No calculation needed for points on the sides of the grid, since E=0
		outside capacitors and grad is initialised to zero.
	*/

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

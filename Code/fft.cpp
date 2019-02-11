#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "fft.h"
#include "sine_transform.hpp"
#include "linspace.h"
#include "fourier.h"

using namespace std;

void fft(int J, int L, double dx, double dy, vector< vector<double> > &u, vector< vector<double> > &bound) {

	ofstream outfile;
	outfile.open("solution.dat");

	int j,l,m,n;

	vector<double> x = linspace(0, L * dx, L);
	vector<double> y = linspace(0, J * dy, J);

	vector< vector<double> > f(J, vector<double> (L, 0));
	vector< vector<double> > F(J, vector<double> (L, 0));
	vector< vector<double> > U(J, vector<double> (L, 0));
	vector< vector<double> > K(J, vector<double> (L, 0));
	vector<double> row;
	vector<double> col;

	/*
	double *p_row;
	p_row = row;

	double *p_col;
	p_col = col;

/*
	for (j = 0; j < J-2; j++) {
		f[i][0] -= u[i+1][0];
		f[i][N-3] -= u[i+1][N-1];
		sum_M += i;
	}

	for (l = 0; l < L-2; l++) {
		f[0][j] -= u[0][j+1];
		f[M-3][j] -= u[M-1][j+1];
		sum_N += j;
	}
*/

	for (j = 1; j < J-1; j++) {
		for (l = 1; l < L-1; l++) {
			f[j][l] = -(bound[j+1][l] + bound[j-1][l] + bound[j][l+1] + bound[j][l-1] - 4 * bound[j][l]);
		}
	}


	for (m = 0; m < J; m++) {
		for (n = 0; n < L; n++) {
			K[n][m] = 2 * (cos(M_PI*m/J) + cos(M_PI*n/L) - 2);
		}
	}


	//fft of rows
	for (j = 0; j < J; j++) {
		for (l = 0; l < L; l++) {
			row.push_back(f[j][l]);
		}

		sinft(row);

		for (l = 0; l < L; l++) {
			F[j][l] = row[l];
		}
		row.clear();
	}


	//fft of columns
	for (l = 0; l < L; l++) {
		for (j = 0; j < J; j++) {
			col.push_back(F[j][l]);
		}
		sinft(col);

		for (j = 0; j < J; j++) {
			F[j][l] = col[j];
		}
		col.clear();
	}


	for (m = 0; m < J; m++) {
		for (n = 0; n < L; n++) {
			U[n][m] = F[n][m] / K[n][m];
		}
	}



	//ifft of rows
	for (j = 0; j < J; j++) {
		for (l = 0; l < L; l++) {
			row.push_back(U[j][l]);
		}
		sinft(row);

		for (l = 0; l < L; l++) {
			u[j][l] = row[l];
		}
		row.clear();
	}


	//ifft of columns
	for (l = 0; l < L; l++) {
		for (j = 0; j < J; j++) {
			col.push_back(u[j][l]);
		}

	 sinft(col);

		for (j = 0; j < J; j++) {
			u[j][l] = 4*col[j]/(J*L);
		}
		col.clear();
	}


	// Appends data to file for plotting
	for (j = 0; j < J; j++ ) {
		for (l = 0; l < L; l++) {
			outfile << x[l] << " " << y[j] << " " << u[j][l] << endl;
		}
	}

	outfile.close();


}

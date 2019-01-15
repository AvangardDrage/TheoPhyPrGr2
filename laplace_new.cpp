#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "linspace.h"

using namespace std;

int main () {

	ofstream outfile;
	outfile.open("plates.dat");

	double error = 1;
	double tol = 1e-3;
	double dx = 0.01;
	double x_max = 10;
	double y_max = 1;

	vector<double> x = linspace(0, x_max, int(x_max/dx));
	vector<double> y = linspace(0, y_max, int(y_max/dx));
	vector<vector<double>> u(x.size(), vector<double> (y.size(), 0));
	vector<vector<double>> u1;


	for (int i = 0; i < x.size(); i++) {
		u[i][0] = 5;
		u[i][y.size()-1] = -5;
  	}


	while (abs(error) < 100) {
		u1 = u;
		 for (int i = 1; i < x.size()-1; i++) {
			 for (int j = 1; j < y.size()-1; j++) {
				 u[i][j] = 0.25 * (u1[i+1][j] + u1[i-1][j] + u1[i][j+1] + u1[i][j-1]);
			 }
		 }
	error++;
	}

	for (int i = 0; i < x.size(); i++ ) {
		for (int j = 0; j < y.size(); j++) {
			outfile << x[i] << " " << y[i] << " " << u[i][j] << endl;
		}
	}

  	outfile.close();
	return 0;
}

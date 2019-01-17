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
	double dx = 0.1;
	double x_max = 10;
	double y_max = 10;

	vector<double> x = linspace(0, x_max, int(x_max/dx));
	vector<double> y = linspace(0, y_max, int(y_max/dx));
	vector< vector<double> > u(y.size(), vector<double> (x.size(), 0));
	vector< vector<double> > u1;


	for (int i = int(2/dx-1); i < y.size()-int(2/dx-1); i++) {
		u[i][int(4/dx-1)] = 5;
		u[i][x.size()-int(4/dx-1)] = -5;
  	}


	while (abs(error) < 1000) {
		u1 = u;
		for(int j = 1; j < x.size()-1; j++) {
			for(int i = 1; i < y.size()-1; i++) {
				u[i][j] = 0.25 * (u1[i+1][j] + u1[i-1][j] + u1[i][j+1] + u1[i][j-1]);
			}
		}
		for (int i = int(2/dx-1); i < y.size()-int(2/dx-1); i++) {
			u[i][int(4/dx-1)] = 5;
			u[i][x.size()-int(4/dx-1)] = -5;
		}
		error++;
	}

	for (int i = 0; i < y.size(); i++ ) {
		for (int j = 0; j < x.size(); j++) {
			outfile << x[j] << " " << y[i] << " " << u[i][j] << endl;
		}
	}

  	outfile.close();
	return 0;
}

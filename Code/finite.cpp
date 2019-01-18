#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include "linspace.h"

using namespace std;

int main () {

	ofstream outfile;
	outfile.open("plates.dat");

	double max_error = 1;
	double tol = 1e-3;
	double dx = 0.1;
	double x_max = 10;
	double y_max = 10;
	double Ex, Ey;

	vector<double> x = linspace(0, x_max, int(x_max/dx));
	vector<double> y = linspace(0, y_max, int(y_max/dx));
	vector<double> error;
	vector< vector<double> > u(y.size(), vector<double> (x.size(), 0));
	vector< vector<double> > u1;
	vector< vector<double> > grad(y.size(), vector<double> (x.size(), 0));


	for (int i = int(2/dx-1); i < y.size()-int(2/dx-1); i++) {
		u[i][int(4/dx-1)] = 100;
		u[i][x.size()-int(4/dx-1)] = -100;
  	}


	while (max_error > tol)  {
		u1 = u;
		for(int j = 1; j < x.size()-1; j++) {
			for(int i = 1; i < y.size()-1; i++) {
				u[i][j] = 0.25 * (u1[i+1][j] + u1[i-1][j] + u1[i][j+1] + u1[i][j-1]);
			}
		}
		for (int i = int(2/dx-1); i < y.size()-int(2/dx-1); i++) {
			u[i][int(4/dx-1)] = 100;
			u[i][x.size()-int(4/dx-1)] = -100;
		}
		error.clear();
		for (int i = 0; i < y.size(); i++ ) {
			for (int j = 0; j < x.size(); j++) {
				error.push_back(abs(u1[i][j] - u[i][j]));
	 		}
	 	}
		max_error = *max_element(error.begin(), error.end());
	}

	for(int j=1; j < x.size()-1;j++) {
		for(int i=1; i < y.size()-1; i++) {
			Ey= 0.5*(u[i+1][j]-u[i-1][j])/dx;
			Ex= 0.5*(u[i][j+1]-u[i][j-1])/dx;
			Ey= -Ey;
			Ex= -Ex;
			grad[i][j]= sqrt( pow(Ex, 2) + pow(Ey, 2));
	    }
	}

	for (int i = 0; i < y.size(); i++ ) {
		for (int j = 0; j < x.size(); j++) {
			outfile << x[j] << " " << y[i] << " " << u[i][j] << " " << grad[i][j] << endl;
		}
	}

  	outfile.close();
	return 0;
}

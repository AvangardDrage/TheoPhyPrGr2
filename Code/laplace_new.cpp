#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include "linspace.h"
#include "gradient.h"

using namespace std;

int main () {

	ofstream outfile;
	outfile.open("plates.dat");

	int k = 0;
	double max_error = 1;
	double tol = 1e-3;
	double dx = 0.01;
	double x_max = 1;
	double y_max = 10;

	vector<double> x = linspace(0, x_max, int(x_max/dx));
	vector<double> y = linspace(0, y_max, int(y_max/dx));
	vector<double> error;
	vector< vector<double> > u(y.size(), vector<double> (x.size(), 0));
	vector< vector<double> > u1;
	vector< vector<double> > grad;


	for (int i = 0; i < y.size(); i++) {
		u[i][0] = 5;
		u[i][x.size()-1] = -5;
  	}


	while (max_error > tol) {
		u1 = u;
		for(int j = 1; j < x.size()-1; j++) {
			for(int i = 1; i < y.size()-1; i++) {
				u[i][j] = 0.25 * (u1[i+1][j] + u1[i-1][j] + u1[i][j+1] + u1[i][j-1]);
			}
		}
		error.clear();
		for (int i = 0; i < y.size(); i++ ) {
			for (int j = 0; j < x.size(); j++) {
				error.push_back(abs(u1[i][j] - u[i][j]));
	 		}
	 	}
		max_error = *max_element(error.begin(), error.end());
	}

	grad = gradient(y.size(), x.size(), u);

	for (int i = 0; i < y.size(); i++ ) {
		for (int j = 0; j < x.size(); j++) {
			outfile << x[j] << " " << y[i] << " " << u[i][j] << " " << grad[i][j] <<endl;
		}
	}

  	outfile.close();
	return 0;
}

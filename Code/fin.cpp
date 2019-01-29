#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "linspace.h"

using namespace std;

int main () {

	ofstream outfile;
	outfile.open("plates.dat");

	int iter = 1;
	int max_iter = 10000;
	double resid;
	double rnorm;
	double tol = 1e-6;
	double x_max = 10;
	double y_max = 10;
	double dx = 0.05;
	double Ex, Ey;


	vector<double> x = linspace(0, x_max, int(x_max/dx));
	vector<double> y = linspace(0, y_max, int(y_max/dx));
	vector< vector<double> > u(y.size(), vector<double> (x.size(), 0));
	vector< vector<double> > boundary(y.size(), vector<double> (x.size(), NULL));
	vector< vector<double> > grad(y.size(), vector<double> (x.size(), 0));

	//t = cos(M_PI/x.size()) + cos(M_PI/y.size());
	//w = (8 - sqrt(64 - 16 * t*t)) / (t*t);

	/*for (int i = 0; i < y.size(); i++) {
		u[i][0] = 100;
		u[i][x.size()-1] = -100;
  	}*/

	for (int i = int(2/dx-1); i < y.size()-int(2/dx-1); i++) {
		boundary[i][int(4/dx-1)] = 100;
		boundary[i][x.size()-int(4/dx-1)] = -100;
  	}

	double w = 1;
	double p = cos(M_PI / x.size());
	int ipass, jsw, lsw;

	for (int n = 0; n<max_iter; n++)  {

		rnorm = 0;
		jsw = 1;

		//red-black sor
		for (ipass=0; ipass<2; ipass++) {
			lsw=jsw;
			for (int i = 1; i < y.size()-1; i++) {
				for (int j = 1; j < x.size()-1; j++) {
					if (boundary[i][j] == NULL) {
						resid = u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1] - 4 * u[i][j];
						u[i][j] += w * resid * 0.25;
						rnorm += fabs(resid);
					} else {
						u[i][j] = boundary[i][j];
					}
				}
				lsw = 3-lsw;
			}
			jsw = 3-jsw;
			w=(n == 0 && ipass == 0 ? 1.0/(1.0-0.5*p*p) : 1.0/(1.0-0.25*p*p*w));
		}


		if (rnorm >= tol) {
			iter++;
		} else {
			cout << "Method converges in " << iter << " iterations and w = " << w << endl;
			break;
		}
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

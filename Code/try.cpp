#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include "linspace.h"
#include <ctime>

using namespace std;

int main () {

	ofstream outfile;
	outfile.open("plates.dat");

	int iter = 1;
	int max_iter = 10000;
	double resid;
	double rnorm;
	double avg_norm;
	double tol = 1e-6;
	double x_max = 10;
	double y_max = 10;
	double dx = 0.05;
	double Ex, Ey;

	vector<double> x = linspace(0, x_max, int(x_max/dx));
	vector<double> y = linspace(0, y_max, int(y_max/dx));
	vector< vector<double> > u(y.size(), vector<double> (x.size(), 0));
	vector< vector<double> > boundary(y.size(), vector<double> (x.size(), 0));
	vector< vector<double> > grad(y.size(), vector<double> (x.size(), 0));

	//double t = cos(M_PI/x.size()) + cos(M_PI/y.size());
	//double w = (8 - sqrt(64 - 16 * t*t)) / (t*t);

	/*for (int i = 0; i < y.size(); i++) {
		u[i][0] = 100;
		u[i][x.size()-1] = -100;
  	}*/

	for (int i = int(1/dx-1); i < y.size()-int(1/dx-1); i++) {
		boundary[i][int(3/dx-1)] = 100;
		boundary[i][x.size()-int(3/dx-1)] = -100;
  	}

	int start_X = int(5/dx); // center point
	int start_Y = int(5/dx);

	int r1 = int(0.5/dx);

	for (int i = 0; i < y.size(); i++ ) {
		for (int j = 0; j < x.size(); j++) {
			if(((i - start_X) * (i - start_X) + (j - start_Y) * (j - start_Y)) <= r1 * r1)
			{
				boundary[i][j] = 0.1;
			}
		}
	}

	clock_t start, end;
	double cpu_time;

	start = clock();

	int half_sweep, isw, jsw;
	double w = 1;
	double p = cos(M_PI / x.size());

	for (int n = 0; n < max_iter; n++)  {

		rnorm = 0.0;
		avg_norm = 0.0;
		isw = 1;

		//red-black SOR
		for (half_sweep = 1; half_sweep < 3; half_sweep++) {
			jsw=isw;
			for (int i = 1; i < y.size()-1; i++) {
				for (int j = jsw; j < x.size()-1; j+=2) {
					if (boundary[i][j] == 0) {
						resid = u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1] - 4.0 * u[i][j];
						u[i][j] += w * resid * 0.25;
						rnorm += fabs(resid);
					} else {
						u[i][j] = boundary[i][j];
					}
				}
				jsw = 3-jsw;
			}
			isw = 3-isw;

			if (n==0 && half_sweep == 1) {
				w = 1.0 / (1.0 - 0.5 * p*p);
			} else {
				w = 1.0 / (1.0 - 0.25 * p*p * w);
			}
		}

		avg_norm = rnorm / (x.size() * y.size());

		if (avg_norm >= tol) {
			iter++;
		} else {
			cout << "Method converges in " << iter << " iterations and w = " << w << endl;
			break;
		}
	}

	for(int i=1; i < y.size()-1;i++) {
		for(int j=1; j < x.size()-1; j++) {
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

	end = clock();
	cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout << "CPU time used: " << cpu_time << endl;
	
	return 0;
}

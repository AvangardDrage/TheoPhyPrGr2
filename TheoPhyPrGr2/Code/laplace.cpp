#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

int main () {

	ofstream outfile;
	outfile.open("plates.dat");

	float error = 1;
	float tol = 1e-3;
	float dx = 0.01;
	float x_max = 10;
	float y_max = 1;
	float x[int(x_max/dx)], y[int(y_max/dx)];
	float delta1, delta2;

	for ( int i = 0; i <= sizeof(x)/sizeof(x[0]) ; i++) {

		delta1 = 10/(1/dx +1);
		x[i] = 0 + i*delta1;

	}


  for ( int j = 0; j <= sizeof(y)/sizeof(y[0]) ; j++) {

		delta2 = 1/(1/dx +1);
		y[j] = 0 + j*delta2;

  }

	float u[sizeof(x)/sizeof(x[0])][sizeof(y)/sizeof(y[0])] = {{0}};
	float u1[sizeof(x)/sizeof(x[0])][sizeof(y)/sizeof(y[0])];
	float E[sizeof(x)/sizeof(x[0])][sizeof(y)/sizeof(y[0])] = {{0}};

	for ( int i = 0; i < sizeof(x)/sizeof(x[0]) ; i++) {

		u[i][0] = 5;
		u[i][sizeof(x)/sizeof(x[0]) - 1] = -5;

  }

	while (abs(error) > tol) {

		 for (int i = 1; i < sizeof(x)/sizeof(x[0]) - 1 ; i++) {
			 for (int j = 1; j < sizeof(y)/sizeof(y[0]) -1 ; j++) {

				 u[i][j] = 0.25 * (u1[i+1][j] + u1[i-1][j] + u1[i][j+1] + u1[i][j-1]);

			 }

			 error = u[i][j] - u1[i][j];
		 }

	}

	for ( int i = 0; i < sizeof(x)/sizeof(x[0]) ; i++ ) {
		for ( int j = 0; j < sizeof(y)/sizeof(y[0]) ; j++) {

			outfile << x[i] << " " << y[i] << " " << u[i][j] << endl;

		}
	}

  outfile.close();
	return 0;

}

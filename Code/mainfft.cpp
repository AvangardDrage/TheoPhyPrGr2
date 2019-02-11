#include <iostream>
#include <vector>
#include <ctime>
#include "numerical.h"
#include "fft.h"
//#include "fourier.hpp"

using namespace std;

int main() {

	// Set the dimensions  of the solution grid and the respective increment sizes
	int xsize = 130;
	int ysize = 130;
	float dx = 0.05;
	float dy = 0.05;

	// Initialise grids for potential and boundaries to zero
	vector< vector<double> > u(ysize, vector<double> (xsize, 0));
	vector< vector<double> > bound(ysize, vector<double> (xsize, 0));

	/*
	Box test;

	test.ground = true;

	test.set_centre(5/dx, 5/dy);
	test.set_parameters(0.5/dx, 4/dx);
	test.set_potential(5);
	*/


	// Set the boundaries of the system
/*
	for (int i = int(1/dx-1); i < ysize-int(1/dx-1); i++) {
		bound[i][int(2.2/dx-1)] = 10;
		bound[i][xsize-int(2.2/dx-1)] = -10;
	}
*/
	for (int i = 0; i < ysize; i++) {
		bound[i][0] = 10;
		bound[i][xsize-1] = -10;
	}

/*
	int start_X = int(5/dx); // center point
	int start_Y = int(5/dx);

	int r1 = int(0.5/dx);

	for (int i = 0; i < ysize; i++ ) {
		for (int j = 0; j < xsize; j++) {
			if(((i - start_X) * (i - start_X) + (j - start_Y) * (j - start_Y)) <= r1 * r1)
			{
				bound[i][j] = 0.1;
			}
		}
	}
*/

	/*
	int start_X = int(5/dx); // center point
	int start_Y = int(5/dx);

	int r1 = int(4/dx);
	int r2 = int(1/dx);

	for (int i = 0; i < ysize; i++ ) {
		for (int j = 0; j < xsize; j++) {
			if(((i - start_X) * (i - start_X) + (j - start_Y) * (j - start_Y)) <= r1 * r1 + 2/dx && ((i - start_X) * (i - start_X) + (j - start_Y) * (j - start_Y)) >= r1 * r1 - 2/dx)
			{
				bound[i][j] = 10;
			}
		}
	}

	for (int i = 0; i < ysize; i++ ) {
		for (int j = 0; j < xsize; j++) {
			if(((i - start_X) * (i - start_X) + (j - start_Y) * (j - start_Y)) <= r2 * r2 )
			{
				bound[i][j] = 0.1;
			}
		}
	}
*/


	// Measure CPU time for SOR function
	clock_t start, end;
	double cpu_time;
	start = clock();


	// Apply SOR method to find potential and electric field magnitude
	//sor(xsize, ysize, dx, dy, u, bound);
	fft(xsize, ysize, dx, dy, u, bound);

	end = clock();
	cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout << "CPU time used: " << cpu_time << endl;


	return 0;
}

#include <vector>
#include "numerical.h"

using namespace std;

int main() {

	// Set the dimensions of the solution grid and the respective increment sizes
	int xsize = 200;
	int ysize = 200;
	float dx = 10 / xsize;
	float dy = 10 / ysize;

	// Initialise grids for potential and boundaries to zero
	vector< vector<double> > u(ysize, vector<double> (xsize, 0));
	vector< vector<double> > bound(ysize, vector<double> (xsize, 0));


	// Set the boundaries of the system
	for (int i = 40; i < ysize-40; i++) {
		bound[i][80] = 100;
		bound[i][xsize-80] = -100;
  	}

	// Apply SOR method to find potential and electric field magnitude
	sor(xsize, ysize, u, bound);


	return 0;
}

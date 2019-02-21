#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include "ObjectInput.h"
#include "Boundary.h"
#include "BDef.h"
#include "EigenSor.h"
#include "jac.h"
#include "gauss.h"

int main() {

	std::ofstream outfile;
	outfile.open("comparison.dat");

	Plate pplate; // positive plate
	Plate nplate; // negative plate

	for(int N=50; N<=250; N+=5) {

	    Eigen::Matrix <bool,Eigen::Dynamic,Eigen::Dynamic> lgrid(N,N); // logic grid
	    Eigen::Matrix <double,Eigen::Dynamic,Eigen::Dynamic> pgrid(N,N); // potential grid


	    for(int i=0; i<lgrid.rows();i++) {
	    	for(int j=0; j<lgrid.cols(); j++) {
		  		lgrid(i,j) = true;
		  		pgrid(i,j) = 0;
			}
	    }

		// Create a system of two parallel plates capacitor
		pplate.centre[0] = 0;  // on the left side
		pplate.direction[0] = true;  // vertical
		pplate.direction[1] = false;  // to the left
		pplate.potential = 10;
		PGD(lgrid, pgrid, pplate);

		nplate.centre[0] = pgrid.cols()-1;  // on the right side
		nplate.direction[0] = true;  // vertical
		nplate.direction[1] = true;  // to the right
		nplate.potential = -10;
		PGD(lgrid, pgrid, nplate);

		// numerical method
		int iter_sor = sor(pgrid,lgrid);
		outfile << N << " " << iter_sor << " ";



		for(int i=0; i<lgrid.rows();i++) {
	    	for(int j=0; j<lgrid.cols(); j++) {
		  		lgrid(i,j) = true;
		  		pgrid(i,j) = 0;
			}
	    }

		// Create a system of two parallel plates capacitor
		pplate.centre[0] = 0;  // on the left side
		pplate.direction[0] = true;  // vertical
		pplate.direction[1] = false;  // to the left
		pplate.potential = 10;
		PGD(lgrid, pgrid, pplate);

		nplate.centre[0] = pgrid.cols()-1;  // on the right side
		nplate.direction[0] = true;  // vertical
		nplate.direction[1] = true;  // to the right
		nplate.potential = -10;
		PGD(lgrid, pgrid, nplate);

		// numerical method
		int iter_gauss = gauss(pgrid,lgrid);
		outfile << iter_gauss << " ";



		for(int i=0; i<lgrid.rows();i++) {
	    	for(int j=0; j<lgrid.cols(); j++) {
		  		lgrid(i,j) = true;
		  		pgrid(i,j) = 0;
			}
	    }

		// Create a system of two parallel plates capacitor
		pplate.centre[0] = 0;  // on the left side
		pplate.direction[0] = true;  // vertical
		pplate.direction[1] = false;  // to the left
		pplate.potential = 10;
		PGD(lgrid, pgrid, pplate);

		nplate.centre[0] = pgrid.cols()-1;  // on the right side
		nplate.direction[0] = true;  // vertical
		nplate.direction[1] = true;  // to the right
		nplate.potential = -10;
		PGD(lgrid, pgrid, nplate);

		// numerical method
		int iter_jac = jac(pgrid,lgrid);
		outfile << iter_jac << std::endl;

	}

	outfile.close();

    return 0;
}

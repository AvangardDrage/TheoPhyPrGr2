#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "linspace.h"


using namespace std;


//This program computes the analyical solution for the first analytical problem


int main(){


	int xsize=200,ysize=200;          //size of the solution grid
	double V=1,a=1, b=5;             //a:raduis of the cylinder, b:radius of outer shell,V:potential of outer shell
	double dx = 0.05;                 //spacing of the grid
	double r;		  //independent variables in cylindical coordinate

	double x0,y0;
	
	ofstream outfile;
	outfile.open("solution_first.dat");

	double solution[ysize][xsize];	//an array that stores solution


	//initialise vector that store coordinate values in Cartesian. xmin = -5, ymin = -5, xmax = 5, ymax 5 with spacing 0.05 between nodes
	vector<double> x = linspace(0, xsize * dx, xsize);
	vector<double> y = linspace(0, ysize * dx, ysize);

	for (int i = 0; i < ysize; i++){
		y[i] -= ysize/2*dx;
	}

	for (int j = 0; j < xsize; j++){
		x[j] -= xsize/2*dx;
	}

	

	for (int i = 0; i < ysize; i++){
	    for (int j = 0; j < xsize; j++){

		//convert cartesian into 2d cylindical coordinate
		r = sqrt(pow(x[j],2)+pow(y[i],2));

		//calculate the solution

		//if r < a then the potnetial is zero as it is insinde the grounded cylinder
		if (r < a){
			solution[i][j]=0;
		   }
		//if b < r then the potnetial is V
		else if (b < r) {
			solution[i][j] = V;
			}		    
		//otherwise, calculate the potential inbetween a and b from the analytical solution
		else {
		     solution[i][j] = V*log(r/a)/log(b/a);
		     }

		outfile << x[j] << " " << y[i] << " " << solution[i][j] << endl;
		}
	    }



    return 0;
}




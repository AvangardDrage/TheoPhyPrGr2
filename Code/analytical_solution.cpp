#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "linspace.h"


using namespace std;


//This program computes the analyical solution for the second analytical problem


int main(){


	int xsize=200,ysize=200;          //size of the solution grid
	double d=5,V=1,a=1.15;             //d:distance from the origin to the plate, V:the magnitude of the potential, a:radius of the cylinder
	double dx = 0.05;                 //spacing of the grid
	double r,theta;			  //independent variables in cylindical coordinate

	double x0,y0;
	
	ofstream outfile;
	outfile.open("solution_new.dat");

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

	

	//Calculate the analytical solution
	for (int i = 0; i < ysize; i++){
	    for (int j = 0; j < xsize; j++){

		//convert cartesian into 2d cylindical coordinate
		r = sqrt(pow(x[j],2)+pow(y[i],2));
		theta = atan(y[i]/x[j]);

		//calculate the solution
		//if r < a then the potnetial is zero as it is insinde the grounded cylinder
		if (r < a){
			solution[i][j]=0;
		   }
		//else calculate the solution between r=a to r=d/cos(theta) from the analytical solution
		// on the negative x-axis, potential is set to +V, on the positive it is -V
		else if (x[j] < 0){
			solution[i][j] = cos(theta)*(r-pow(a,2)/r)*(V*d)/(pow(d,2)-pow(cos(theta),2)*pow(a,2));
		    }
		else if (x[j] > 0){
			solution[i][j]= cos(theta)*(r-pow(a,2)/r)*(-1*V*d)/(pow(d,2)-pow(cos(theta),2)*pow(a,2));
		    }


		outfile << x[j] << " " << y[i] << " " << solution[i][j] << endl;
		}
	    }


    return 0;
}




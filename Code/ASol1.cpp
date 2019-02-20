#include <iostream>
#include "ASol1.h"

//This program computes the analyical solution for the first analytical problem

void ASol1(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& asol, Circle cobj, Shell sobj)
{
  double r;   //independent variables in cylindrical coordinates

  double rc = static_cast<double> (cobj.radius);  // cylinder radius
  double ri = static_cast<double> (sobj.iradius); // inner radius
  double ro = static_cast<double> (sobj.oradius); // outer radius


  double x0,y0;

  std::ofstream outfile;
  outfile.open("a_sol.dat");


  //Calculate the analytical solution
  for (int i = 0; i < asol.rows(); i++)
    {
      for (int j = 0; j < asol.cols(); j++)
	{

	  //std::cout << "i: " << i << ", j: " << j << std::endl;

	  //convert cartesian into 2d cylindrical coordinate
	  double rx = static_cast<double>(j - cobj.centre[1]);
	  double ry = static_cast<double>(i - cobj.centre[0]);

	  r = sqrt(pow(rx,2)+pow(ry,2));

	  //calculate the solution

	  //if r < a then the potential is zero as it is insinde the grounded cylinder
	  if (r < rc)
	    {
	      asol(i,j) = 0;
	    }
	  else if (r >= ri)
	    {
	      asol(i,j) = sobj.potential;
	    }
	  //otherwise, calculate the potential inbetween a and b from the analytical solution
	  else
	    {
	      asol(i,j) = sobj.potential*log(r/rc)/log(ri/rc);
	    }

	  outfile << j << " " << i << " " << asol(i,j) << std::endl;
	}
    }

  outfile.close();
}

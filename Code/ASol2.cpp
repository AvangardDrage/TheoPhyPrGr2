#include <iostream>
#include "ASol2.h"

//This program computes the analyical solution for the second analytical problem


void ASol2(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& asol, Circle& cobj, Plate& pplate, Plate& nplate)
{
  double r;
  double theta;			  //independent variables in cylindrical coordinates

  std::ofstream outfile;
  outfile.open("a_sol.dat");


  //Calculate the analytical solution
  for (int i = 0; i < asol.rows(); i++)
    {
      for (int j = 0; j < asol.cols(); j++)
	{


	  double rx = static_cast<double>(j - cobj.centre[1]);
	  double ry = static_cast<double>(i - cobj.centre[0]);

	    // std::cout << "rx: "<< rx << "    " << "ry: "<< ry << std::endl;

	      // convert cartesian into 2d cylindical coordinate
	   r = sqrt(pow(rx,2)+pow(ry,2));
	   theta = atan(ry/rx);



	   // if r < a then the potential is zero as it is insinde the grounded cylinder
	   if (r <= cobj.radius)
	      {
		 asol(i,j)=0;
	      }
	      //else calculate the solution between r=a to r=d/cos(theta) from the analytical solution
	      // on the negative x-axis, potential is set to +V, on the positive it is -V
	   else if (j < cobj.centre[1] && j > pplate.centre[0])
		{
		 asol(i,j) = 2*cos(theta)*(r-pow(cobj.radius,2)/r)*(pplate.potential*(nplate.centre[0]-pplate.centre[0]))/(pow((nplate.centre[0]-pplate.centre[0]),2)-pow(cos(theta),2)*pow(cobj.radius,2));
		}
	   else if (j > cobj.centre[1] && j < nplate.centre[0])
		{
		 asol(i,j) = 2*cos(theta)*(r-pow(cobj.radius,2)/r)*(nplate.potential*(nplate.centre[0]-pplate.centre[0]))/(pow((nplate.centre[0]-pplate.centre[0]),2)-pow(cos(theta),2)*pow(cobj.radius,2));
		}
	      outfile << j << " " << i << " " << asol(i,j) << std::endl;
	}
    }


  outfile.close();
}

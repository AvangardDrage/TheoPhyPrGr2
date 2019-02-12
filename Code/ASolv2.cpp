#include <iostream>
#include "ASol.h"

//This program computes the analyical solution for the second analytical problem


void ASol(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& asol, Circle& cobj, Plate& pplate, Plate& nplate)
{


  double r;
  double theta;			  //independent variables in cylindical 
	
  std::ofstream outfile;
  outfile.open("solution_new.dat");

  //Calculate the analytical solution
  for (int i = 0; i < asol.rows(); i++)
    {
      //std::cout << "*********************************" << std::endl;
      for (int j = 0; j < asol.cols(); j++)
	{

	  double rx = static_cast<double>(cobj.centre[1]-j);
	  double ry = static_cast<double>(cobj.centre[0]-i);

	    // std::cout << "--------------------------------" << std::endl;
	    // std::cout << "i: " << i << "    " << "j: " << j << std::endl;
	    // std::cout << "rx: "<< rx << "    " << "ry: "<< ry << std::endl;

	  if(j!=cobj.centre[1])
	    {

	      // convert cartesian into 2d cylindical coordinate
	      r = sqrt(pow(rx,2)+pow(ry,2));
	      theta = atan(ry/rx);

	      // std::cout << "Gate 1: r =  " << r << "; theta = " << theta << std::endl;
	      // calculate the solution

	      if(j <= pplate.centre[0])
		{
		  //  std::cout <<"Gate 2.1" << std::endl;
		  asol(i,j) = pplate.potential;
		}
	      else if(j>=nplate.centre[0])
		{
		  // std::cout <<"Gate 2.2" << std::endl;
		  asol(i,j) = nplate.potential;
		}

	      // if r < a then the potnetial is zero as it is insinde the grounded cylinder
	      else if (r <= cobj.radius)
		{
		  // std::cout <<"Gate 2.3" << std::endl;
		  asol(i,j)=0;
		}
	      //else calculate the solution between r=a to r=d/cos(theta) from the analytical solution
	      // on the negative x-axis, potential is set to +V, on the positive it is -V
	      else if (j < cobj.centre[0])
		{
		  // std::cout << "Gate 2.4" << std::endl;
		  asol(i,j) = cos(theta)*(r-pow(cobj.radius,2)/r)*(pplate.potential*(nplate.centre[0]-pplate.centre[0]))/(pow((nplate.centre[0]-pplate.centre[0]),2)-pow(cos(theta),2)*pow(cobj.radius,2));
		}
	      else if (j > cobj.centre[0])
		{
		  // std::cout << "Gate 2.5" << std::endl;
		  asol(i,j) = cos(theta)*(r-pow(cobj.radius,2)/r)*(nplate.potential*(nplate.centre[0]-pplate.centre[0]))/(pow((nplate.centre[0]-pplate.centre[0]),2)-pow(cos(theta),2)*pow(cobj.radius,2));
		}
	      // std::cout << "Gate 3" << std::endl;
	      outfile << j << " " << i << " " << asol(i,j) << std:: endl;
	      // std::cout << "--------------------------------" << std::endl;
	    }
	  //  std::cout << "*********************************" << std::endl;
	}
    }
}




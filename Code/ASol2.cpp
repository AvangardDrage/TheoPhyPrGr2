#include <iostream>
#include "ASol2.h"

//This program computes the analyical solution for the second analytical problem


void ASol2(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& asol, Circle& cobj, Plate& pplate, Plate& nplate)
{


  double r;

  double theta;			  //independent variables in cylindical

  std::ofstream outfile;
  std::ofstream cosdata;
  outfile.open("a_sol_2.dat");
  cosdata.open("cosdata.dat");


 // int bp_s=clock();

  //Calculate the analytical solution
  for (int i = 0; i < asol.rows(); i++)
    {
      //std::cout << "*********************************" << std::endl;
      for (int j = 0; j < asol.cols(); j++)
	{


	  double rx = static_cast<double>(j - cobj.centre[1]);
	  double ry = static_cast<double>(i - cobj.centre[0]);

	    // std::cout << "--------------------------------" << std::endl;
	    // std::cout << "i: " << i << "    " << "j: " << j << std::endl;
	    // std::cout << "rx: "<< rx << "    " << "ry: "<< ry << std::endl;

	      // convert cartesian into 2d cylindical coordinate
	   r = sqrt(pow(rx,2)+pow(ry,2));
	   theta = atan(ry/rx);



	   // if r < a then the potnetial is zero as it is insinde the grounded cylinder
	   if (r <= cobj.radius)
	      {
		 asol(i,j)=0;
	      }
	      //else calculate the solution between r=a to r=d/cos(theta) from the analytical solution
	      // on the negative x-axis, potential is set to +V, on the positive it is -V
	   else if (j < cobj.centre[1] && j > pplate.centre[0])
		{
		  // std::cout << "Gate 2.4" << std::endl;
		 asol(i,j) = 2*cos(theta)*(r-pow(cobj.radius,2)/r)*(pplate.potential*(nplate.centre[0]-pplate.centre[0]))/(pow((nplate.centre[0]-pplate.centre[0]),2)-pow(cos(theta),2)*pow(cobj.radius,2));
		}
	   else if (j > cobj.centre[1] && j < nplate.centre[0])
		{
		  // std::cout << "Gate 2.5" << std::endl;
		 asol(i,j) = 2*cos(theta)*(r-pow(cobj.radius,2)/r)*(nplate.potential*(nplate.centre[0]-pplate.centre[0]))/(pow((nplate.centre[0]-pplate.centre[0]),2)-pow(cos(theta),2)*pow(cobj.radius,2));
		}

	      // std::cout << "Gate 3" << std::endl;
	      outfile << j << " " << i << " " << asol(i,j) << std:: endl;
	      // std::cout << "--------------------------------" << std::endl;

	  //  std::cout << "*********************************" << std::endl;
	}
    }
  //int ep_s=clock();
 // std::cout<<"Analytical Method time: " << ( ep_s-bp_s )/double(CLOCKS_PER_SEC)<<" seconds" <<std::endl;


  outfile.close();
}

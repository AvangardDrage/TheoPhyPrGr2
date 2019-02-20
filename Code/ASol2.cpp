#include <iostream>
#include "ASol2.h"

//This program computes the analyical solution for the second analytical problem


void ASol2(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& asol, Circle& cobj, Plate& pplate, Plate& nplate)
{


  double r;
  double ctheta;			  //independent variables in cylindical 
	
  std::ofstream outfile;
  std::ofstream cosdata;
  outfile.open("a_sol_2.dat");
  cosdata.open("cosdata.dat");

   
  cosdata << "j i rx ry r ctheta" << std::endl;

  int bp_s=clock();
  //Calculate the analytical solution
  for (int i = 0; i < asol.rows(); i++)
    {
      //std::cout << "*********************************" << std::endl;
      for (int j = 0; j < asol.cols(); j++)
	{

	  double rx = static_cast<double>(j-cobj.centre[1]);
	  double ry = static_cast<double>(i-cobj.centre[0]);
	  
	  double dist_xy = sqrt(pow(static_cast<double>(j),2)+pow(static_cast<double>(i),2));
	  double ctheta = (static_cast<double>(j))/dist_xy;
	  double dist_c = sqrt(pow(cobj.centre[0],2)+pow(cobj.centre[1],2)); 
	  // if(j!=cobj.centre[1])
	  //   {

	      // convert cartesian into 2d cylindical coordinate
	      r = sqrt(pow(rx,2)+pow(ry,2));
	      //     ctheta = rx/r;
	      double cthetaprime = (static_cast<double>(j)+dist_c*ctheta)/r;


	      // std::cout << "----------------------------------------" << std::endl;
	      // std::cout << "x: " << j << "; y: " << i << std::endl;
	      // std::cout << "dist_xy: " << dist_xy << std::endl;
	      // std::cout << "ctheta: " << ctheta << std::endl;
	      // std::cout << "x_c: " << cobj.centre[1] << "; y_c: " << cobj.centre[0] << std::endl;
	      // std::cout << "dist_c: " << dist_c << std::endl;
	      // std::cout << "rx: " << rx << "; ry: " << ry << std::endl;
	      // std::cout << "r: " << r << std::endl;
	      // std::cout << "ctheta': " << cthetaprime << std::endl;
	      
	      if(j <= pplate.centre[0])
	      	{
	      	  asol(i,j) = pplate.potential;
	      	}
	      else if(j>=nplate.centre[0])
	      	{
	      	  asol(i,j) = nplate.potential;
	      	}

	      else if (r <= cobj.radius)
	      	{
	      	  asol(i,j)=0;
	      	}
	      //else calculate the solution between r=a to r=d/cos(theta) from the analytical solution
	      // on the negative x-axis, potential is set to +V, on the positive it is -V
	      else if (j < cobj.centre[1])
	      	{
		  asol(i,j) = (cthetaprime)*((pow(r,2)-pow(cobj.radius,2))/r)*(pplate.potential*(static_cast<double>(nplate.centre[1]-pplate.centre[1])))/(pow((static_cast<double>(nplate.centre[1]-pplate.centre[1])),2)-pow(cthetaprime,2)*pow(cobj.radius,2));

		  // std::cout << "-------------" << std::endl;
		  // std::cout << j << ", " << i << ": " << std::endl;
		  // std::cout << "ctheta': " << (cthetaprime) << std::endl;
		  // std::cout << "(r^2-a^2)/r: " << ((pow(r,2)-pow(cobj.radius,2))/r) << std::endl;
		  // std::cout << "V * d: " <<(pplate.potential*(static_cast<double>(nplate.centre[0]-pplate.centre[0]))) << std::endl;
		  // std::cout << "d^2 - ctheta' ^2 * a^2: " << (pow((static_cast<double>(nplate.centre[0]-pplate.centre[0])),2)-pow(cthetaprime,2)*pow(cobj.radius,2)) << std::endl;
		  
	      	  //asol(i,j) = (cthetaprime)*(r-pow(cobj.radius,2)/r)*(pplate.potential*(static_cast<double>(nplate.centre[1]-pplate.centre[1])))/(pow((static_cast<double>(nplate.centre[1]-pplate.centre[1]),2)-pow((cthetaprime),2)*pow(cobj.radius,2)));
	      	}
	      else if (j > cobj.centre[1])
	      	{
		  // std::cout << j << ", " << i << ": " << (cthetaprime)*((pow(r,2)-pow(cobj.radius,2))/r)*(nplate.potential*(static_cast<double>(nplate.centre[0]-pplate.centre[0])))/(pow((static_cast<double>(nplate.centre[0]-pplate.centre[0])),2)-pow(cthetaprime,2)*pow(cobj.radius,2)) << std::endl;

		  // std::cout << "-------------" << std::endl;
		  // std::cout << j << ", " << i << ": " << std::endl;
		  // std::cout << "ctheta': " << (cthetaprime) << std::endl;
		  // std::cout << "(r^2-a^2)/r: " << ((pow(r,2)-pow(cobj.radius,2))/r) << std::endl;
		  // std::cout << "V * d: " <<(nplate.potential*(static_cast<double>(nplate.centre[0]-pplate.centre[0]))) << std::endl;
		  // std::cout << "d^2 - ctheta' ^2 * a^2: " << (pow((static_cast<double>(nplate.centre[0]-pplate.centre[0])),2)-pow(cthetaprime,2)*pow(cobj.radius,2)) << std::endl;



		  asol(i,j) = (cthetaprime)*((pow(r,2)-pow(cobj.radius,2))/r)*(nplate.potential*(static_cast<double>(nplate.centre[0]-pplate.centre[0])))/(pow((static_cast<double>(nplate.centre[0]-pplate.centre[0])),2)-pow(cthetaprime,2)*pow(cobj.radius,2));
	      	  //asol(i,j) = (cthetaprime)*(r-pow(cobj.radius,2)/r)*(nplate.potential*(static_cast<double>(nplate.centre[1]-pplate.centre[1])))/(pow((static_cast<double>(nplate.centre[1]-pplate.centre[1]),2)-pow((cthetaprime),2)*pow(cobj.radius,2)));
	      	}
	      // std::cout << "asol(i,j): " << asol(i,j) << std::endl;
	      // std::cout << "----------------------------------------" << std::endl;
     	      outfile << j << " " << i << " " << asol(i,j) << std:: endl;
	      cosdata << j << " " << i << " " << rx << " " << ry << " "<<  r << " " << ctheta << std::endl;
	    }
	}
  //    }
  int ep_s=clock();
  std::cout<<"Analytical Method time: " << ( ep_s-bp_s )/double(CLOCKS_PER_SEC)<<" seconds" <<std::endl;

  outfile.close();
}




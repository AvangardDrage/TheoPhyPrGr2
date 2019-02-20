#include "AimSolver.h"
#include "ASol1.h"

void ASol1(Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& asol, Circle cobj, Shell sobj)
{
  double r;   //independent variables in cylindical coordinate
  
  double rc = static_cast<double> (cobj.radius);  // cylinder radius
  double ri = static_cast<double> (sobj.iradius); // inner radius
  double ro = static_cast<double> (sobj.oradius); // outer radius


  double x0,y0;
  
  std::ofstream outfile;
  outfile.open("a_sol_1.dat");
  

  int bp_s = clock();
  
  for (int i = sobj.centre[0]-sobj.oradius; i < sobj.centre[0]+sobj.oradius; i++)
    {
      for (int j = sobj.centre[1]-sobj.oradius; j < sobj.centre[1]+sobj.oradius; j++)
	{ 

	  //std::cout << "i: " << i << ", j: " << j << std::endl;
	  
	  //convert cartesian into 2d cylindical coordinate
	  double rx = static_cast<double>(j - cobj.centre[1]);
	  double ry = static_cast<double>(i - cobj.centre[0]);
	 
	  r = sqrt(pow(rx,2)+pow(ry,2));
	  
	  //calculate the solution
	  
	  //if r < a then the potnetial is zero as it is insinde the grounded cylinder
	  if (r < rc)
	    {
	      asol(i,j) = 0;
	    }
	  else if (r > ro)
	    {
	      asol(i,j) = sobj.potential;
	    }		    
	  //otherwise, calculate the potential inbetween a and b from the analytical solution
	  else
	    {
	      asol(i,j) = sobj.potential*log(r/rc)/log(ri/rc);
	    }
	  
	  outfile << j << " " << i << " " << asol << std::endl;
	}
    }

  int ep_s = clock();

  std::cout<<"Analytical Method time: " << ( ep_s-bp_s )/double(CLOCKS_PER_SEC)<<" seconds" <<std::endl;
  outfile.close();
}




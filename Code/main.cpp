#include <iostream>
#include <Eigen/Dense>
#include "ObjectInput.h"
#include "Boundary.h"

int main()
{
  int n;
  std::cout<< "Enter row and column number: ";
  std::cin >> n;
  Eigen::Matrix <bool,10,10> lgrid(n,n); // logic grid
  Eigen::Matrix <double,10,10> pgrid(n,n); // potential grid
  
  for(int i=0; i<lgrid.rows();i++)
    {
      for(int j=0; j<lgrid.cols(); j++)
	{
	  lgrid(i,j) = true;
	  pgrid(i,j) = 0;
	}
    }

  bool another;
  Box bobj;
  Circle cobj;
  Plate pobj;
  char g;
  int xc, yc;
  double p;

  do
    {
      another = false;
      char o;
      char t;
      std::cout << "Please choose an object (B,C, or P) to insert: ";
      std::cin >> o;
      
      switch(o){
      case 'B' :
	
	int w,l;

	std::cout <<"Please enter the x coordinate of the centre: ";
	std::cin >> xc;
	bobj.centre[0]=xc;

	std::cout <<"Please enter the y coordinate of the centre: ";
	std::cin >> yc;
	bobj.centre[1]=yc;

	std::cout <<"Width of the box: ";
	std::cin >> w;
	bobj.width = w;

	std::cout << "Lenght of the box: ";
	std::cin >> l;
	bobj.length = l;

	std::cout << "Is the object grounded?('y' or 'n'): ";
	std::cin >> g;
       

	if(g=='n')
	  {
	    std::cout << "Specify potential of bobject: ";
	    std::cin >> p;

	    bobj.potential = p;
	  }
	else
	  {
	    bobj.potential = 0;
	  }
	
	
        BGD(lgrid, bobj);
        BPD(pgrid, bobj);

      	break;
      case 'C' :
	int r;
	

	std::cout <<"Please enter the x coordinate of the centre: ";
	std::cin >> xc;
	cobj.centre[0]=xc;

	std::cout <<"Please enter the y coordinate of the centre: ";
	std::cin >> yc;
	cobj.centre[1]=yc;

	std::cout <<"Radius of Circle: ";
	std::cin >> r;
	cobj.radius = r;

	std::cout << "Is the object grounded?('y' or 'n'): ";
	std::cin >> g;
       

	if(g=='n')
	  {
	    std::cout << "Specify potential of object: ";
	    std::cin >> p;

	    cobj.potential = p;
	  }
	else
	  {
	    cobj.potential = 0;
	  }
	
	
        CGD(lgrid, cobj);
        CPD(pgrid, cobj);
	

      	break;
      case 'P' :
	char vert, pos;
	
	std::cout <<"Please enter the x coordinate of an end: ";
	std::cin >> xc;
	pobj.centre[0]=xc;

	std::cout <<"Please enter the y coordinate of an end: ";
	std::cin >> yc;
	pobj.centre[1]=yc;

	std::cout <<"Is the plate vertical? ('y' or 'n'): ";
	std::cin >> vert;
	if(vert=='n'){pobj.direction[0]=false;}
	
	std::cout <<"Moving Right/Down? ('y' or 'n'): ";
	std::cin >> pos;
	if(vert=='n'){pobj.direction[1]=false;}

	std::cout << "Is the object grounded?('y' or 'n'): ";
	std::cin >> g;
       

	if(g=='n')
	  {
	    std::cout << "Specify potential of object: ";
	    std::cin >> p;

	    pobj.potential = p;
	  }
	else
	  {
	    pobj.potential = 0;
	  }

        PGD(lgrid, pobj);
        PPD(pgrid, pobj);


      	break;
      default:
	std::cout << "Entered undefined object class, please try again." << std::endl;
	another = true;
      }

      std::cout << "Would you like to insert another object? ('y' or 'n')" <<std:: endl;
      std::cin >> t;
      
      if(t=='y')
	{
	  another = true;
	}

    }while(another);

      std::cout << "Logic grid" << std::endl;
      std::cout << lgrid << std::endl;
      std::cout << std::endl;
      std::cout << "Potential grid" << std::endl;
      std::cout << pgrid << std::endl;





  return 0;
}

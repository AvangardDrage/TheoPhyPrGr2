#include "BDef.h"


void BDef(Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid)
{
  bool another;
  Box bobj;
  Circle cobj;
  Plate pobj;
  Shell sobj;
  char g;
  int xc, yc;
  double p;

do
    {
      another = false;
      char o;
      char t;
      std::cout << "Please choose an object (B(ox),C(ircle), P(late), or S(hell)) to insert: ";
      std::cin >> o;
      
      switch(o){
	/* ------ Box Case ----- */ 
      case 'B' :
	
	int w,l;

	std::cout <<"Please enter the x coordinate of the corner (smaller value): ";
	std::cin >> xc;
	bobj.corner[1]=xc;

	std::cout <<"Please enter the y coordinate of the corner (smaller value): ";
	std::cin >> yc;
	bobj.corner[0]=yc;

	std::cout <<"Width (x-direction) of the box: ";
	std::cin >> w;
	bobj.xwidth = w;

	std::cout << "Lenght (y-direction) of the box: ";
	std::cin >> l;
	bobj.ywidth = l;

	std::cout << "Is the object grounded?('y' or 'n'): ";
	std::cin >> g;
       

	if(g=='n')
	  {
	    std::cout << "Specify potential of object: ";
	    std::cin >> p;

	    bobj.potential = p;
	  }
	else
	  {
	    bobj.potential = 0;
	  }
	
	
        BGD(lgrid, pgrid, bobj);
        //BPD(pgrid, bobj);

      	break;	
	/* ----- Circle case ----- */
      case 'C' :
	int r;
	

	std::cout <<"Please enter the x coordinate of the centre: ";
	std::cin >> xc;
	cobj.centre[1]=xc;

	std::cout <<"Please enter the y coordinate of the centre: ";
	std::cin >> yc;
	cobj.centre[0]=yc;

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
	
	
        CGD(lgrid, pgrid, cobj);
        //CPD(pgrid, cobj);
	

      	break;
	/* ----- Plate Case ----- */ 
      case 'P' :
	char vert, pos;
	
	std::cout <<"Is the plate vertical? ('y' or 'n'): ";
	std::cin >> vert;

	if(vert=='y') // vertical
	  {
	    pobj.direction[0]=true;
	    
	    std::cout << "Choose the starting/finishing coordinate in x: ";
	    std::cin >> xc;
	    pobj.centre[0]=xc;
	    
	    std::cout << "Does the plate extend to [+]ve x? ('y' or 'n'): ";
	    std::cin >> pos;
	    if(pos=='y') // to the right
	      {
		pobj.direction[1]=true;
	      }
	    else // to the left
	      {
		pobj.direction[1]=false;
	      }
	  }
	else // horizontal
	  {
	    pobj.direction[0]=false;
	    
	    std::cout << "Choose the starting/finishing coordinate in y: ";
	    std::cin >> yc;
	    pobj.centre[1]=yc;
	    
	    std::cout << "Does the plate extend to [+]ve y? ('y' or 'n'): ";
	    std::cin >> pos;
	    if(pos=='y') // down
	      {
		pobj.direction[1]=true;
	      }
	    else // up
	      {
		pobj.direction[1]=false;
	      }
	  }

	
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

        PGD(lgrid, pgrid, pobj);
        //PPD(pgrid, pobj);

      	break;
	/* ----- Shell case ----- */
      case 'S':

	int a,b;

	std::cout <<"Please enter the x coordinate of the centre: ";
	std::cin >> xc;
	sobj.centre[1]=xc;

	std::cout <<"Please enter the y coordinate of the centre: ";
	std::cin >> yc;
	sobj.centre[0]=yc;

	std::cout <<"Outer Radius of Shell: ";
	std::cin >> b;
	sobj.oradius = b;

	std::cout <<"Inner Radius of Shell: ";
	std::cin >> a;
	sobj.iradius = a;

	std::cout << "Is the object grounded?('y' or 'n'): ";
	std::cin >> g;
       

	if(g=='n')
	  {
	    std::cout << "Specify potential of object: ";
	    std::cin >> p;

	    sobj.potential = p;
	  }
	else
	  {
	    sobj.potential = 0;
	  }
	
	
        SGD(lgrid, pgrid, sobj);
        //SPD(pgrid, cobj);

	break;
      default:
	std::cout << "Entered undefined object class, please try again." << std::endl;
	another = true;
      }

	  std::cout << "Would you like to insert another object? ('y' or 'n'): ";
	  std::cin >> t;
      
      if(t=='y')
	{
	  another = true;
	}
    }while(another);
}

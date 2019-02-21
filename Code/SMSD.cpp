#include "SMSD.h"

void SMSD(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid)
{

  Plate tplate;
  Plate bplate;

  tplate.direction[0]=false;
  tplate.direction[1]=true;
  
  bplate.direction[0]=false;
  bplate.direction[1]=false;

  int mode;
  int height;
  int number;
  int length;
  int twidth;
  int bwidth;
  double tpotential;
  double bpotential;
  
  
  std::cout << "Please choose Silicon MicroStrip Detector (SMSD) layout definition method: " << std::endl;
  std::cout << "[1] User defined number of implants" << std::endl;
  std::cout << "[2] User defined side lenght (x-direction) of implants" << std::endl;
  std::cout << "Please enter corresponding number: ";
  std::cin >> mode;

  std::cout << "Please define the height (y-direction) of implants: ";
  std::cin >> height;
 
  std::cout << "Please define the width (y-direction) of the bottom plate: ";
  std::cin  >> bwidth;
  std::cout << "Please define the potential of bottom plate (i.e. +V): ";
  std::cin >> bpotential;
  
  bplate.centre[1] = bwidth;
  bplate.potential = bpotential;
  PGD(lgrid, pgrid, bplate);

  std::cout << "Please define the width (y-direction) of the top plate: ";
  std::cin  >> twidth;
  std::cout << "Please define the potential of top plate (0 for GND): ";
  std::cin >> tpotential;
  
  tplate.centre[1] = lgrid.rows()-twidth;
  tplate.potential = tpotential;
  PGD(lgrid, pgrid, tplate);

  switch(mode){

  case 1:
    std::cout << "Please define the number of implants: ";
    std::cin >> number;

    length = static_cast<int>((static_cast<double>(lgrid.cols()))/(static_cast<double>(2*number + 1)));
       
    for(int i=0; i < number; i++)
      {
	Box bobj;
	bobj.corner[0]= lgrid.rows()-twidth-length;
	bobj.corner[1] = (2*i + 1)*length;
	bobj.potential = 0;
	bobj.xwidth = length;
	bobj.ywidth = height;

	BGD(lgrid, pgrid, bobj);
      }
    

    sor(pgrid, lgrid);
    break;

  case 2:
    
    std::cout << "Please define the side length (x-direction) of implants: ";
    std::cin >> length;

    number = static_cast<int>(((static_cast<double>(lgrid.cols())/static_cast<double>(length))-1)*0.5);
    
    
    for(int i=0; i < number; i++)
      {
	Box bobj;
	bobj.corner[0]= lgrid.rows()-twidth-length;
	bobj.corner[1] = (2*i + 1)*length;
	bobj.potential = 0;
	bobj.xwidth = length;
	bobj.ywidth = height;

	BGD(lgrid, pgrid, bobj);
      }

    int random = sor(pgrid, lgrid);
    break;

  }




}

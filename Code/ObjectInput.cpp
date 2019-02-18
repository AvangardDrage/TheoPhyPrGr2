// ObjectInput funtions created by Gediminas Glemza
// Version 1.0
// Descriptions of functions:
//
// 1) set_centre takes in two parametres and sets them as the coordinate 
//    of the object centre.
//
// 2) set_parametres: takes in two parameters and sets them as
//    width and length of the box
//
// 3) set_radius: takes in a single parameter and sets it as the
//    radius of the circle
//
// 4) set_length: takes in a single parameter and sets it as the 
//    length of the wire
//
// 5) set_direction: takes in two parameters and sets them as the 
//    directional increases in x and y directions.
//
// 6) set_potential: takes in one parameter, checks if the object 
//    is set as Ground, if yes - Potential is set to 0; 
//    if no parameter is set as the potential.


#include "ObjectInput.h"


/* Constructor */

Box::Box()
{
  corner.clear();
  corner.push_back(0);
  corner.push_back(0);
  xwidth = 0;
  ywidth = 0;
  ground = true;
  potential = 0.0;

}

Circle::Circle()
{
  centre.clear();
  centre.push_back(0);
  centre.push_back(0);
  radius = 0;
  ground = true;
  potential = 0.0;

}

Plate::Plate()
{
  centre.clear();
  centre.push_back(0);
  centre.push_back(0);
  direction.clear();
  direction.push_back(true); //plate is vertical
  direction.push_back(true); //plate is in positive x
  ground = true;
  potential = 0.0;

}

Shell::Shell()
{
  centre.clear();
  centre.push_back(0);
  centre.push_back(0);
  iradius = 0;
  oradius = 0;
  ground = true;
  potential = 0.0;
}

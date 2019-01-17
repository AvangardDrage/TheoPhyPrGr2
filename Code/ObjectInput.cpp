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



#include <vector>
#include "ObjectInput.h"

/* Box class functions */

void Box::set_centre (double x, double y)
{
  centre.clear();
  centre.push_back(x);
  centre.push_back(y);
}

void Box::set_parameters (double x, double y)
{
  width = x;
  length = y;
}

void Box::set_potential (double V)
{
  if(ground)
    {
      potential = 0;
    }
  else
    {
      potential = V;
    }
}

/* Circle class functions */

void Circle::set_centre (double x, double y)
{
  centre.clear();
  centre.push_back(x);
  centre.push_back(y);
}

void Circle::set_radius (double r)
{
  radius = r;
}

void Circle::set_potential (double V)
{
  if(ground)
    {
      potential = 0;
    }
  else
    {
      potential = V;
    }
}

/* Wire Class functions */ 

void Wire::set_centre (double x, double y)
{
  centre.clear();
  centre.push_back(x);
  centre.push_back(y);
}

void Wire::set_length (double l)
{
  length = l;
}

void Wire::set_direction (double xdir, double ydir)
{
  direction.clear();
  direction.push_back(xdir);
  direction.push_back(ydir);
}

void Wire::set_potential (double V)
{
  if(ground)
    {
      potential = 0;
    }
  else
    {
     potential = V;
    }
}

/* Boundary Class functions */
void Boundary::set_centre (double x, double y)
{
  centre.clear();
  centre.push_back(x);
  centre.push_back(y);
}

void Boundary::set_direction (double xdir, double ydir)
{
  direction.clear();
  direction.push_back(xdir);
  direction.push_back(ydir);
}

void Boundary::set_potential (double V)
{
  if(ground)
    {
      potential = 0;
    }
  else
    {
      potential = V;
    }
}

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
  centre.clear();
  centre.push_back(0);
  centre.push_back(0);
  width = 0;
  length = 0;
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

/* Box Class Functions */

void Box::set_centre (int x, int y)
{
  centre.clear();
  centre.push_back(x);
  centre.push_back(y);
}

void Box::set_parameters (int x, int y)
{
  width = x;
  length = y;
}

void Box::set_potential (int V)
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

void Circle::set_centre (int x, int y)
{
  centre.clear();
  centre.push_back(x);
  centre.push_back(y);
}

void Circle::set_radius (int r)
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

// /* Wire Class functions */ 

// void Wire::set_centre (double x, double y)
// {
//   centre.clear();
//   centre.push_back(x);
//   centre.push_back(y);
// }

// void Wire::set_length (double l)
// {
//   length = l;
// }

// void Wire::set_direction (double xdir, double ydir)
// {
//   direction.clear();
//   direction.push_back(xdir);
//   direction.push_back(ydir);
// }

// void Wire::set_potential (double V)
// {
//   if(ground)
//     {
//       potential = 0;
//     }
//   else
//     {
//      potential = V;
//     }
// }

/* Plate Class functions */
void Plate::set_centre (int x, int y)
{
  centre.clear();
  centre.push_back(x);
  centre.push_back(y);
}

void Plate::set_direction (bool vert, bool pos)
{
  direction.clear();
  direction.push_back(vert);
  direction.push_back(pos);
}


// void Plate::set_direction (double xdir, double ydir)
// {
//   direction.clear();
//   direction.push_back(xdir);
//   direction.push_back(ydir);
// }

void Plate::set_potential (double V)
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

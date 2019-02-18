// Requires: iostream, vector

#ifndef OBJECTINPUT_H
#define OBJECTINPUT_H

#include <vector>
 
class Box{
 public:
  std::vector<int> corner;
  int xwidth;
  int ywidth;
  bool ground;
  double potential;

  Box();
};

class Circle{
 public:
  std::vector<int> centre;
  int radius;
  bool ground;
  double potential;

  Circle();
};


class Shell{
 public:
  std::vector<int> centre;
  int iradius; // inner radius
  int oradius; // outer radius
  bool ground;
  double potential;

  Shell();
};

class Plate{
 public:
  std::vector<int> centre;
  std::vector<bool> direction; 
  // direction(vert,pos): if vert=yes => plate is vertical, pos=yes => extension to the [+] direction
  bool ground;
  double potential;

  Plate();
};
		      



#endif

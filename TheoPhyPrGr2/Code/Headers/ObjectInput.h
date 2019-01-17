// Requires: iostream, vector

#ifndef OBJECTINPUT_H
#define OBJECTINPUT_H

#include <vector>
 
class Box{
 public:
  std::vector<double> centre;
  double width;
  double length;
  bool ground;
  double potential;

  void set_centre (double x,double y);
  void set_parameters (double width, double length);
  void set_potential (double potential); 
};

class Circle{
 public:
  std::vector<double> centre;
  double radius;
  bool ground;
  double potential;

  void set_centre (double x, double y);
  void set_radius (double radius);
  void set_potential (double potential);
};


class Wire{
 public:
  std::vector<double> centre;
  std::vector<double> direction;
  double length;
  bool ground;
  double potential;

  void set_centre (double x, double y);
  void set_length (double length);
  void set_direction (double xdir, double ydir);
  void set_potential (double potential);
};

class Boundary{
 public:
  std::vector<double> centre;
  std::vector<double> direction;
  bool ground;
  double potential;

  void set_centre (double x, double y);
  void set_potential (double potental);
  void set_direction (double xdir, double ydir);
};
		      



#endif

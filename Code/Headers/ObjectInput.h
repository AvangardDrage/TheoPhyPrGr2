// Requires: iostream, vector

#ifndef OBJECTINPUT_H
#define OBJECTINPUT_H

#include <vector>
 
class Box{
 public:
  std::vector<int> centre;
  int width;
  int length;
  bool ground;
  double potential;

  Box();

  void set_centre (int x,int y);
  void set_parameters (int width, int length);
  void set_potential (int potential);
};

class Circle{
 public:
  std::vector<int> centre;
  int radius;
  bool ground;
  double potential;

  Circle();

  void set_centre (int x, int y);
  void set_radius (int radius);
  void set_potential (double potential);
};


/* class Wire{ */
/*  public: */
/*   std::vector<double> centre; */
/*   std::vector<double> direction; */
/*   double length; */
/*   bool ground; */
/*   double potential; */

/*   void set_centre (double x, double y); */
/*   void set_length (double length); */
/*   void set_direction (double xdir, double ydir); */
/*   void set_potential (double potential); */
/* }; */

class Plate{
 public:
  std::vector<int> centre;
  std::vector<bool> direction;
  bool ground;
  double potential;

  Plate();

  void set_centre (int x, int y);
  void set_potential (double potental);
  //void set_direction (double xdir, double ydir);
  void set_direction (bool vert, bool pos); // if vert=yes => plate is vertical, pos=yes => extension to the [+] direction

};
		      



#endif

// Requires: iostream, vector

#ifndef ObjectInput.h
#define ObjectInput.h
 
#include<vector>

class Box{
public:
  std::vector<double> centre;
  double width;
  double lenght;
  bool ground;
  double potential;

  void set_centre (double, double);
  void set_parameters (double, double);
  void set_potential (double); 
};

class Circle{
public:
  std::vector<double> centre;
  double radius;
  bool ground;
  double potential;

  void set_centre (double, double);
  void set_radius (double);
  void set_potential (double);
};


class Wire{
public:
  std::vector<double> centre;
  atd::vector<double> direction;
  double lenght;
  bool ground;
  double potential;

  void set_centre (double, double);
  void set_length (double);
  void set_direction (double, double); 
  void set_potential (double);
};

class Boundary{
public:
  std::vector<double> centre;
  std::vector<double> direction;
  bool Ground;
  double Potential;

  void set_centre (double, double);
  void set_potential (double);
  void set_direction (double, double);
};

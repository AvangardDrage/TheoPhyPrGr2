// Requires: iostream, vector

#ifndef ObjectInput.h
#define ObjectInput.h
 
class Box{
  vector<double> centre;
  double width;
  double lenght;
  bool ground;
  double potential;

public:
  void set_centre (double, double);
  void set_parameters (double, double);
  void set_potential (double); 
};

class Circle{
  vector<double> centre;
  double radius;
  bool ground;
  double potential;

public:
  void set_centre (double, double);
  void set_radius (double);
  void set_potential (double);
};


class Wire{
  vector<double> centre;
  vector<double> direction;
  double lenght;
  bool ground;
  double potential;

 public:
  void set_centre (double, double);
  void set_length (double);
  void set_direction (double, double); 
  void set_potential (double);
};

class Boundary{
  vector<double> centre;
  vector<double> direction;
  bool Ground;
  double Potential;

 public:
  void set_centre (double, double);
  void set_potential (double);
  void set_direction (double, double);
};
		      


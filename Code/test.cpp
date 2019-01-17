#include <iostream>
#include <typeinfo>
#include "ObjectInput.h"

using namespace std;

int main()
{
  Box obj1;
 
  obj1.set_centre(1,2);
  obj1.set_parameters(20,30);
  obj1.ground = true;
  obj1.set_potential(5.2);
  
  cout << "Box class type: " << typeid(Box).name() << endl;
  cout << "Circle class type: " << typeid(Circle).name() << endl;
  cout << "Object type: " << typeid(obj1).name() << endl;
  cout << "Object centred at:" << obj1.centre[0] << " " << obj1.centre[1] << endl;
  cout << "Object Width: " << obj1.width << endl;
  cout << "Object Length: " << obj1.length << endl;
  cout << "[!] Object Grounded" << endl;
  cout << "Object Potential: " << obj1.potential << endl;
  cout << "[!] Object Charged" << endl;
  obj1.ground = false;
  obj1.set_potential(5.2);
  cout << "Object Potential: " << obj1.potential << endl;
  return 0;
}

#include <iostream>
#include "MeshSpace.h"

using namespace std;

int main()
{
  MeshPoint a;
  char i;

  cout << "Mesh Point created" << endl;
  cout << "Is is static (type y, n): ";
  cin >> i;

  if(i=='y')
    {
      a.predef = true;
    }
  else
    {
      a.predef = false;
    }

  cout << endl;
  cout << "Potential of the point: ";
  cin >> a.potential;

  cout << endl;
  cout << "Trying to set potential to 45" << endl;

  if(!a.predef)
    {
      a.potential = 45;
      cout << "Potential changed successfully" << endl;	
    }
  else
    {
      cout << "Potential change failed" << endl;
    }
  
   cout << "Point potential: " << a.potential << endl; 

  
  return 0;
}

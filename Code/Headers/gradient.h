#include <cmath>
#include <vector>

using namespace std;

vector< vector<double> > gradient(int n, int m, vector< vector<double> > &u) {

  double dx=0.01;
  vector< vector<double> > grad(m, vector<double> (n, 0))
  for(int j=1; j < n-1;j++) {
    for(int i=1; i < m-1; i++) {

      double Ex= 0.5*(u[i+1][j]-u[i-1][j])/dx;
      double Ey= 0.5*(u[i][j+1]-u[i][j-1])/dx;

      grad[i][j]= sqrt( pow(Ex, 2) + pow(Ey, 2));

    }
  }

  return grad;
}

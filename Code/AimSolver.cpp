#include "AimSolver.h"
#include <fstream>
#include <iomanip>

void AimSolver(Eigen::Matrix <bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic>& pgrid)
{
  
  std::ofstream adat;
  std::ofstream ndat;
  std::ofstream edat;
  
  adat.open("ASol.dat");
  ndat.open("NSol.dat");
  edat.open("Err.dat");

  Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> asol(pgrid.rows(),pgrid.cols());
asol = pgrid; // copy pgrid matrix into a separate analytical solution matrix

 Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> nsol(pgrid.rows(),pgrid.cols());
nsol = pgrid; // copy pgrid matrix into a separate numerical solution matrix

 Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> err(pgrid.rows(),pgrid.cols());

 // Eigen::Matrix <double, Eigen::Dynamic, Eigen::Dynamic> Cerr(err.rows()/2,err.cols()/2);

err  = pgrid; // create an error matrix based on pgrid matrix.

 Circle cobj;  // centre wire
 Plate pplate; // positive plate
 Plate nplate; // negative plate
 int r;
 int dist; 
 int endp; // endpoint 

 /* Centre Cylinder */

 cobj.centre[0] = static_cast<int>((lgrid.cols()-1)/2);
 cobj.centre[1] = static_cast<int>((lgrid.rows()-1)/2);
 

 std::cout << "Please specify radius of the centre circle: ";
 std::cin >> r;
 cobj.radius = r;
 cobj.potential = 0;
 CGD(lgrid, nsol,cobj);

   /* Side Plates */
 std::cout << "Please specify the distance between two plates: ";
 std::cin >> dist;

 endp = static_cast<int>((lgrid.cols()-1-dist)/2);

 pplate.centre[0] = endp;
 pplate.direction[0] = true; // vertical 
 pplate.direction[1] = false; // to the left
 pplate.potential = 1;
 PGD(lgrid, nsol, pplate);
 
 nplate.centre[0] = lgrid.cols()-1-endp;
 nplate.direction[0] = true; // vertical
 nplate.direction[1] = true; // to the right
 nplate.potential = -1;
 PGD(lgrid, nsol, nplate);

 // std::cout << "Hello 1 " << std::endl;
 // std::cout << "Lgrid: " << std::endl << lgrid << std::endl;
 // std::cout << "Hello 2 " << std::endl;

 // std::cout << "NSol before method: " << std::endl << nsol << std::endl;
 // std::cout << "ASol before method: " << std::endl << asol << std::endl;



 // std::cout << "Numerical Method Start" << std::endl;
 sor(1,1,nsol,lgrid); // numerical method
 // std::cout << "Numerical Method End" << std::endl;
 // std::cout << "Analytical Method Start" << std::endl;
 ASol2(asol,cobj,pplate,nplate); // analytical method
 // std::cout << "Analytical Method End" << std::endl;

 //std::cout << "NSol after method: " << std::endl << nsol << std::endl;
 //std::cout << "ASol after method: " << std::endl << asol << std::endl;




 for(int i=0;i<lgrid.rows();i++)
   {
     for(int j=0;j<lgrid.cols();j++)
       {
	 if(j!=cobj.centre[0])
	   {
	     if(lgrid(i,j))
	       {
		 err(i,j)= sqrt(pow((asol(i,j)-nsol(i,j)),2));
	       }		    
	     else
	       {
		 err(i,j) = 0;
	       }
	   }
       }
   }

 double nze = 0.0;
 double nzs = 0.0;

 for(int i=0;i<err.rows();i++)
   {
     for(int j=0;j<err.cols();j++)
       {
	 if(lgrid(i,j) || (j!=cobj.centre[0]))
	   {
	     nzs = nzs+err(i,j);
	     nze++;
	   }
       }
   }
	 
   

	     
 // std::cout << "----------------------" << std::endl;
 // std::cout << "Err rows: " << err.rows() << std::endl;
 // std::cout << "Err cols: " << err.cols() << std::endl;
 // std::cout << "Err mean: " << nzs/nze << std::endl;
 // std::cout << "Max b: " << err.maxCoeff() << std::endl;
 // std::cout << "Min b: " << err.minCoeff() << std::endl;
 // std::cout << "Err Matrix: "<<std::endl << err << std::endl;

 // int rk = 0;


 // for(int i=0;i<lgrid.rows();i++)
 //   {
 //     bool cerrt;
 //     int cl = 0;
 //     cerrt = false;
 //     for(int j=0;j<lgrid.cols();j++)
 //       {
 // 	 if(err(i,j)!=0)
 // 	   {
 // 	     Cerr(rk,cl) = err(i,j);
 // 	     cl++;
 // 	     cerrt = true;
 // 	     // adat << std::fixed << std::setprecision(2) << asol(i,j) << " ";
 // 	     // ndat << std::fixed << std::setprecision(2) << nsol(i,j) << " ";
 // 	   }
 // 	 }
 //     if(cerrt)
 //       {
 // 	 rk++;
 //       }
 //   }



 // std::cout << "----------------------" << std::endl;
 // std::cout << "Cerr rows: " << Cerr.rows() << std::endl;
 // std::cout << "Cerr cols: " << Cerr.cols() << std::endl;
 // std::cout << "Cerr mean: " << Cerr.mean() << std::endl;
 // std::cout << "Max b: " << Cerr.maxCoeff() << std::endl;
 // std::cout << "Min b: " << Cerr.minCoeff() << std::endl;
 // std::cout << "Cerr Matrix: "<<std::endl << Cerr << std::endl;


 std::cout << "Precision of the Eigen SOR method used in general solver: " << nzs/nze << " +- " << err.maxCoeff()-(nzs/nze) << std::endl;

 //  std::cout << "Corrected precision of the Eigen SOR method used in general solver: " << Cerr.mean() << " + " << Cerr.maxCoeff()-Cerr.mean() << " - " << Cerr.mean()-Cerr.minCoeff() << std::endl;

 adat.close();
 ndat.close();
 edat.close();

}

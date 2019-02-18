#include "Boundary.h"


/* Box Grid Definition */
 void BGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid, Box obj)
{
  for(int i=obj.corner[0];i < obj.corner[0] + obj.ywidth; i++)
    {
      for(int j = obj.corner[1] ; j < obj.corner[1] + obj.ywidth; j++)
	{
	  lgrid(i,j) = false;
	  pgrid(i,j) = obj.potential;
	}
    }
}


/* Circle Grid Definition */
void CGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid, Circle obj)
{
  for(int i = static_cast<int>(obj.centre[0]-obj.radius);i <= static_cast<int>(obj.centre[0]+obj.radius); i++)
    {
      for(int j = static_cast<int>(obj.centre[1]-obj.radius);j <= static_cast<int>(obj.centre[1]+obj.radius); j++)
	{
	  if(pow((i-obj.centre[0]),2)+ pow((j-obj.centre[1]),2) <= pow(obj.radius,2.0))	   
	    {
	      lgrid(i,j) = false;
	      pgrid(i,j) = obj.potential;
	    }
	}
    }  
}


/* Plate Grid Defininion */
void PGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid, Plate obj)
{
  if(obj.direction[0]) // vertical
    {
      if(obj.direction[1]) // +ve x
	{
	  for(int i=0;i<lgrid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j<lgrid.cols();j++)
		{
		  lgrid(i,j)=false;
		  pgrid(i,j)=obj.potential;
		}
	    }
	}
      else // -ve x
	{
	   for(int i=0;i<lgrid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j >= 0;j--)
		{
		  lgrid(i,j)=false;
		  pgrid(i,j)=obj.potential;
		}
	    }
	 }
    }


  else // horizontal
    {
      if(obj.direction[1]) // Down, +ve y
	{
	  for(int i=obj.centre[1];i<lgrid.rows(); i++)
	    {
	      for(int j=0;j<lgrid.cols();j++)
		{
		  lgrid(i,j)=false;
		  pgrid(i,j)=obj.potential;
		}
	    }
	}
      else // Up, -ve y
	{
	  for(int i=obj.centre[1];i>=0; i--)
	    {
	      for(int j=0;j<lgrid.cols();j++)
		{
		  lgrid(i,j)=false;
		  pgrid(i,j)=obj.potential;
		}
	    }
	}
    }
}


/* Shell Grid Definition */
void SGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& lgrid, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& pgrid, Shell obj)
{
  for(int i = static_cast<int>(obj.centre[0]-obj.oradius);i <= static_cast<int>(obj.centre[0]+obj.oradius); i++)
    {
      for(int j = static_cast<int>(obj.centre[1]-obj.oradius);j <= static_cast<int>(obj.centre[1]+obj.oradius); j++)
	{
	  if((pow((i-obj.centre[0]),2)+ pow((j-obj.centre[1]),2) <= pow(obj.oradius,2.0))&&(pow((i-obj.centre[0]),2)+ pow((j-obj.centre[1]),2) >= pow(obj.iradius,2.0)))	   
	    {
	      lgrid(i,j) = false;
	      pgrid(i,j) = obj.potential;
	    }
	}
    }  
}

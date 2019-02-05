#include "Boundary.h"

 void BGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& grid, Box obj)
{
  for(int i=static_cast<int>(obj.centre[0]-(0.5*obj.width));i < static_cast<int>((obj.centre[0]+(0.5*obj.width))); i++)
    {
      for(int j=floor((obj.centre[1]-(0.5*obj.length)));j<floor((obj.centre[1]+(0.5*obj.length))); j++)
	{
	  grid(i,j) = false;
	}
    }
}

void BPD (Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& grid, Box obj)
{
  for(int i = floor((obj.centre[0]-(0.5*obj.width)));i < floor((obj.centre[0]+(0.5*obj.width))); i++)
    {
      for(int j = floor((obj.centre[1]-(0.5*obj.length)));j < floor((obj.centre[1]+(0.5*obj.length))); j++)
	{
	  grid(i,j) = obj.potential;
	}
    }
}


void CPD (Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& grid, Circle obj)
{
  for(int i= static_cast<int>(obj.centre[0]-obj.radius);i <= static_cast<int>(obj.centre[0]+(obj.radius)); i++)
    {
      for(int j= static_cast<int>(obj.centre[1]-obj.radius);j <= static_cast<int>(obj.centre[1]+(obj.radius)); j++)
	{
	  if(pow((i-obj.centre[0]),2)+ pow((j-obj.centre[1]),2) <= pow(obj.radius,2.0))
	    {
	      grid(i,j) = obj.potential;
	    }
	}
    }
}

void CGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& grid, Circle obj)
{
  for(int i = static_cast<int>(obj.centre[0]-obj.radius);i <= static_cast<int>(obj.centre[0]+obj.radius); i++)
    {
      for(int j = static_cast<int>(obj.centre[1]-obj.radius);j <= static_cast<int>(obj.centre[1]+obj.radius); j++)
	{
	  if(pow((i-obj.centre[0]),2)+ pow((j-obj.centre[1]),2) <= pow(obj.radius,2.0))	   
	    {
	      grid(i,j) = false;
	    }
	}
    }  
}

void PGD (Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& grid, Plate obj)
{
  if(obj.direction[0]) // vertical
    {
      if(obj.direction[1]) // +ve x
	{
	  for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j<grid.cols();j++)
		{
		  grid(i,j)=false;
		}
	    }
	}
      else // -ve x
	{
	   for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j >= 0;j--)
		{
		  grid(i,j)=false;
		}
	    }
	 }
    }


  else // horizontal
    {
      if(obj.direction[1]) // Down, +ve y
	{
	  for(int i=obj.centre[1];i<grid.rows(); i++)
	    {
	      for(int j=0;j<grid.cols();j++)
		{
		  grid(i,j)=false;
		}
	    }
	}
      else // Up, -ve y
	{
	  for(int i=obj.centre[1];i>=0; i--)
	    {
	      for(int j=0;j<grid.cols();j++)
		{
		  grid(i,j)=false;
		}
	    }
	}
    }
}


void PPD (Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& grid, Plate obj)
{
  if(obj.direction[0]) // vertical
    {
      if(obj.direction[1]) // +ve x
	{
	  for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j<grid.cols();j++)
		{
		  grid(i,j)=obj.potential;
		}
	    }
	}
      else // -ve x
	{
	   for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j >= 0;j--)
		{
		  grid(i,j)=obj.potential;
		}
	    }
	 }
    }


  else // horizontal
    {
      if(obj.direction[1]) // Down, +ve y
	{
	  for(int i=obj.centre[1];i<grid.rows(); i++)
	    {
	      for(int j=0;j<grid.cols();j++)
		{
		  grid(i,j)=obj.potential;
		}
	    }
	}
      else // Up, -ve y
	{
	  for(int i=obj.centre[1];i>=0; i--)
	    {
	      for(int j=0;j<grid.cols();j++)
		{
		  grid(i,j)=obj.potential;
		}
	    }
	}
    }
}

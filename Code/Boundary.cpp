#include "Boundary.h"

 void BGD (Eigen::Matrix<bool, 10, 10>& grid, Box obj)
{
  for(int i=static_cast<int>(obj.centre[0]-(0.5*obj.width));i < static_cast<int>((obj.centre[0]+(0.5*obj.width))); i++)
    {
      for(int j=floor((obj.centre[1]-(0.5*obj.length)));j<floor((obj.centre[1]+(0.5*obj.length))); j++)
	{
	  grid(i,j) = false;
	}
    }
}

void BPD (Eigen::Matrix<double, 10, 10>& grid, Box obj)
{
  for(int i = floor((obj.centre[0]-(0.5*obj.width)));i < floor((obj.centre[0]+(0.5*obj.width))); i++)
    {
      for(int j = floor((obj.centre[1]-(0.5*obj.length)));j < floor((obj.centre[1]+(0.5*obj.length))); j++)
	{
	  grid(i,j) = obj.potential;
	}
    }
}


void CPD (Eigen::Matrix<double, 10, 10>& grid, Circle obj)
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

void CGD (Eigen::Matrix<bool, 10, 10>& grid, Circle obj)
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

void PGD (Eigen::Matrix<bool, 10, 10>& grid, Plate obj)
{
  if(obj.direction[0])
    {
      // vertical
      if(obj.direction[1])
	{
	  // extension to the right

	  for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j<grid.cols();j++)
		{
		  grid(i,j)=false;
		}
	    }
	}
      else
	{
	    // extension to the left
	   for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j>=grid.cols();j--)
		{
		  grid(i,j)=false;
		}
	    }
	 }
    }


  else
    {
      // longitudinal

      if(obj.direction[1])
	{
	  // extension up
	  for(int i=obj.centre[1];i>=grid.rows(); i--)
	    {
	      for(int j=0;j<grid.cols();j++)
		{
		  grid(i,j)=false;
		}
	    }
	}
      else
	{
	    // extension down

	  for(int i=obj.centre[1];i<grid.rows(); i++)
	    {
	      for(int j=0;j<grid.cols();j++)
		{
		  grid(i,j)=false;
		}
	    }
	}
    }
}


void PPD (Eigen::Matrix<double, 10, 10 >& grid, Plate obj)
{
  if(obj.direction[0])
    {
      // vertical
      if(obj.direction[1])
	{
	  // extension to the right
	  for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j<grid.cols();j++)
		{
		  grid(i,j)=obj.potential;
		}
	    }
	}
      else
	{
	    // extension to the left
	   for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.centre[0];j>=grid.cols();j--)
		{
		  grid(i,j)=obj.potential;
		}
	    }
	 }
    }


  else
    {
      // longitudinal

      if(obj.direction[1])
	{
	  // extension up
	  for(int i=obj.centre[1];i>=grid.rows(); i--)
	    {
	      for(int j=0;j<grid.cols();j++)
		{
		  grid(i,j)=obj.potential;
		}
	    }
	}
      else
	{
	    // extension down

	  for(int i=obj.centre[1];i<grid.rows(); i++)
	    {
	      for(int j=0;j<grid.cols();j++)
		{
		  grid(i,j)=obj.potential;
		}
	    }
	}
    }
}

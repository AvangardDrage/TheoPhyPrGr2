#include "BDefine.h"

//Definitions:
// B - box, C - circle, P - plate
// GD - grid definition, PD - potential definition

// For *GD, "true" => potential can be changed


Eigen::Matrix<double, Dynamic, Dynamic> BGD (Eigen::Matrix<bool, Dynamic, Dynamic> grid, ObjectInput::Box obj)
{
  for(int i=floor((obj.center[0]-(0.5*obj.width)));i<floor((obj.center[0]+(0.5*obj.width))); i++)
    {
      for(int j=floor((obj.center[1]-(0.5*obj.length)));j<floor((obj.center[1]+(0.5*obj.length))); j++)
	{
	  grid(i,j) = false;
	}
    }

  return grid;
}

Eigen::Matrix<double, Dynamic, Dynamic> BPD (Eigen::Matrix<double, Dynamic, Dynamic> grid, ObjectInput::Box obj)
{
  for(int i=floor((obj.center[0]-(0.5*obj.width)));i<floor((obj.center[0]+(0.5*obj.width))); i++)
    {
      for(int j=floor((obj.center[1]-(0.5*obj.length)));j<floor((obj.center[1]+(0.5*obj.length))); j++)
	{
	  grid(i,j) = obj.potential;
	}
    }
  
  return grid;
} 

Eigen::Matrix<double, Dynamic, Dynamic> CGD (Eigen::Matrix<bool, Dynamic, Dynamic> grid, ObjectInput::Circle obj)
{
  for(int i=floor((obj.center[0]-(0.5*obj.width)));i<floor((obj.center[0]+(0.5*obj.width))); i++)
    {
      for(int j=floor((obj.center[1]-(0.5*obj.length)));j<floor((obj.center[1]+(0.5*obj.length))); j++)
	{
	  if(pow(i,2)+ pow(j,2) <= obj.radius)
	    {
	      grid(i,j) = false;
	    }
	}
    }

  return grid;
}

Eigen::Matrix<double, Dynamic, Dynamic> CPD (Eigen::Matrix<bool, Dynamic, Dynamic> grid, ObjectInput::Circle obj)
{
  for(int i=floor((obj.center[0]-(0.5*obj.width)));i<floor((obj.center[0]+(0.5*obj.width))); i++)
    {
      for(int j=floor((obj.center[1]-(0.5*obj.length)));j<floor((obj.center[1]+(0.5*obj.length))); j++)
	{
	  if(pow(i,2)+ pow(j,2) <= obj.radius)
	    {
	      grid(i,j) = false;
	    }
	}
    }
  
  return grid;
}

Eigen::Matrix<double, Dynamic, Dynamic> PGD (Eigen::Matrix<bool, Dynamic, Dynamic> grid, ObjectInput::Plate obj)
{
  if(obj.direction[0])
    {
      // vertical
      if(obj.direction[1]
	{
	  // extension to the right
	  for(int i=0;i<grid.rows(); i++)
	    {
	      for(int j=obj.center[0];j<grid.cols();j++)
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
	      for(int j=obj.center[0];j>=grid.cols();j--)
		{
		  grid(i,j)=false;
		}
	    }
	 }
    }
  else
    {
      // longitudinal

      if(obj.direction[1]
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

      return grid;
}

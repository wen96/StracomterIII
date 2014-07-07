
#ifndef __MAINSTRUCTURES__HPP__
#define __MAINSTRUCTURES__HPP__

#ifndef PARTICLE_REAL_PRECISION
    #define PARTICLE_REAL_PRECISION float
#endif

#include "math.h"

struct triangle
{
    float  x, y, z;
    
    triangle operator - (const triangle t) const
    {
		triangle result;
		result.x = x - t.x;
		result.y = y - t.y;
		result.z = z - t.z;
		return result;
	}
	
	bool operator == (const triangle t) const
	{
		return (x==t.x) && (y==t.y) && (z==t.z);
	}
	
	double modulo (const triangle t) const
	{
		return sqrt((x-t.x)*(x-t.x) + (y-t.y)*(y-t.y) + (z-t.z)*(z-t.z));
	}
};


struct Quad
{
    float r, g, b, a;
};

#endif

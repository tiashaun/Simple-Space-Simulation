#ifndef PLANET_H
#define PLANET_H

#include <cmath>
#include <cstring>

#include "mass.h"

#define PLANET_SECTS  20                                  /* Number of sections used to draw a planet */

/**
	@author Kapone <kapone@7rc.org>
*/

    #define X 0.525731112119133606
    #define Z 0.850650808352039932

    static GLfloat vdata[12][3] = {
      {-X,0,Z},{X,0,Z},{-X,0,-Z},{X,0,-Z},
      {0,Z,X},{0,Z,-X},{0,-Z,X},{0,-Z,-X},
      {Z,X,0},{-Z,X,0},{Z,-X,0},{-Z,-X,0}
    };
    
    static GLuint tindices[20][3] = {
      {1,4,0},{4,9,0},{4,5,9},{8,5,4},{1,8,4},
      {1,10,8},{10,3,8},{8,3,5},{3,2,5},{3,7,2},
      {3,10,7},{10,6,7},{6,11,7},{6,0,11},{6,1,0},
      {10,1,6},{11,0,9},{2,11,9},{5,2,9},{11,2,7}
    };

class Planet : public Mass
{
    /* Ratios for drawing spheres */
    static const float x = 0.525731112119133606;
    static const float z = 0.850650808352039932;

    float   radius;
    int     detail;
    
    /* Functions */
    void  normalize( float v[3] );
    void  subdivide( float *, int *, float *, float *, float *, int depth = 3 );
    void  build();

public:
    Planet( float mass, float rad );
    ~Planet();

    void  set( float rad, int det );
    void  setDetail( int  det );
    void  setRadius( float rad );
};

#endif

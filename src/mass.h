#ifndef MASS_H
#define MASS_H

#include <iostream>

#include "SDL_opengl.h"

#include "matrix3.h"
#include "object3d.h"
#include "quaternion.h"
#include "vector3.h"

/**
	@author Kapone <kapone@7rc.org>
*/

class Mass : public Object3D
{
  vector<int> p_size;
  vector<char> p_type;
  vector<float*> polygons;

  inline void updateDirection();
  
protected:
  int n_arrays;              /* Number of arrays enabled */

  Vector3           acceleration;
  
  Vector3           direction;
  vector<COOR_TYPE> velocity;

  /* I doubt both are entirely */
  Quaternion  orientation;
  Matrix3     rotation;

  float mass;

public:
    Mass( float arg1 = 5.9736e24 );
    Mass( vector<COOR_TYPE>, float arg2 = 5.9736e24 );

    ~Mass();

    /* Drawing functions */
    void        addPolygons( char, float *, int );
    void        draw();
    void        erase();

		/* Public, for now */
		GLfloat			colour[4];
		GLfloat			emissive_colour[4];

		/* For lighting */
		//friend class LightSource;

    /* Properties */
    Vector3     getDirection() { return direction; };
    Vector3     getTop();
    
		void				setColour( GLfloat arg1, GLfloat arg2, GLfloat arg3,  GLfloat arg4 ) { colour[0] = arg1, colour[1] = arg2; colour[2] = arg3; colour[3] = arg4; }
		void				setEmissiveColour( GLfloat arg1, GLfloat arg2, GLfloat arg3,  GLfloat arg4 ) { emissive_colour[0] = arg1; emissive_colour[1] = arg2; emissive_colour[2] = arg3; emissive_colour[3] = arg4; }
		
    void        setMass( float arg1 ) { mass = arg1; }
    float       getMass() { return mass; }
    
    Quaternion  getOrientation();
    void        setOrientation( float angle, COOR_TYPE x, COOR_TYPE y, COOR_TYPE z );

    Vector3			getVelocity();
    void        setVelocity( vector<COOR_TYPE> );
    void        setVelocity( float x, float y, float z ) { velocity[0] = x; velocity[1] = y; velocity[2] = z; }

    /* Other functions */
    void        accelerate( float arg1 ) { acceleration += direction * arg1; }
    void        accelerate( vector<COOR_TYPE> arg1 ) { acceleration += arg1; };
    void        accelerate( float x, float y, float z ) { acceleration.x += x; acceleration.y += y; acceleration.z += z; }
    
    void        localAccelerate( float, float, float );

		void				orbitLargeObject( Mass *, float distance, float angle, Vector3 v );
    
    void        increment( float sec = 1 );
    void        rotate( double, Vector3 );
    void        rotate( double, COOR_TYPE, COOR_TYPE, COOR_TYPE );
    
    /* Debug */
    void        print();
};

#endif

#ifndef QUATERNION_H
#define QUATERNION_H

/**
	@author Kapone <kapone@7rc.org>
*/

#include "vector3.h"

class Quaternion{
public:
    union {
      struct {
        COOR_TYPE r;
        COOR_TYPE i;
        COOR_TYPE j;
        COOR_TYPE k;
      };
      COOR_TYPE data[4];
    };

public:
    Quaternion();
    Quaternion( COOR_TYPE, COOR_TYPE, COOR_TYPE, COOR_TYPE );

    ~Quaternion();

		Vector3		operator*( const Vector3 & );
    void			operator*= ( const Quaternion & );
    float&		operator[] ( const int & );
    
    void			addScaledVector( Vector3, float );
    float			getAngle();
    Vector3		getAxis();
    void			normalize();
    void			rotate( double, COOR_TYPE, COOR_TYPE, COOR_TYPE );
    void			rotateByVector( const Vector3& arg );
};

#endif

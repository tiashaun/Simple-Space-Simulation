#ifndef VECTOR3_H
#define VECTOR3_H

#include <vector>
#include <cmath>

using namespace std;

typedef float COOR_TYPE;

class Vector3{
    union {
      struct {
        COOR_TYPE x;
        COOR_TYPE y;
        COOR_TYPE z;
      };
      COOR_TYPE data[3];
    };

public:
    Vector3() : x(0), y(0), z(0) {};
    Vector3( const COOR_TYPE x, const COOR_TYPE y, const COOR_TYPE z ) : x(x), y(y), z(z) {}
    ~Vector3() {};

    /* Operator overload */
    void          operator=( vector<COOR_TYPE> arg ) { x = arg[0]; y = arg[1]; z = arg[2]; }
    void          operator+=( const COOR_TYPE arg ) { x += arg; y += arg; z += arg; }
    void          operator+=( Vector3 arg ) { x += arg.x; y += arg.y; z += arg.z; }
    void          operator+=( const vector<COOR_TYPE> &arg ) { x += arg[0]; y += arg[1]; z += arg[2]; }
    void          operator*=( const COOR_TYPE arg ) { x *= arg; y *= arg; z *= arg; }
    Vector3       operator*( const COOR_TYPE arg ) const { return Vector3( arg*x, arg*y, arg*z ); }
    COOR_TYPE&    operator[]( const int arg ) { return data[arg]; }

		Vector3				crossProduct( Vector3 & );
		COOR_TYPE			dotProduct( Vector3 & );

    void					invert() { x = -x; y = -y; z = -z; }
    void					normalize() { COOR_TYPE d = magnitude();x /= d;y /= d;z /= d; }
    void					zero() { x = 0; y = 0; z = 0; }

    COOR_TYPE			magnitude() { return sqrt( x*x + y*y + z*z ); }
		
		/* misc */
		COOR_TYPE*		getData() { return data; }
		void					setData( COOR_TYPE x, COOR_TYPE y, COOR_TYPE z ) { data[0] = x; data[1] = y; data[2] = z; }
};

#endif

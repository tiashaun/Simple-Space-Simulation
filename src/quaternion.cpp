#include "quaternion.h"
#include "Matrix3.h"

Quaternion::Quaternion()
{
}


Quaternion::Quaternion( COOR_TYPE arg1, COOR_TYPE arg2, COOR_TYPE arg3, COOR_TYPE arg4 )
{
  r = arg1;
  i = arg2;
  j = arg3;
  k = arg4;
}


Quaternion::~Quaternion()
{
}


Vector3 Quaternion::operator*( const Vector3 &v )
{
	Matrix3 m;
	
	m.setOrientation( *this );
	
	return m * v;
}


void Quaternion::operator*=( const Quaternion &m )
{
  Quaternion q = *this;

  r = q.r*m.r - q.i*m.i - q.j*m.j - q.k*m.k;
  i = q.r*m.i + q.i*m.r + q.j*m.k - q.k*m.j;
  j = q.r*m.j + q.j*m.r + q.k*m.i - q.i*m.k;
  k = q.r*m.k + q.k*m.r + q.i*m.j - q.j*m.i;
}


float& Quaternion::operator[]( const int &i )
{
  return data[i];
}


void Quaternion::addScaledVector( Vector3 v, float scale )
{
  Quaternion p, q( 0, v.x*scale, v.y*scale, v.z*scale );

  p = *this;
  p *= q;
  //q *= *this;
  r += p.r * 0.5;
  i += p.i * 0.5;
  j += p.j * 0.5;
  k += p.k * 0.5;
}

/* Returns rotation in degrees along specified axis */
float Quaternion::getAngle()
{
  return acos( r )*2 * 180.0/M_PI;
}


Vector3 Quaternion::getAxis()
{
  Vector3 ret;
  float   c;
  
  c = sin( acos(r)/2 );
  c = ( c == 0 ? 1 : c );
  ret[0] = -i/c;
  ret[1] = -j/c;
  ret[2] = -k/c;
  
  return ret;
}


void Quaternion::normalize()
{
  float d = r*r + i*i + j*j + k*k;

  if( d == 0 )
  {
    r = 1;
    return;
  }

  d = 1.0/sqrt(d);
  r *= d;
  i *= d;
  j *= d;
  k *= d;
}


void Quaternion::rotate( double angle, COOR_TYPE x, COOR_TYPE y, COOR_TYPE z )
{
  angle = angle * M_PI/180;
  Quaternion temp( cos(angle), x*sin(angle), y*sin(angle), z*sin(angle) );
  
  temp *= (*this);
  (*this) = temp;
}


void Quaternion::rotateByVector( const Vector3 &arg )
{
  Quaternion q( 0, arg.x, arg.y, arg.z );
  (*this) *= q;
  normalize();
}

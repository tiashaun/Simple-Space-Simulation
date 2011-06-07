#include "circle.h"

Circle::Circle( float radius, int arg1 )
 : Mass()
{
  set( radius, arg1 );
}


Circle::~Circle()
{
}


void Circle::set( float radius, int edges )
{
  erase();

  float* poly = new float [ edges*3 ];

  for( int i = 0; i < edges*3; i+=3 )
  {
    poly[i] = radius*sin( 2*M_PI * (float)i/edges );
    poly[i+1] = radius*cos( 2*M_PI * (float)i/edges );
    poly[i+2] = 0;
  }

  addPolygons( GL_POLYGON, poly, edges*3 );
}

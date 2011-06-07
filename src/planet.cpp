#include "planet.h"

Planet::Planet( float mass, float rad )
 : Mass( mass )
{
  n_arrays = 1;
  detail = 0;
  
  radius = rad;
  
  build();
}


Planet::~Planet()
{
}


void Planet::normalize( float v[3] )
{
  GLfloat d = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );

  if( d == 0.0 )
  {
    perror( "zero length vector" );
    return;
  }

  v[0] /= d;
  v[1] /= d;
  v[2] /= d;
}


using namespace std;
void Planet::subdivide( float *poly, int *place, float *v1, float *v2, float *v3, int depth )
{
  float v12[3], v23[3], v31[3];
  int i;

  if( depth == 0 )
  {
    memcpy( &poly[ (*place -= 3) ], v3, 3 * sizeof( *poly ) );
    //memcpy( &poly[ (*place -= 3) ], v3, 3 * sizeof( *poly ) );

    memcpy( &poly[ (*place -= 3) ], v2, 3 * sizeof( *poly ) );
    //memcpy( &poly[ (*place -= 3) ], v2, 3 * sizeof( *poly ) );

    memcpy( &poly[ (*place -= 3) ], v1, 3 * sizeof( *poly ) );
    //memcpy( &poly[ (*place -= 3) ], v1, 3 * sizeof( *poly ) );

    return;
  }

  for( i = 0; i < 3; i++ )
  {
    v12[i] = (v1[i]+v2[i])/2;
    v23[i] = (v2[i]+v3[i])/2;
    v31[i] = (v3[i]+v1[i])/2;
  }

  normalize( v12 );
  normalize( v23 );
  normalize( v31 );

  subdivide( poly, place, v1, v12, v31, depth - 1 );
  subdivide( poly, place, v2, v23, v12, depth - 1 );
  subdivide( poly, place, v3, v31, v23, depth - 1 );
  subdivide( poly, place, v12, v23, v31, depth - 1 );
}


void Planet::build()
{
  erase();

  const int   points = 3;
  const int   numb = 20;
  int         size, temp;
  float*      poly;

  /* Number of modes * numb of vertices * depth */
  size = n_arrays * numb*points*3 * pow( (double)4, (double)detail );
  poly = new float [ size ];

  /* Done so polygons are facing outwords( coordinates anticlockwise ) */
  temp = size;
  for( int i = 0; i < numb; i++ )
  {
    subdivide( poly, &temp, &vdata[ tindices[i][0] ][0],
                            &vdata[ tindices[i][1] ][0],
                            &vdata[ tindices[i][2] ][0], detail );
  }

  for( int i = 0; i < size; i++ )
    poly[i] *= radius;

  addPolygons( GL_TRIANGLES, poly, size / 3 );
}


void Planet::set( float rad, int det )
{
  radius = rad;
  detail = det;
  build();
}


void Planet::setDetail( int det )
{
  detail = det;
  build();
}


void Planet::setRadius( float rad )
{
  radius = rad;
  build();
}

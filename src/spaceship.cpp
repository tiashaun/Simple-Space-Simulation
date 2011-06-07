#include "spaceship.h"

SpaceShip::SpaceShip( float arg1 )
 : Mass( arg1 )
{
	/*  Use interface for user */
	interface = new UserInterface( this );
	
  /* TEMP: Create ship 3km squared */
  const int   points = 4;
  const int   numb = 6;
  int         size, r;
  float       length = 100;
  float*      poly;
  
  float temp[] = { length/2, length/2, -length/2, 
                  length/2, -length/2, -length/2, 
                  -length/2, -length/2, -length/2, 
                  -length/2, length/2, -length/2,
                  -length/2, length/2, length/2,
                  -length/2, -length/2, length/2,
                  length/2, -length/2, length/2,
                  length/2, length/2, length/2 };

  /* Number of modes * numb of vertices * depth */
  size = numb*points*3;
  poly = new float [ size ];
  
  /* first ones easy */
  memcpy( poly, temp, 2*points*3*sizeof(*temp) );
  
  /* Rotate about Y axis */
  for( int i = 0; i < 8; i++ )
  {
    r = temp[i*3 + X];
    temp[i*3 + X] = -temp[i*3 + Z];
    temp[i*3 + Z] = r;
  }
  
  memcpy( poly + 2*points*3, temp, 2*points*3*sizeof(*temp) );

  /* Rotate about Z axis */
  for( int i = 0; i < 8; i++ )
  {
    r = temp[i*3 + X];
    temp[i*3 + X] = -temp[i*3 + Y];
    temp[i*3 + Y] = r;
  }
  
  memcpy( &poly[4*points*3], temp, 2*points*3*sizeof(*temp) );
  
  addPolygons( GL_QUADS, poly, size / 3 );
}


SpaceShip::~SpaceShip()
{
	delete interface;
}


Interface* SpaceShip::getInterface()
{
	return interface;
}

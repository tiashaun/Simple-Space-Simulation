#include "universe.h"

#include "mass.h"

Mass::Mass( float arg1 )
{
  mass = arg1;
  n_arrays = 1;

  location.resize( 3, 0 );
  velocity.resize( 3, 0 );
  
  /* By default everything looks down the negative Z axis */
  setOrientation( 0, 0, 0, -1 );

  p_size.clear();
  p_type.clear();
  polygons.clear();
	
	/* greyish */
	colour[0] = 0.5;
	colour[1] = 0.5;
	colour[2] = 0.5;
	colour[3] = 1;
	
	/* No emmisive light */
	emissive_colour[0] = 0;
	emissive_colour[1] = 0;
	emissive_colour[2] = 0;
	emissive_colour[3] = 1;
}


Mass::Mass( vector<COOR_TYPE> arg1, float arg2 )
{
  mass = arg2;
  n_arrays = 1;

  direction.z = -1;
  velocity.resize( 3, 0 );

  setLocation( arg1 );

  p_size.clear();
  p_type.clear();
  polygons.clear();
	
	/* greyish */
	colour[0] = 0.5;
	colour[1] = 0.5;
	colour[2] = 0.5;
	colour[3] = 1;
	
	/* No emmisive light */
	emissive_colour[0] = 0;
	emissive_colour[1] = 0;
	emissive_colour[2] = 0;
	emissive_colour[3] = 1;
}


Mass::~Mass()
{
  erase();
}


inline void Mass::updateDirection()
{
  Matrix3 m; Vector3 z( 0, 0, -1 );
  m.setOrientation( orientation );
  direction = m * z;
}


void Mass::addPolygons( char type, float *poly, int size )
{
  switch( type )
  {
    case GL_TRIANGLES:
    case GL_QUADS:
      p_size.push_back( size );
      p_type.push_back( type );
      polygons.push_back( poly );
      break;

    default:
      cout << "Polygon type not supported" << endl;
      break;
  }
}


void Mass::draw()
{
  int       i;
  vector<float*>::iterator it;
  Vector3   axis;
  
  glPushMatrix();
		
  /* Rotate and fix location */
  axis = orientation.getAxis();
  glTranslatef( location[0], location[1], location[2] );
  glRotatef( orientation.getAngle(), axis[0], axis[1], axis[2] ); 
  
  /* Cycle through polygons */
  for( it = polygons.begin(), i = 0; it < polygons.end(); it++,i++ )
  {
    /* Draw the damn thing */
		glNormalPointer( GL_FLOAT, 0, *it );
    glVertexPointer( 3, GL_FLOAT, 0, *it );

		glColor4fv( colour );
		glMaterialfv( GL_FRONT, GL_EMISSION, emissive_colour );

    glDrawArrays( p_type[i], 0, p_size[i]  );
  }
  
  glPopMatrix();
}


void Mass::erase()
{
  vector<float*>::iterator it;

  /* Cyce through polygons */
  for( it = polygons.begin(); it < polygons.end(); it++ )
    delete *it;

  p_size.clear();
  p_type.clear();
  polygons.clear();
}


Vector3 Mass::getTop()
{
  Matrix3 m;
  Vector3 ret( 0, 1, 0 );
  
  m.setOrientation( orientation );
  ret = m*ret;
  
  return ret;
}


Quaternion Mass::getOrientation()
{
  return orientation;
}


void Mass::setOrientation( float angle, COOR_TYPE x, COOR_TYPE y, COOR_TYPE z )
{
  angle = angle * M_PI/180.0;
  orientation.r = cos( angle/2 );
  orientation.i = x*sin( angle/2 );
  orientation.j = y*sin( angle/2 );
  orientation.k = z*sin( angle/2 ); 
  orientation.normalize();
  
  updateDirection();
}


Vector3 Mass::getVelocity()
{
	Vector3 v( velocity[X], velocity[Y], velocity[Z] );
	
  return v;
}


void Mass::setVelocity( vector<COOR_TYPE> arg1 )
{
  velocity = arg1;
}


void Mass::localAccelerate( float x, float y, float z )
{
  Vector3 v( x, y, z );
  Matrix3 m;
  
  m.setOrientation( orientation );
  acceleration += m*v;
}

/* Only works when mass is small compared to body being orbited, or not too close */
void Mass::orbitLargeObject( Mass* m, float distance, float angle, Vector3 v )
{
	Matrix3	mat;
	Vector3 temp( 0, 1, 0 );
	float		r_angle;
	double	velocity = sqrt( G * m->getMass() / distance );
	

	angle = angle * M_PI / 180;
	v.normalize();

	r_angle = acos( temp.dotProduct( v ) );
	temp =  temp.crossProduct( v );
	cout << r_angle << endl;
	cout << temp.magnitude() << endl;
	
	if( temp.magnitude() == 0 )
	{
		mat.setIdentity();
		mat *= v[1];
	}
	else
	{
		temp.normalize();
	
		/* Rotation Matrix */
		#define t	(1 - cos( r_angle ))
		#define s	sin( r_angle )
		#define c cos( r_angle )
		mat.setData( t*temp[X]*temp[X] + c, t*temp[X]*temp[Y] + s*temp[Z], t*temp[X]*temp[Z] - s*temp[Y],
								v[X], v[Y], v[Z],
								t*temp[X]*temp[Z] + s*temp[Y], t*temp[Y]*temp[Z] - s*temp[X], t*temp[Z]*temp[Z] + c );
		#undef t
		#undef s
		#undef c
	}
	
	v.setData( 0, 0, -distance );
	v = mat * v;

	v += m->getLocation();
	setLocation( v[X], v[Y], v[Z] );
	
	v.setData( velocity, 0, 0 );
	v = mat * v;
	v += m->getVelocity(); 
	
  setVelocity( v[X], v[Y], v[Z] );
}


void Mass::increment( float sec )
{
  location[0] += velocity[0] * sec + acceleration.x * sec*sec /2;
  location[1] += velocity[1] * sec + acceleration.y * sec*sec /2;
  location[2] += velocity[2] * sec + acceleration.z * sec*sec /2;

  
  velocity[0] += acceleration.x*sec;
  velocity[1] += acceleration.y*sec;
  velocity[2] += acceleration.z*sec;

  acceleration.zero();
}


void Mass::rotate( double angle, Vector3 axis )
{ 
  orientation.rotate( angle, axis[X], axis[Y], axis[Z] ); 
  orientation.normalize();
  updateDirection(); 
};


void Mass::rotate( double angle, COOR_TYPE x, COOR_TYPE y, COOR_TYPE z )
{ 
  orientation.rotate( angle, x, y, z ); 
  orientation.normalize();
  updateDirection();
};


void Mass::print()
{
  Vector3 temp;
  
  /* Mass */
  cout << ":Mass: " << mass << endl;
  
  /* Direction */
  cout << "Direction: ";
  cout << direction[0] << ", ";
  cout << direction[1] << ", ";
  cout << direction[2] << " modulus:";
  cout << direction.magnitude() << " ";
  
  cout << "Top: ";
  temp = getTop();
  cout << temp[0] << ", " << temp[1] << ", " << temp[2] << " ";
  
  cout << "Pitch: " << atan(direction[1]/direction[2]) * 180/M_PI << " ";
  cout << "Yaw: " << atan(direction[0]/direction[2]) * 180/M_PI << endl;
  
  /* Orientation */
  temp = orientation.getAxis();
  cout << "Orientation: ";
  cout << orientation.getAngle() << ", ";
  cout << temp[0] << ", ";
  cout << temp[1] << ", ";
  cout << temp[2] << endl;
  
  /* Acceleration */
  cout << "Acceleration: ";
  cout << acceleration.x << ", ";
  cout << acceleration.y << ", ";
  cout << acceleration.z << endl;
  
  /* Velocity */
  cout << "Velocity: ";
  cout << velocity[0] << ", ";
  cout << velocity[1] << ", ";
  cout << velocity[2] << endl;
  
  Object3D::print();
}

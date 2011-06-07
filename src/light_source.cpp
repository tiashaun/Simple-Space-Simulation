#include "light_source.h"

bool LightSource::lights_used[];

LightSource::LightSource( GLfloat arg1, GLfloat arg2, GLfloat arg3 ) {
	for( int i = 0; i < GL_MAX_LIGHTS; i++ )
		if( lights_used[ i ] == false )
		{
			lights_used[ i ] = true;
			light_numb = GL_LIGHT0;//;translate( i );
			
			break;
		}
	
	/* Light is not attached to anything initially */
	mass = NULL;
	
	setAmbient( 0, 0, 0, 1 );
	setDiffuse( arg1, arg2, arg3, 1 );
	setIntensity( arg1, arg2, arg3, 1 );
	
	enable();
}


LightSource::~LightSource() {
	disable();

	lights_used[ translate_reverse(light_numb) ] = false;
}


void LightSource::attach( Mass *m, int x, int y, int z )
{
	if( mass != NULL )
		detach();

	mass = m;	
	memcpy( m->emissive_colour, intensity, sizeof( GLfloat ) * 3 );
}


void LightSource::detach()
{
	memset( mass->emissive_colour, '\x00', sizeof( GLfloat ) * 3 );
	mass = NULL;
}


void LightSource::init() {
	for( int i = 0; i < GL_MAX_LIGHTS; i++ )
		lights_used[i] = false;
		
	glEnable( GL_LIGHTING );
	glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );

	glLighti( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1 );

	/* Enable colour tracking */
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
}


void LightSource::place() {
	Vector3 axis;
	Quaternion q;
	Vector3 l;
	
	q = mass->getOrientation();
	l = mass->getLocation();
	axis = q.getAxis();
	
	glPushMatrix();
	
	glRotatef( q.getAngle(), axis[X], axis[Y], axis[Z] );
	glTranslatef( l[X], l[Y], l[Z] );
	glLightfv( light_numb, GL_POSITION, position.getData() );
	
	glPopMatrix();
}


void LightSource::setAmbient( GLfloat x, GLfloat y, GLfloat z, GLfloat alpha )
{
	GLfloat ambient[4] = { x, y, z, alpha };

	glLightfv( light_numb, GL_AMBIENT, ambient );
}


void LightSource::setDiffuse( GLfloat x, GLfloat y, GLfloat z, GLfloat alpha )
{
	GLfloat diffuse[4] = { x, y, z, alpha };

	glLightfv( light_numb, GL_DIFFUSE, diffuse );
}


void LightSource::setIntensity( GLfloat x, GLfloat y, GLfloat z, GLfloat alpha )
{
	intensity[0] = x;
	intensity[1] = y;
	intensity[2] = z;
	intensity[3] = alpha;
	
	glLightfv( light_numb, GL_INTENSITY, intensity );
}


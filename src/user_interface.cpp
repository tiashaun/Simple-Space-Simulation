#include "user_interface.h"

UserInterface::UserInterface( Mass *m ) : Interface( m )
{
	font.init( "assets/samplefont.ttf", 16 );
	
	/* Arrows for displaying vectors */
	#define ARROW_RATIO					0.8
	#define ARROW_WIDTH_RATIO		0.2
	const GLfloat ARROW_COLOURS[][3] = { { 0xff, 0, 0 },		/* RED */
																{ 0, 0xff, 0 } };		/* GREEN */
	arrow_base = glGenLists( ARROW_SIZE );
	
	for( int i = 0; i < ARROW_SIZE; i++ )
	{
		glNewList( arrow_base + i, GL_COMPILE );
			glBegin( GL_TRIANGLES );
				glPushMatrix();
				glColor3fv( ARROW_COLOURS[ i*3 ] );
				
				/* Bottom half */
				glTranslatef( 0, -ARROW_RATIO, 0 );
				glScalef( ARROW_WIDTH_RATIO, ARROW_RATIO, ARROW_WIDTH_RATIO );
				for( int r = 0; r < 4; r++ )
				{
					glVertex3f( 1, 1, -1 );
					glVertex3f( 0, 0, 0 );
					glVertex3f( -1, 1, -1 );
					glRotatef( 45, 0, 1, 0 );
				}
				glTranslatef( 0, ARROW_RATIO, 0 );
				
				/* Top half */
				glRotatef( 180, 0, 0, 1 ); 
				glScalef( ARROW_WIDTH_RATIO, (1 - ARROW_RATIO), ARROW_WIDTH_RATIO );
				for( int r = 0; r < 4; r++ )
				{
					glVertex3f( 1, 1, -1 );
					glVertex3f( 0, 0, 0 );
					glVertex3f( -1, 1, -1 );
					glRotatef( 45, 0, 1, 0 );
				}
				glPopMatrix();
			glEnd();
		glEndList();
	}
}


UserInterface::~UserInterface()
{
	font.clean();
}


void UserInterface::draw()
{
			glLoadIdentity();
			
			Font::print( font, 100, 100, "Velocity: %.0f m/s", mass->getVelocity().magnitude() );
}


void UserInterface::keyPress( SDLKey key )
{
    switch( key )
    {
      case SDLK_w:
        mass->accelerate( 50 );
        break;
      case SDLK_s:
        mass->accelerate( -50 );
        break;
      case SDLK_a:
        mass->localAccelerate( -50, 0, 0 );
        break;
      case SDLK_d:
        mass->localAccelerate( 50, 0, 0 );
        break;

      case SDLK_UP:
        mass->rotate( -0.5, 1, 0, 0 );
        break;
      case SDLK_DOWN:
        mass->rotate( 0.5, 1, 0, 0 );
        break;
      case SDLK_RIGHT:
        mass->rotate( 0.5, 0, 1, 0 );
        break;
      case SDLK_LEFT:
        mass->rotate( -0.5, 0, 1, 0 );
        break;
      default:
        break;
    }
		
    return;
}

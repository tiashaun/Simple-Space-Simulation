#include "SDL.h"
#include "SDL_opengl.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "camera.h"
#include "planet.h"
#include "spaceship.h"
#include "universe.h"
#include "user_interface.h"

#define WIDTH  1024
#define HEIGHT 768


GLfloat yaw;
GLfloat pitch;
int     level;

float scale;
int detail;

SDL_Surface*  screen;

Camera				*camera;
UserInterface	*interface;
SpaceShip			*ship;


Universe    *universe;

void gravitate( Mass *arg1, Mass *arg2 )
{
    vector<COOR_TYPE> temp, temp2;
    vector<COOR_TYPE> dist;
    float             d = 0,f1,f2;

    temp = arg1->getLocation();
    temp2 = arg2->getLocation();
    dist.resize(3,0);

    for( int i = 0; i < 3;i++ )
    {
      dist[i] = temp2[i] - temp[i];

      d += dist[i] * dist[i];
    }

    /* f = Gmm/r^2 */
    f1 = G*arg2->getMass()/d;
    f2 = G*arg1->getMass()/d;
    
    for( int i = 0; i < 3; i++ )
    {
      temp[i] = ((dist[i] >= 0 )?1:-1)*abs(dist[i]/sqrt(d))*f1;
      temp2[i] = ((dist[i] >= 0 )?-1:1)*abs(dist[i]/sqrt(d))*f2;
    }

    arg1->accelerate( temp );
    arg2->accelerate( temp2 );
}

static void repaint()
{
    /* Clear the color plane and the z-buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		GLfloat l_specular[] = { 0, 0, 0, 1 };

		glMaterialfv( GL_FRONT, GL_SPECULAR, l_specular );
		glMateriali( GL_FRONT, GL_SHININESS, 1 );
    
		glLoadIdentity();
    camera->update();
    universe->draw();
		interface->draw();
    
    //gluLookAt( 0, 0, 0, 0, 0, 1, 0, 1, 0 );

    //glRotatef( angle, -1, -1, 1 );
    //glScalef( scale, scale, scale );
    
    /* finally, swap the back and front buffers */
    SDL_GL_SwapBuffers();
}

static void setup_sdl() 
{
    const SDL_VideoInfo* video;
    
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ) {
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    video = SDL_GetVideoInfo( );

    if( !video ) {
        fprintf(stderr,
                "Couldn't get video information: %s\n", SDL_GetError());
        exit(1);
    }

    /* Set the minimum requirements for the OpenGL window */
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* Note the SDL_DOUBLEBUF flag is not required to enable double 
     * buffering when setting an OpenGL video mode. 
     * Double buffering is enabled or disabled using the 
     * SDL_GL_DOUBLEBUFFER attribute.
     */
    screen = SDL_SetVideoMode( WIDTH, HEIGHT, video->vfmt->BitsPerPixel, SDL_OPENGL );
    if( screen == NULL ) {
        fprintf(stderr, 
                "Couldn't set video mode: %s\n", SDL_GetError());
        exit(1);
    }
    
    SDL_EnableKeyRepeat( 10, 10 );
}

static void setup_opengl()
{
    float aspect = (float)WIDTH / (float)HEIGHT;

    /* Make the viewport cover the whole window */
    glViewport(0, 0, WIDTH, HEIGHT);

    /* Set the camera projection matrix:
     * field of view: 90 degrees
     * near clipping plane at 0.1
     * far clipping plane at 100.0
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    /*I sit about a meter from my computer monitor, 'near' used to be 50km! */
    gluPerspective(60, aspect, 5, 2*50000.0 );
    
    /* We're done with the camera, now matrix operations 
     * will affect the modelview matrix
     * */
    glMatrixMode(GL_MODELVIEW);

    /* set the clear color to gray */
    glClearColor(0, 0 ,0, 0);
    
    /* We want z-buffer tests enabled*/
    glEnable(GL_DEPTH_TEST);
	
		glShadeModel( GL_SMOOTH );

    /* Enable vertex arrays */
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );

    /* Do not draw back-facing polygons*/
    glEnable(GL_CULL_FACE);
		
		/* Lighting */
		LightSource::init();
}


static void main_loop() 
{
    SDL_Event       event;
    int   time_speed = 1;
		int i;
		float lmodel[] = { 0, 0, 0, 1 };
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel );

    while( 1 )
    {
      /* process pending events */
      while( SDL_PollEvent( &event ) ) {
  
          switch( event.type ) {
                case SDL_KEYDOWN:
                  interface->keyPress( event.key.keysym.sym );
  
                  switch (event.key.keysym.sym) {
                  case SDLK_ESCAPE:
                      return;
              
                  case SDLK_EQUALS:
                      time_speed = time_speed++;
                      goto speed_print;
                  case SDLK_MINUS:
                      if( --time_speed <= 0 )
                        time_speed = 1;
                      
                      speed_print:
                          universe->setTimeSpeed( time_speed );
                          cout << "Speed: " << (float)time_speed/(1200) << " hours per second" << endl;
                      break;
                      
                  case SDLK_9:
                      for( i = 0; i < 3; i++ )
												lmodel[ i ] += 0.1;
					  
											glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel );
                      break;
											
                  case SDLK_8:
										for( i = 0; i < 3; i++ )
											lmodel[ i ] -= 0.1;
					  
										glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel );
										break;
  
                  /* Camera Manipulation */
                  case SDLK_SPACE:
                      
                      break;
                  case SDLK_c:
                      /* Change camera position */
                        break;
                        
                  /* Toggle fullscreen */
                  case SDLK_f:
                    #ifdef linux
                    SDL_WM_ToggleFullScreen( screen );
                    #endif
                    break;
                      
                default:
                      //no default key processing
                      //(stops compiler warnings for unhandled SDL keydefs
                      break;
                  }
              break;
              case SDL_MOUSEMOTION:
                  pitch += event.motion.yrel;
                  if (pitch < -70) pitch = -70;
                  if (pitch > 70) pitch = 70;
                  break;
  
              case SDL_QUIT:
                exit (0);
              }
          }
  
	  repaint();
	}
}


int main(int argc, char* argv[])
{
    /* Setup preferences */
    setup_sdl();
    setup_opengl();

    universe = new Universe();
    
    /* Set initial camera position */
    camera = new Camera();

    /* Default values */
    scale = 10;
    detail = 2;

    Mass *temp, *temp2;
    
		//const float EARTH_FROM_SUN = 1520977;
		//const float EARTH_VELOCITY = 0.29783;
		
    /* Create planets */
    /* Sun */
    temp = new Planet( 0, 1000 ); /* Divide by 100 to keep scaled */
    temp->setLocation( 50000, 0, 0 );
		temp->setVelocity( 0, 0, 0 );
    ((Planet*)temp)->setDetail( detail );
		universe->addMass( temp, new LightSource( 0.5, 0.5, 0.1 ) );
		
		/* Earth */
    temp2 = temp = new Planet( 5.9736e24, 637 ); /* Divide by 100 to keep scaled */
		temp->setColour( 0, 0, 0.5, 1  );
    temp->setLocation( 0, 0, 441.2 );
    temp->setVelocity( -0.12807, 0, 0 );
    ((Planet*)temp)->setDetail( detail );
    universe->addMass( temp );

    /* Other */
		ship = new SpaceShip( 2029203 );  /* Weight of a space shuttle */
		ship->setLocation( 0/*150 + 637 - 441.2*/, -1000, -1000 ); /* Low Earth orbit 160 - 2000 km */
		ship->setVelocity( 0, /*711*/0, 0 );
		//ship->setOrientation( 1, 1, 0, 0 );
		ship->orbitLargeObject( temp2, 2000, 0, Vector3( 0, 1, -1 ) );
		//universe->addMass( ship );
    
    /* Moon */
    temp2 = temp = new Planet( 7.3477e22, 173);
		temp->setColour( 0.009, 0.009, 0.04, 1 );
    temp->setLocation( 0, 0, 35869.2 ); /* Perigee */
    temp->setVelocity( -104.14, 0, 0 );
    ((Planet*)temp)->setDetail( detail );
    universe->addMass( temp );
		
    /* Our ship :) */
    temp = ship = new SpaceShip( 2029203 );  /* Weight of a space shuttle */
    temp->setLocation( 0, 0,  -5000 ); /* Low Earth orbit 160 - 2000 km */
    temp->setVelocity( 0.12807, 0, 0 );
    temp->setOrientation( 1, 0, 0, 0 );
		temp->orbitLargeObject( temp2, 1000, 0, Vector3( 0, -1, 0 ) );
    universe->addMass( temp );
		interface = (UserInterface *)ship->getInterface();
		
    /* Focus camera */
    camera->setFocus( temp );
    camera->follow( temp );
    //camera->setLocation( 0, 0, -4000 );

		main_loop();
	
    return EXIT_SUCCESS;
}

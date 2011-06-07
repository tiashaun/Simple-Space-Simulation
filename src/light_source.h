#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <OpenGL/gl.h>

#include "object3d.h"
#include "mass.h"

class LightSource {
	static bool lights_used[ GL_MAX_LIGHTS ];	
	
	bool enabled;
	int light_numb;
	
	Mass* mass;
	Vector3 position;
	
	GLfloat intensity[4];
	
	inline int translate( int arg ) { return arg + GL_LIGHT0; }	
	inline int translate_reverse( int arg ) { return arg - GL_LIGHT0; }
	
	public:
		LightSource( GLfloat arg1 = 0.9, GLfloat arg2 = 0.9, GLfloat arg3 = 0 );	/* Default to only set intensity */
		~LightSource();
		
		void attach( Mass *arg, int x = 0, int y = 0, int z = 0 );
		void detach();
		
		void place();
		
		void disable() { enabled = false; glDisable( light_numb ); }
		void enable() { enabled = true; glEnable( light_numb ); }
		bool isEnabled() { return enabled; }
		
		void	setAmbient( GLfloat, GLfloat, GLfloat, GLfloat );
		void setDiffuse( GLfloat, GLfloat, GLfloat, GLfloat );
		void setIntensity( GLfloat, GLfloat, GLfloat, GLfloat );
		
		static void init();
		static int sourcesLeft();
};
 
#endif

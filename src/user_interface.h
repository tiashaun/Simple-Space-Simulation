#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "SDL.h"
#include "interface.h"
#include "font.h"

class UserInterface : public Interface
{
		/* ARROW STUFF */
		enum { ARROW_ACCELERATION, ARROW_VELOCITY, ARROW_SIZE };
		GLuint arrow_base;
		
		struct Font::font_data font;
		
public:
    UserInterface( Mass *m );
    ~UserInterface();

		void draw();
    void keyPress( SDLKey );
};

#endif

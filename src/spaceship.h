#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "mass.h"
#include "user_interface.h"
/**
	@author Kapone <kapone@7rc.org>
*/
class SpaceShip : public Mass
{
		Interface *interface;
		
public:
    SpaceShip( float arg1 = 1000 );
    ~SpaceShip();

		Interface* getInterface();
};

#endif

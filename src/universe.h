#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SDL.h>

#include "light_source.h"
#include "linklist3d.h"
#include "mass.h"


/**
	@author Kapone <kapone@7rc.org>
*/

/* Gravitational constant, adapted for km's */
const double G = (6.67428e-11)*1e-6;

class Universe{
    double gravitational_const;
    double time_increment;
    double time_speed;
    double time_update_interval;
    
    SDL_TimerID timer;
    
		vector<LightSource *> lights;
    //LinkList3d  masses;
    vector<Mass *> masses;
    
    void gravitate( Mass *, Mass *  );
    void applyGravity();
    
    static Uint32 callUpdateTime( Uint32, void * );

public:
    Universe();
    ~Universe();

    void operator++();
    
    void draw();
    
		void	addLight( LightSource * );
    void  addMass( Mass * );
    void  addMass( Mass *, LightSource * );
    Mass* getMass( const int );
    void  setGravitationalConstant( double arg = G ) { gravitational_const = arg; };
    void  setTimeSpeed( double );
};

#endif

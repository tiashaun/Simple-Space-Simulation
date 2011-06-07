#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>

#include "mass.h"

/**
	@author Kapone <kapone@7rc.org>
*/
class Circle : public Mass
{
public:
    Circle( float radius = 30, int edges = 7 );

    ~Circle();

    void set( float radius = 30, int edges = 7 );
};

#endif

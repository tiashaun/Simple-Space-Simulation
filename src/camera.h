#ifndef CAMERA_H
#define CAMERA_H

#include "object3d.h"
#include "mass.h"

/**
	@author Kapone <kapone@7rc.org>
*/
class Camera : public Object3D
{
    Mass *focus_object;

    Mass *follow_object;
    vector<COOR_TYPE> follow_offset;

public:
    Camera();

    ~Camera();

    void focus();
    
    void follow( Mass *arg1 ) { follow_object = arg1; }
    void follow( Mass *, vector<COOR_TYPE> );

    void move( int, COOR_TYPE );

    void setFocus( Mass * );

    void update();
};

#endif

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include <iostream>

#include "vector3.h"

enum { X, Y, Z };

using namespace std;

class Object3D{
protected:
    vector<COOR_TYPE> location;
    vector<COOR_TYPE> pitch;

public:
    Object3D();

    ~Object3D();

    vector<COOR_TYPE> getLocation() { return location; }
    void setLocation( vector<COOR_TYPE> arg1 ) { location = arg1; }
    void setLocation( float x, float y, float z ) { location[X] = x; location[Y] = y; location[Z] = z; }

    vector<COOR_TYPE> getPitch() { return pitch; }
    void setPitch( vector<COOR_TYPE> arg1 ) { pitch = arg1; }
    void setPitch( float x, float y, float z ) { pitch[X] = x; pitch[Y] = y; pitch[Z] = z; }
    
    void print();
};

#endif

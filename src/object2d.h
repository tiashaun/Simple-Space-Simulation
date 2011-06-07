#include "vector3.h"

using namespace std;

class Object2D {
protected:
    vector<COOR_TYPE> location;
    vector<COOR_TYPE> pitch;

public:
    Object2D();
    ~Object2D();

    vector<COOR_TYPE> getLocation() { return location; }
    void setLocation( vector<COOR_TYPE> arg1 ) { location = arg1; }
    void setLocation( float x, float y, float z ) { location[0] = x;location[1] = y;location[2] = z; }

    vector<COOR_TYPE> getPitch() { return pitch; }
    void setPitch( vector<COOR_TYPE> arg1 ) { pitch = arg1; }
    void setPitch( float x, float y, float z ) { pitch[0] = x;pitch[1] = y;pitch[2] = z; }
    
    void print();
};

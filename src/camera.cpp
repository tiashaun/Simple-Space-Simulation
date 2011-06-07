#include "camera.h"

Camera::Camera()
{
  focus_object = NULL;
  follow_object = NULL;

  follow_offset.resize( 3, 0 );
}


Camera::~Camera()
{
}


void Camera::focus()
{
  vector<COOR_TYPE> temp = focus_object->getLocation();

  gluLookAt( location[X], location[Y], location[Z], temp[X], temp[Y], temp[Z], pitch[X], pitch[Y], pitch[Z] );
}


void Camera::follow( Mass *arg1, vector<COOR_TYPE> offset )
{
  follow_object = arg1;
  follow_offset = offset;
}

void Camera::move( int arg1, COOR_TYPE offset )
{
  location[arg1] += offset;
}


void Camera::setFocus( Mass *arg1 )
{
  focus_object = arg1;
}


void Camera::update()
{
  if( follow_object != NULL )
  {
    vector<COOR_TYPE> temp;

    temp = follow_object->getLocation();

    location[X] = temp[X] - follow_offset[X];
    location[Y] = temp[Y] - follow_offset[Y];
    location[Z] = temp[Z] - follow_offset[Z];
  }

  if( focus_object == follow_object )
  {
    Vector3 z = follow_object->getDirection();
    Vector3 y = follow_object->getTop();
 
    gluLookAt( location[X], location[Y], location[Z],
              location[X] + z.x, location[Y] + z.y, location[Z] + z.z,
              y.x, y.y, y.z );
  }
  else
    focus();
}

#include "object3d.h"

Object3D::Object3D()
{
  location.resize( 3, 0 );
  pitch.resize( 3, 0 );

  pitch[1] = 1;
}


Object3D::~Object3D()
{
}


void Object3D::print()
{
  std::cout << "Location: ";
  std::cout << location[0] << ", ";
  std::cout << location[1] << ", ";
  std::cout << location[2] << std::endl;
}





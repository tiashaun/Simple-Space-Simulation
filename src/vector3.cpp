#include "vector3.h"

Vector3 Vector3::crossProduct( Vector3 &arg1 )
{
	Vector3	ret;
	
	ret[0] = data[1] * arg1[2] - data[2] * arg1[1];
	ret[1] = data[2] * arg1[0] - data[0] * arg1[2];
	ret[2] = data[0] * arg1[1] - data[1] * arg1[0];
	
	return ret;
}


COOR_TYPE Vector3::dotProduct( Vector3 &arg1 )
{
	COOR_TYPE ret;
	
	ret = data[0] * arg1[0] + data[1] * arg1[1] + data[2] * arg1[2];
	
	return ret;
}

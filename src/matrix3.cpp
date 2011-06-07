#include "matrix3.h"

Matrix3::Matrix3()
{
}


Matrix3::~Matrix3()
{
}


void Matrix3::operator*=( const float &temp )
{
	data[0] *= temp;
  data[1] *= temp;
  data[2] *= temp;

  data[3] *= temp;
  data[4] *= temp;
  data[5] *= temp;

  data[6] *= temp;
  data[7] *= temp;
  data[8] *= temp;
}


Vector3 Matrix3::operator*( const Vector3 &temp )
{
  Vector3 ret;
  Vector3 arg = temp;
  
  ret[0] = data[0]*arg[0] + data[1]*arg[1] + data[2]*arg[2];
  ret[1] = data[3]*arg[0] + data[4]*arg[1] + data[5]*arg[2];
  ret[2] = data[6]*arg[0] + data[7]*arg[1] + data[8]*arg[2];
  
  return ret;
}


float Matrix3::getDeterminant()
{
	return data[0]*data[4]*data[8] + data[3]*data[7]*data[2] 
			+	data[6]*data[1]*data[5] - data[0]*data[7]*data[5]
			-	data[6]*data[4]*data[2] - data[3]*data[1]*data[8];
}


void Matrix3::invert()
{
	setInverse( *this );
}


void Matrix3::setData( const float arg1, const float arg2, const float arg3,
									const float arg4, const float arg5, const float arg6, 
									const float arg7, const float arg8, const float arg9 )
{
  data[0] = arg1;
  data[1] = arg2;
  data[2] = arg3;
  data[3] = arg4;
  data[4] = arg5;
  data[5] = arg6;
  data[6] = arg7;
  data[7] = arg8;
  data[8] = arg9;
}


void Matrix3::setIdentity()
{
  data[0] = 1; data[1] = 0; data[2] = 0;
  data[3] = 0; data[4] = 1; data[5] = 0;
  data[6] = 0; data[7] = 0; data[8] = 1;
}


void Matrix3::setInverse( const Matrix3 &m )
{
	float	det = getDeterminant();
	
	if( det == 0 )
		return;
	
	det = ((float)1.0) / det;
	
	data[0] = ( m.data[4]*m.data[8] - m.data[5]*m.data[7] ) * det;
	data[1] = ( m.data[2]*m.data[7] - m.data[1]*m.data[8] ) * det;
	data[2] = ( m.data[1]*m.data[5] - m.data[2]*m.data[4] ) * det;

	data[3] = ( m.data[5]*m.data[6] - m.data[3]*m.data[8] ) * det;
	data[4] = ( m.data[0]*m.data[8] - m.data[2]*m.data[6] ) * det;
	data[5] = ( m.data[2]*m.data[3] - m.data[0]*m.data[5] ) * det;

	data[6] = ( m.data[3]*m.data[7] - m.data[4]*m.data[6] ) * det;
	data[7] = ( m.data[1]*m.data[6] - m.data[0]*m.data[7] ) * det;
	data[8] = ( m.data[0]*m.data[4] - m.data[1]*m.data[3] ) * det;
}


void Matrix3::setOrientation( const Quaternion &q )
{
  data[0] = 1 - (2*q.j*q.j + 2*q.k*q.k);
  data[1] = 2*q.i*q.j + 2*q.k*q.r;
  data[2] = 2*q.i*q.k - 2*q.j*q.r;
  data[3] = 2*q.i*q.j - 2*q.k*q.r;
  data[4] = 1 - (2*q.i*q.i + 2*q.k*q.k);
  data[5] = 2*q.j*q.k + 2*q.i*q.r;
  data[6] = 2*q.i*q.k + 2*q.j*q.r;
  data[7] = 2*q.j*q.k - 2*q.i*q.r;
  data[8] = 1 - (2*q.i*q.i + 2*q.j*q.j);
}


void Matrix3::setTranspose( const Matrix3 &arg )
{
  data[0] = arg.data[0];
  data[1] = arg.data[3];
  data[2] = arg.data[6];
  data[3] = arg.data[1];
  data[4] = arg.data[4];
  data[5] = arg.data[7];
  data[6] = arg.data[2];
  data[7] = arg.data[5];
  data[8] = arg.data[8];
}


Matrix3 Matrix3::transpose() const
{
  Matrix3 result;

  result.setTranspose( *this );
  
  return result;
}

#include <iostream>
using namespace std;
void Matrix3::print()
{
  cout << ":Matrix:" << endl;
  for( int i = 0; i < 3; i++ )
  {
    for( int c = 0; c < 3; c++ )
      cout << data[i*3 + c] << " ";
    cout << endl;
  }
}

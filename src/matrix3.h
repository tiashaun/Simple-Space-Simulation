#ifndef MATRIX3_H
#define MATRIX3_H

#include "quaternion.h"
#include "vector3.h"

class Matrix3{
  float data[9];
  
public:
    Matrix3();
    ~Matrix3();

    Vector3 operator*( const Vector3 & );
		void operator*=( const float & );
    
		float		getDeterminant();
		
		void		invert();
		
		void		setData( const float, const float, const float, const float, const float, const float, const float, const float, const float );
		void		setInverse( const Matrix3 & );
    void    setIdentity();
    void    setOrientation( const Quaternion & );
    void    setTranspose( const Matrix3 & );
    
    Matrix3 transpose() const;
    
    void print();
};

#endif

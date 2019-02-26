#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <math.h>

class Vector3d {
public:
   Vector3d(float a=0.0f, float b=0.0f, float c=0.0f); // Constructor
   const Vector3d& operator = (const Vector3d& v);     // Assignment
   Vector3d operator + (const Vector3d& v) const;      // Addition
   Vector3d operator - (const Vector3d& v) const;      // Subtraction
   float operator * (const Vector3d& v) const;         // Dot product
   Vector3d operator ^ (const Vector3d& v) const;      // Cross product
   float length() const;                               // return length
   void normalize();                                   // Normalize to unit length
   Vector3d operator * (float c) const;                // Scaling


   friend std::ostream& operator << (std::ostream &out, const Vector3d &v);
   friend std::istream& operator >> (std::istream &in, Vector3d &v);

   float x;
   float y;
   float z;

private:

};

#endif // VECTOR3D_H

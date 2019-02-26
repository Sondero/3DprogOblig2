#include "vector3d.h"


Vector3d::Vector3d(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}

const Vector3d& Vector3d::operator=  (const Vector3d& v)
{

    x = v.x;
    y = v.y;
    z = v.z;

    return v;
}

Vector3d Vector3d::operator + (const Vector3d& v) const //addition
{
    return Vector3d(x+v.x, y+v.y, z+v.z);
}

Vector3d Vector3d::operator- (const Vector3d& v) const //subtraction
{
    return Vector3d(x-v.x, y-v.y, z-v.z);
}

float Vector3d::operator * (const Vector3d& v) const //dot product
{
    return x*v.x+y*v.y+z*v.z;
}

Vector3d Vector3d::operator ^ (const Vector3d& v) const
{
    return Vector3d(y*v.z-z*v.y, x*v.z-z*v.x, x*v.y+y*v.x);
}

float Vector3d::length() const
{
    return static_cast<float>(sqrt(static_cast<double>(x*x+y*y+z*z)));
}

void Vector3d::normalize()
{
    float vLength = this->length();

    if (vLength > 0.0001f || vLength < -0.0001f)
    {
        x = x/vLength;
        y = y/vLength;
        z = z/vLength;
    }
}

Vector3d Vector3d::operator * (float c) const
{
    return Vector3d(x*c, y*c, z*c);
}


std::ostream& operator << (std::ostream &out, const Vector3d &v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";

    return out;
}

std::istream& operator >> (std::istream &in, Vector3d &v)
{

    char commaCharacter;
    in >> v.x;
    in >> commaCharacter;
    in >> v.y;
    in >> commaCharacter;
    in >> v.z;

    return in;
}

#include "camera.h"

Camera::Camera()
{

}

void Camera::lookAt(const Vector3d &eye, const Vector3d &at, const Vector3d &up)
{
    QMatrix4x4 M;
    M.setToIdentity();

    Vector3d v = up;
    v.normalize();

    Vector3d n = eye-at;
    n.normalize();

    Vector3d u = v^n;
    u.normalize();

    v = n^u;
    v.normalize();
    M(0,0) = u.x;  M(0,1) = u.y;  M(0,2) = u.z;
    M(1,0) = v.x;  M(1,1) = v.y;  M(1,2) = v.z;
    M(2,0) = n.x;  M(2,1) = n.y;  M(2,2) = n.z;
    M.translate(-eye.x, -eye.y, -eye.z);

}

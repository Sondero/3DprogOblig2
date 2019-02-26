#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "vector3d.h"
#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>

class Camera
{

public:
    Camera();
    void lookAt(const Vector3d &eye, const Vector3d &at, const Vector3d &up);

};

#endif // CAMERA_H

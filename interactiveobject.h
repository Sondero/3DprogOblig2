#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"
#include "visualobject.h"

class InteractiveObject : public VisualObject
{
public:
    InteractiveObject();
    ~InteractiveObject() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float x, float y, float z);
private:
    float mx, my, mz; // posisjon

};

#endif // INTERACTIVEOBJECT_H

#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"
#include "visualobject.h"

class Cube : public VisualObject
{
private:
    //Vertex points[8];
public:
    Cube(std::vector<float> location = {0.f,0.f,0.f});
    ~Cube() override;
    void init(GLint matrixUniform) override;
    void draw() override;
};

#endif // CUBE_H

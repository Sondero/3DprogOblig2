#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"
#include "visualobject.h"

class TriangleSurface : public VisualObject
{
private:

public:
    TriangleSurface();
    TriangleSurface(std::vector<float> aLocation = {0.f, 0.f, 0.f}, std::vector<float> bLocation = {0.f, 0.f, 0.f},
                    std::vector<float> cLocation = {0.f, 0.f, 0.f});
    ~TriangleSurface() override;
    void init(GLint matrixUniform) override;
    void draw() override;
};

#endif // TRIANGLESURFACE_H

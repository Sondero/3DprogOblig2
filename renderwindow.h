#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QTimer>
#include <QElapsedTimer>

#include <vector>
//#include "vertex.h"

#include "shader.h"
#include "mainwindow.h"
#include "vertex.h"
#include "visualobject.h"
#include "xyz.h"
#include "trianglesurface.h"
#include "interactiveobject.h"

class QOpenGLContext;
class Shader;
class MainWindow;

/// This inherits from QWindow to get access to the Qt functionality and
/// OpenGL surface.
/// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
/// This is the same as using glad and glw from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow() override;

    QOpenGLContext *context() { return mContext; }

    void exposeEvent(QExposeEvent *) override;

    //XYZ xyz = XYZ();
    //TriangleSurface triangle = TriangleSurface({0.f, 1.f, 0.3f}, {0.f, -1.f, -0.3f}, {1.f, 0.f, -0.3f});

    InteractiveObject player = InteractiveObject();


//    void error(const QString &msg);

private slots:
    void render();

private:
    void init();
    std::vector<Vertex> mVertices;

    QOpenGLContext *mContext;
    bool mInitialized;

    Shader *mShaderProgram;
    GLint  mMatrixUniform;

    GLuint mVAO;
    GLuint mVBO;

    QMatrix4x4 *mMVPmatrix; //The matrix with the transform for the object we draw

    QTimer *mRenderTimer;     //timer that drives the gameloop
    QElapsedTimer mTimeStart;       //time variable that reads the actual FPS

    MainWindow *mMainWindow;    //points back to MainWindow to be able to put info in StatusBar

    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};

    void checkForGLerrors();

    void calculateFramerate();

    void startOpenGLDebugger();

protected:
    //The QWindow that we inherit from has these functions to capture
    // mouse and keyboard. Uncomment to use
    //
    //    void mousePressEvent(QMouseEvent *event) override{}
    //    void mouseMoveEvent(QMouseEvent *event) override{}
    void keyPressEvent(QKeyEvent *event) override;
    //    void keyReleaseEvent(QKeyEvent *event) override{}
    //    void wheelEvent(QWheelEvent *event) override{}
};

#endif // RENDERWINDOW_H

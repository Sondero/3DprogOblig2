#include "renderwindow.h"
#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>

/*
#include "shader.h"
#include "mainwindow.h"
#include "vertex.h"
#include "visualobject.h"
#include "xyz.h"
*/

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext(nullptr), mInitialized(false), mMainWindow(mainWindow)

{

    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    mContext = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    mContext->setFormat(requestedFormat());
    if (!mContext->create()) {
        delete mContext;
        mContext = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

    //This is the matrix used to transform the triangle
    //You could do without, but then you have to simplify the shader and shader setup
    mMVPmatrix = new QMatrix4x4{};
    mMVPmatrix->setToIdentity();

    //Make the gameloop timer:
    mRenderTimer = new QTimer(this);
}

RenderWindow::~RenderWindow()
{
    //cleans up the GPU memory
    glDeleteVertexArrays( 1, &mVAO );
    glDeleteBuffers( 1, &mVBO );
}

/*
//Simple global for vertices of a triangle - should belong to a class !
static GLfloat vertices[] =
{

    // Positions         // Colors (RGB)
    -0.5f, -0.5f, 0.0f,   0.75f, 0.75f, 0.75f, // Bottom Left
    0.5f,  -0.5f, 0.0f,   0.0f, 0.99f, 0.99f,  // Bottom Right
    0.0f,   0.5f, 0.0f,   0.99f, 0.99f, 0.0f,  // Top
    0.0f,   0.0f, 0.5f,   0.5f, 0.0f, 0.0f,    // Back
    -0.5f, -0.5f, 0.0f,   0.75f, 0.75f, 0.75f, // Bottom Left
    0.5f,  -0.5f, 0.0f,   0.0f, 0.99f, 0.99f   // Bottom Right
};
*/
/// Sets up the general OpenGL stuff and the buffers needed to render a triangle
void RenderWindow::init() {
   connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));
   if (!mContext->makeCurrent(this)) {
       qDebug() << "makeCurrent() failed";
       return;
   }
   if (!mInitialized)
       mInitialized = true;

   initializeOpenGLFunctions();
   startOpenGLDebugger();

   glEnable(GL_DEPTH_TEST);    //enables depth sorting - must use
   glClearColor(0.4f, 0.4f, 0.4f,1.0f);    //color used in glClear GL_COLOR_BUFFER_BIT

   mShaderProgram = new Shader("../GSOpenGL2019/plainvertex.vert",
"../GSOpenGL2019/plainfragment.frag");

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //enable the matrixUniform
   // NB: enable in shader and in render() function also to use matrix
   mMatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "matrix" );

   glBindVertexArray( 0 );
   //xyz.init(mMatrixUniform);
   //triangle.init(mMatrixUniform);
   player.init(mMatrixUniform);
}


///Called each frame - doing the rendering
void RenderWindow::render()
{
   mTimeStart.restart(); //restart FPS clock
   mContext->makeCurrent(this);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(mShaderProgram->getProgram() );

   //xyz.draw();
   //xyz.constantRotateY(2.f);

   //triangle.draw();
   player.draw();


   calculateFramerate();
   mContext->swapBuffers(this);

}


//This function is called from Qt when window is exposed (shown)
//and when it is resized
//exposeEvent is a overridden function from QWindow that we inherit from
void RenderWindow::exposeEvent(QExposeEvent *)
{
    if (!mInitialized)
        init();

    //This is just to support modern screens with "double" pixels
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    //If the window actually is exposed to the screen we start the main loop
    //isExposed() is a function in QWindow
    if (isExposed())
    {
        //This timer runs the actual MainLoop
        //16 means 16ms = 60 Frames pr second (should be 16.6666666 to be exact..)
        mRenderTimer->start(16);
        mTimeStart.start();
    }
}

//The way this is set up is that we start the clock before doing the draw call,
//and check the time right after it is finished (done in the render function)
//This will approximate what framerate we COULD have.
//The actual frame rate on your monitor is limited by the vsync and is probably 60Hz
void RenderWindow::calculateFramerate()
{
    long nsecElapsed = mTimeStart.nsecsElapsed();
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)    //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 30) //once pr 30 frames = update the message twice pr second (on a 60Hz monitor)
        {
            //showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                  QString::number(nsecElapsed/1000000.f, 'g', 4) + " ms  |  " +
                                                  "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 60 frames
        }
    }
}


/// Uses QOpenGLDebugLogger if this is present
/// Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            qDebug() << message;
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            qDebug() << "glGetError returns " << err;
        }
    }
}

/// Tries to start the extended OpenGL debugger that comes with Qt
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            qDebug() << "This system can not use QOpenGLDebugLogger, so we revert to glGetError()";

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            qDebug() << "System can log OpenGL errors!";
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                qDebug() << "Started OpenGL debug logger!";
        }
    }
}

void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) //Shuts down whole program
    {
        mMainWindow->close();
    }

    if (event->key() == Qt::Key_D)
    {
        player.move(0.1f, 0.f, 0.f);
    }
    if (event->key() == Qt::Key_W)
    {
        player.move(0.f, 0.f, 0.1f);
    }
    if (event->key() == Qt::Key_A)
    {
        player.move(-0.1f, 0.f, 0.f);
    }
    if (event->key() == Qt::Key_S)
    {
        player.move(0.f, 0.f, -0.1f);
    }


    //You get the keyboard input like this
//    if(event->key() == Qt::Key_A)
//    {
//        mMainWindow->statusBar()->showMessage(" AAAA");
//    }
//    if(event->key() == Qt::Key_S)
//    {
//        mMainWindow->statusBar()->showMessage(" SSSS");
//    }
}

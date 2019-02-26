QT          += core gui widgets

TEMPLATE    = app
CONFIG      += c++11

TARGET      = 3D-programmering

SOURCES += main.cpp \
    renderwindow.cpp \
    shader.cpp \
    mainwindow.cpp \
    vertex.cpp \
    xyz.cpp \
    visualobject.cpp \
    trianglesurface.cpp \
    cube.cpp \
    interactiveobject.cpp \
    camera.cpp \
    vector3d.cpp

HEADERS += \
    renderwindow.h \
    shader.h \
    mainwindow.h \
    vertex.h \
    xyz.h \
    visualobject.h \
    trianglesurface.h \
    cube.h \
    interactiveobject.h \
    camera.h \
    vector3d.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    plainfragment.frag \
    plainvertex.vert

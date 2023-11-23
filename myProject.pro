TEMPLATE = app
TARGET = myProject
DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += ./src
QT += opengl xml
CONFIG += qt \
    release
MOC_DIR = ./tmp/moc
OBJECTS_DIR = ./tmp/obj

# Input
HEADERS += ./src/point3.h \
    ./src/Mesh.h \
    ./src/MyViewer.h \
    ./src/gl/GLUtilityMethods.h \
    ./src/gl/BasicColors.h \
    src/glwidget.h \
    src/image_ppm.h \
    src/mainwindow.h \
    src/perlinNoise.h \
    src/terrainMesh.h \
    src/window.h
SOURCES += ./src/main.cpp \
    ./src/gl/GLUtilityMethods.cpp\
    ./src/gl/BasicColors.cpp \
    src/glwidget.cpp \
    src/mainwindow.cpp \
    src/perlinNoise.cpp \
    src/terrainMesh.cpp \
    src/window.cpp

RESOURCES += \
    src/shaders.qrc

EXT_DIR = /home/usr/libQGLViewer-main/build


#QGLViewer
{
 INCLUDEPATH += $${EXT_DIR}
 LIBS +=    -L$${EXT_DIR}/QGLViewer \
            -lQGLViewer
}



LIBS += -lglut \
    -lGLU
LIBS += -lgsl \
    -lgomp
LIBS += -lblas \
    -lgomp
release:QMAKE_CXXFLAGS_RELEASE += -O3 \
    -fopenmp
release:QMAKE_CFLAGS_RELEASE += -O3 \
    -fopenmp

DISTFILES += \
    src/fshader.glsl \
    src/vshader.glsl

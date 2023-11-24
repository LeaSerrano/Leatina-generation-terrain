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
    src/mySimpleViewer.h \
    src/perlinNoise.h \
    src/terrainMesh.h \
    src/window.h
SOURCES += ./src/main.cpp \
    ./src/gl/GLUtilityMethods.cpp\
    ./src/gl/BasicColors.cpp \
    src/glwidget.cpp \
    src/mainwindow.cpp \
    src/mySimpleViewer.cpp \
    src/perlinNoise.cpp \
    src/terrainMesh.cpp \
    src/window.cpp

RESOURCES += \
    src/shaders.qrc

#Ordi de la maison
#EXT_DIR = /home/usr/libQGLViewer-main/build

#QGLViewer
#{
# INCLUDEPATH += $${EXT_DIR}
# LIBS +=    -L$${EXT_DIR}/QGLViewer \
#            -lQGLViewer
#}

#Ordi de la fac
EXT_DIR = extern

#QGLViewer
{
 INCLUDEPATH += $${EXT_DIR}/libQGLViewer-2.6.1
 LIBS +=    -L$${EXT_DIR}/libQGLViewer-2.6.1/QGLViewer \
            -lQGLViewer-qt5
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

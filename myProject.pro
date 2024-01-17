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
    src/mainwindow.h \
    src/path.h \
    src/perlinNoise.h \
    src/terrainMesh.h \
    src/window.h
SOURCES += ./src/main.cpp \
    ./src/gl/GLUtilityMethods.cpp\
    ./src/gl/BasicColors.cpp \
    src/mainwindow.cpp \
    src/path.cpp \
    src/perlinNoise.cpp \
    src/terrainMesh.cpp \
    src/window.cpp

RESOURCES += \
    src/shaders.qrc

#INCLUDEPATH += /usr/include/opencv4 include
#LIBS += -L/usr/include/opencv4 -lopencv_core -lopencv_highgui -lopencv_imgproc



# EXT_DIR = /usr/lib/x86_64-linux-gnu/

# #QGLViewer
# {
#     INCLUDEPATH += /usr/include/QGLViewer
#     #LIBS += -L/usr/local/lib -lQGLViewer
#     #LIBS += -L$${EXT_DIR} -lQGLViewer-qt5
#     LIBS += -L/home/usr/libQGLViewer-main/build/QGLViewer -lQGLViewer
#     #LIBS += -L/usr/include/QGLViewer

# }



#Ordi de la fac
EXT_DIR = extern

#QGLViewer
{
INCLUDEPATH += $${EXT_DIR}/libQGLViewer-2.6.1
LIBS +=    -L$${EXT_DIR}/libQGLViewer-2.6.1/QGLViewer \
           -lQGLViewer-qt5
}

#{
#INCLUDEPATH += $${EXT_DIR}/opencv2
#LIBS +=    -L$${EXT_DIR}/opencv2 \
#            -lopencv_core -lopencv_highgui -lopencv_imgproc
#}


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

FORMS += \
    mainwindow.ui

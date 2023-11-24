#ifndef MYSIMPLEVIEWER_H
#define MYSIMPLEVIEWER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "terrainMesh.h"

class MySimpleViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    TerrainMesh terrainMesh;

public:
    MySimpleViewer(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    GLuint vertexbuffer;
    GLuint indexbuffer;

    QOpenGLShaderProgram shaderProgram;

    QVector3D lightDirection;
};

#endif // MYSIMPLEVIEWER_H

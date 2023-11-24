#include "mySimpleViewer.h"

MySimpleViewer::MySimpleViewer(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void MySimpleViewer::initializeGL()
{
    initializeOpenGLFunctions();

    // Génération du buffer de vertex
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, terrainMesh.vertex_buffer.size() * sizeof(QVector3D), &terrainMesh.vertex_buffer[0], GL_STATIC_DRAW);

    // Génération du buffer d'index
    glGenBuffers(1, &indexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrainMesh.index_buffer.size() * sizeof(short), &terrainMesh.index_buffer[0], GL_STATIC_DRAW);

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    shaderProgram.link();
    shaderProgram.bind();

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Direction de la lumière
    lightDirection = QVector3D(1.0f, 1.0f, 1.0f);

    // Matrice de projection
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);
    shaderProgram.setUniformValue("modelViewProjectionMatrix", projectionMatrix);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        qDebug() << "OpenGL error:" << error;
    }

}

void MySimpleViewer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // Mettez à jour la matrice de projection en cas de redimensionnement
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);
    shaderProgram.setUniformValue("modelViewProjectionMatrix", projectionMatrix);
}


void MySimpleViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activation des shaders
    shaderProgram.bind();

    // Envoi de la direction de la lumière au shader
    shaderProgram.setUniformValue("lightDirection", lightDirection);

    // Dessinez votre terrain ici en utilisant les buffers configurés
    glDrawElements(GL_TRIANGLES, terrainMesh.index_buffer.size(), GL_UNSIGNED_SHORT, 0);

    shaderProgram.release();
}

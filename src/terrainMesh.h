#ifndef TERRAINMESH_H
#define TERRAINMESH_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <QOpenGLBuffer>

class TerrainMesh
{
public:
    TerrainMesh();
    //const GLfloat *constData() const { return vertex_buffer.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 6; }

    QVector<QVector3D> vertex_buffer;
    QVector<short> index_buffer;

private:

    void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, GLfloat z);
    void add(const QVector3D &v, const QVector3D &n);
    void generatePlan(float sizeX, float sizeY, int resolution);
    void generateIndices(int resolution);
    void generatePlanMesh(float sizeX, float sizeY, int resolution);
    QVector3D calculateNormal(int index1, int index2, int index3);
    QVector3D calculateNormalVec3(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);

    int m_count;

};

#endif // TERRAINMESH_H

#ifndef TERRAINMESH_H
#define TERRAINMESH_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <QOpenGLBuffer>
#include "perlinNoise.h"

class TerrainMesh
{
public:
    TerrainMesh();
    ~TerrainMesh();

    QVector<QVector3D> vertex_buffer;
    QVector<float> normal_buffer;
    QVector<short> index_buffer;

    PerlinNoise* perlinNoise;

    float ymax = 1.0;
    float sizeX = 1.0, sizeY = 1.0;
    float averageHeight;
    int resolution = 50;
    int heightRange = 50;
    void regenerateMesh();

private:
    bool perlinNoiseCreated;
    void generatePlan();
    void generateIndices();
    void getHeightAtPerlinPx(GLfloat &y, float perlin);
    void calculateNormals();

};

#endif // TERRAINMESH_H

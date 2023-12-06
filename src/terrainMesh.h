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
    QImage getMap();

    float sizeX = 3.0, sizeY = 1.0, sizeZ = 3.0;
    float averageHeight;
    int resolution = 100;
    int heightRange = 300;
    void generateMesh();
    bool perlinNoiseCreated;
    void getHeightAtPerlinPx(GLfloat &y, float perlin);

private:
    void generatePlan();
    void generateIndices();
    void calculateNormals();
    void setMap(QImage image);


};

#endif // TERRAINMESH_H

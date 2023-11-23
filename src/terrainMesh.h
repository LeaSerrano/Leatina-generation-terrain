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

    QVector<QVector3D> vertex_buffer;
    QVector<short> index_buffer;

    PerlinNoise* perlinNoise;

    float ymax = 1.0, ymin = 0;
    float sizeX = 1.0, sizeY = 1.0;
    float averageHeight;
    int resolution = 16;

private:

    void generatePlan();
    void generateIndices();
    float calculateAverageHeight() const;

};

#endif // TERRAINMESH_H

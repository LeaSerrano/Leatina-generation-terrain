#ifndef TERRAINMESH_H
#define TERRAINMESH_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
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
    QVector<QVector2D> texture_coord_buffer; //Texture

    PerlinNoise* perlinNoise;
    QImage getMap();
    QImage ImgGradient;
    QImage ImgErosion;

    float sizeX = 1.0, sizeY = 1.0, sizeZ = 1.0;
    float averageHeight;
    float resolution = 100;
    float heightRange = 100;
    void generateMesh();
    bool perlinNoiseCreated;
    void getHeightAtPerlinPx(GLfloat &y, float perlin);
    void generateGradientMap(QImage perlinMap);
    void simulateHydraulicErosion(int dropNumber);
    std::vector<QPoint> followGradient(QPoint startPoint);
    float getErosionAt(int i, int j, int resolution);

    int nbRainDrops = 50;
    int nbErosionIterations = 20;
    int intensiteImpact = 40;
    //bool renderErosion = false;

private:
    void generatePlan();
    void generateIndices();
    void calculateNormals();
    void setMap(QImage image);

};

#endif // TERRAINMESH_H

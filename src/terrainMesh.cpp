
#include "terrainMesh.h"
#include <qmath.h>
#include <QDebug>

TerrainMesh::TerrainMesh() {
    perlinNoise = new PerlinNoise();
    generatePlan();
    generateIndices();
    averageHeight = calculateAverageHeight();
}


void TerrainMesh::generatePlan() {
    vertex_buffer.clear();

    float stepX = sizeX / static_cast<float>(resolution);
    float stepY = sizeY / static_cast<float>(resolution);

    perlinNoise->generatePerlinNoise();

    for (int i = 0; i <= resolution; ++i) {
        for (int j = 0; j <= resolution; ++j) {
            GLfloat x = i * stepX;
            GLfloat z = j * stepY;

            float perlin = perlinNoise->getPerlinAt(i, j, resolution);

            GLfloat y = 0.9 - (static_cast<int>(perlin) / 25) * 0.1;

            vertex_buffer.push_back(QVector3D(x, y, z));
        }
    }
}


void TerrainMesh::generateIndices(){
    index_buffer.clear();

    for(int i=0; i <= resolution-1; i++){
        for(int j=0; j <= resolution-1; j++){
            int p1 = i*(resolution+1)+j;
            int p2 = p1+1;
            int p3 = (i+1)*(resolution+1)+j;
            int p4 = p3+1;

            index_buffer.push_back(p1);
            index_buffer.push_back(p4);
            index_buffer.push_back(p2);
            index_buffer.push_back(p1);
            index_buffer.push_back(p3);
            index_buffer.push_back(p4);

        }
    }
}

float TerrainMesh::calculateAverageHeight() const {
    float totalHeight = 0.0f;

    for (const auto& vertex : vertex_buffer) {
        totalHeight += vertex.y();
    }

    return totalHeight / vertex_buffer.size();
}


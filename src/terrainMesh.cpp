
#include "terrainMesh.h"
#include <qmath.h>
#include <QDebug>

TerrainMesh::TerrainMesh() : m_count(0) {

    generatePlan(1.0, 1.0, 16);
    generateIndices(16);
}


void TerrainMesh::generatePlan(float sizeX, float sizeY, int resolution) {
    vertex_buffer.clear();

    float stepX = sizeX/(float)resolution;
    float stepY = sizeY/(float)resolution;

    for(int i=0; i <= resolution; i ++){
        for(int j=0; j <= resolution; j ++){

            GLfloat x = i*stepX;
            GLfloat y = j*stepY;

            vertex_buffer.push_back(QVector3D(x, 0.0f, y));

       }
    }
}

void TerrainMesh::generateIndices(int resolution){
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


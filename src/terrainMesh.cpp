
#include "terrainMesh.h"
#include <qmath.h>
#include <QDebug>
#include <QtGlobal>



void TerrainMesh::getHeightAtPerlinPx(GLfloat &y, float perlin) {
    float step = (float)255/heightRange;

    float stepMin = 0.0;
    float stepMax = step;

    float stepValue = sizeY/heightRange;
    float value = 0.0;

    for (int p = 0; p < heightRange; p++) {
        if (perlin >= stepMin && perlin < stepMax) {
            y = value;
            return;
        }

        if (p == heightRange-1) {
            if (perlin >= stepMin && perlin <= stepMax) {
                y = value;
                return;
            }
        }

        value += stepValue;
        stepMin = stepMax;
        stepMax += step;
    }
}


void TerrainMesh::generatePlan() {


    vertex_buffer.clear();

    if (!perlinNoiseCreated) {
        perlinNoise = new PerlinNoise();
        perlinNoiseCreated = true;
    }

    float stepX = static_cast<float>(sizeX) / static_cast<float>(resolution);
    float stepZ = static_cast<float>(sizeZ) / static_cast<float>(resolution);


    for (int i = 0; i <= resolution; ++i) {
        for (int j = 0; j <= resolution; ++j) {
            GLfloat x = i * stepX;
            GLfloat z = j * stepZ;

            float perlin = perlinNoise->getPerlinAt(i, j, resolution);

            GLfloat y;
            getHeightAtPerlinPx(y, perlin);
            //GLfloat y = 0.0f;

            vertex_buffer.push_back(QVector3D(x, y, z));
        }
    }
}


void TerrainMesh::generateIndices() {

    index_buffer.clear();

    for (int i = 0; i < resolution; ++i) {
        for (int j = 0; j < resolution; ++j) {
            int p1 = i * (resolution + 1) + j;
            int p2 = p1 + 1;
            int p3 = (i + 1) * (resolution + 1) + j;
            int p4 = p3 + 1;

            index_buffer.push_back(p1);
            index_buffer.push_back(p4);
            index_buffer.push_back(p2);
            index_buffer.push_back(p1);
            index_buffer.push_back(p3);
            index_buffer.push_back(p4);
        }
    }
}


void TerrainMesh::calculateNormals() {

       normal_buffer.clear();

       QVector<QVector3D> normals(vertex_buffer.size(), QVector3D(0.0, 0.0, 0.0));

       for (int i = 0; i < index_buffer.size(); i += 3) {
           int idx1 = index_buffer[i];
           int idx2 = index_buffer[i + 1];
           int idx3 = index_buffer[i + 2];

           // Vérifier et ajuster les indices
           idx1 = qMax(0, qMin(idx1, vertex_buffer.size() - 1));
           idx2 = qMax(0, qMin(idx2, vertex_buffer.size() - 1));
           idx3 = qMax(0, qMin(idx3, vertex_buffer.size() - 1));

           QVector3D v1 = vertex_buffer[idx1];
           QVector3D v2 = vertex_buffer[idx2];
           QVector3D v3 = vertex_buffer[idx3];

           QVector3D normal = QVector3D::crossProduct(v2 - v1, v3 - v1);

           normals[idx1] += normal;
           normals[idx2] += normal;
           normals[idx3] += normal;
       }

       for (int i = 0; i < normals.size(); ++i) {
           normals[i].normalize();
           normal_buffer.push_back(normals[i].x());
           normal_buffer.push_back(normals[i].y());
           normal_buffer.push_back(normals[i].z());
       }

    /*normal_buffer.clear();

       QVector<QVector3D> normals(vertex_buffer.size(), QVector3D(0.0, 0.0, 0.0));

       for (int i = 0; i < index_buffer.size(); i += 3) {
           int idx1 = index_buffer[i];
           int idx2 = index_buffer[i + 1];
           int idx3 = index_buffer[i + 2];

           QVector3D v1 = vertex_buffer[idx1];
           QVector3D v2 = vertex_buffer[idx2];
           QVector3D v3 = vertex_buffer[idx3];

           QVector3D normal = QVector3D::crossProduct(v2 - v1, v3 - v1);

           normals[idx1] += normal;
           normals[idx2] += normal;
           normals[idx3] += normal;
       }

       for (int i = 0; i < normals.size(); ++i) {
           normals[i].normalize();
       }

       for (int i = 0; i < normals.size(); ++i) {
           normal_buffer.push_back(normals[i].x());
           normal_buffer.push_back(normals[i].y());
           normal_buffer.push_back(normals[i].z());
       }*/

}


void TerrainMesh::generateMesh() {
    generatePlan();
    generateIndices();
    calculateNormals();
}

TerrainMesh::TerrainMesh() {
    perlinNoiseCreated = false;
    generateMesh();
}

TerrainMesh::~TerrainMesh() {
    if (perlinNoiseCreated) {
        delete perlinNoise;
    }
}

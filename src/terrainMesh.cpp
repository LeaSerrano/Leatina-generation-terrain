#include "terrainMesh.h"
#include <qmath.h>
#include <QDebug>
#include <QtGlobal>

//Générer terrainMesh : nouvelle carte + maillage
TerrainMesh::TerrainMesh() {
    perlinNoiseCreated = false;
    generateMesh();
}

TerrainMesh::~TerrainMesh() {
    if (perlinNoiseCreated) {
        delete perlinNoise;
    }
}

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
    texture_coord_buffer.clear(); //Texture

    if (!perlinNoiseCreated) {
        perlinNoise = new PerlinNoise();
        perlinNoiseCreated = true;
    }

    generateGradientMap(perlinNoise->ImgPerlin);
    simulateHydraulicErosion(nbRainDrops);

    float stepX = static_cast<float>(sizeX) / static_cast<float>(resolution);
    float stepZ = static_cast<float>(sizeZ) / static_cast<float>(resolution);

    float minHeight = std::numeric_limits<float>::max();
    float maxHeight = std::numeric_limits<float>::lowest();

    for (int i = 0; i <= resolution; ++i) {
        for (int j = 0; j <= resolution; ++j) {
            GLfloat x = i * stepX;
            GLfloat z = j * stepZ;

            float perlin = perlinNoise->getPerlinAt(i, j, resolution);

            GLfloat y;
            getHeightAtPerlinPx(y, perlin);

            int gradientValue = getErosionAt(i, j, resolution);

            if (gradientValue == 255) {
                if (y - 0.1 >= 0.0) {
                    y -= 0.1;
                }
            }

            vertex_buffer.push_back(QVector3D(x, y, z));

            GLfloat scaledX = x / sizeX;
            GLfloat scaledZ = z / sizeZ;
            texture_coord_buffer.push_back(QVector2D(scaledX, scaledZ));
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

}

//Générer un nouveau maillage
void TerrainMesh::generateMesh() {
    generatePlan();
    generateIndices();
    calculateNormals();

}



//Mettre une carte
void TerrainMesh::setMap(QImage image){
    perlinNoiseCreated = true;
    perlinNoise->ImgPerlin = image;
}

//Récupérer une carte
QImage TerrainMesh::getMap(){
    return perlinNoise->ImgPerlin;
}

/*
void TerrainMesh::generateGradientMap(QImage perlinMap)
{
    int largeur = perlinMap.width();
    int hauteur = perlinMap.height();

    ImgGradient = QImage(largeur, hauteur, QImage::Format_Grayscale8);

    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            double diffHauteurX = perlinMap.pixelColor(qBound(0, x + 1, largeur - 1), y).value() - perlinMap.pixelColor(x, y).value();
            double diffHauteurY = perlinMap.pixelColor(x, qBound(0, y + 1, hauteur - 1)).value() - perlinMap.pixelColor(x, y).value();

            double pente = atan2(diffHauteurY, diffHauteurX);

            int valeurPixel = static_cast<int>((pente + M_PI) / (2.0 * M_PI) * 255.0);

            ImgGradient.setPixel(x, y, qRgb(valeurPixel, valeurPixel, valeurPixel));
        }
    }

    ImgGradient.save("gradient.png");
}*/

void TerrainMesh::generateGradientMap(QImage perlinMap)
{
    int largeur = perlinMap.width();
    int hauteur = perlinMap.height();

    ImgGradient = QImage(largeur, hauteur, QImage::Format_Grayscale8);

    for (int x = 1; x < largeur - 1; ++x) {
           for (int y = 1; y < hauteur - 1; ++y) {
            // Calcul du gradient avec l'opérateur de Sobel
            double diffHauteurX = (perlinMap.pixelColor(x + 1, y - 1).value() + 2 * perlinMap.pixelColor(x + 1, y).value() + perlinMap.pixelColor(x + 1, y + 1).value())
                                  - (perlinMap.pixelColor(x - 1, y - 1).value() + 2 * perlinMap.pixelColor(x - 1, y).value() + perlinMap.pixelColor(x - 1, y + 1).value());

            double diffHauteurY = (perlinMap.pixelColor(x - 1, y + 1).value() + 2 * perlinMap.pixelColor(x, y + 1).value() + perlinMap.pixelColor(x + 1, y + 1).value())
                                  - (perlinMap.pixelColor(x - 1, y - 1).value() + 2 * perlinMap.pixelColor(x, y - 1).value() + perlinMap.pixelColor(x + 1, y - 1).value());

            double pente = atan2(diffHauteurY, diffHauteurX);

            int valeurPixel = static_cast<int>((pente + M_PI) / (2.0 * M_PI) * 255.0);

            ImgGradient.setPixel(x, y, qRgb(valeurPixel, valeurPixel, valeurPixel));
           }
    }

    ImgGradient.save("gradient.png");
}


std::vector<QPoint> TerrainMesh::followGradient(QPoint startPoint, int maxIterations)
{
    std::vector<QPoint> positionsList;

    int x = qBound(0, startPoint.x(), ImgGradient.width() - 1);
    int y = qBound(0, startPoint.y(), ImgGradient.height() - 1);

    for (int i = 0; i < 200; i++) {

        int pixelValue = ImgGradient.pixel(x, y);
        double angle = 2.0 * M_PI * pixelValue / 255.0;
        double gradientX = cos(angle);
        double gradientY = sin(angle);

        double gradientMagnitude = std::sqrt(gradientX * gradientX + gradientY * gradientY);
        double seuil_plateau = 0.3;

        if (gradientMagnitude >= seuil_plateau) {
            int newX = x + gradientX;
            int newY = y + gradientY;

            x = newX;
            y = newY;

            QPoint currentPoint = QPoint(newX, newY);
            positionsList.push_back(currentPoint);
        }
    }

    return positionsList;
}



void TerrainMesh::simulateHydraulicErosion(int dropNumber) {
    srand(time(NULL));

    int width = ImgGradient.width();
    int height = ImgGradient.height();

    ImgErosion = QImage(width, height, QImage::Format_RGB16);

    QVector<QPointF> dropPositions;
    for (int i = 0; i < dropNumber; ++i) {
        int x = std::rand()%width;
        int y = std::rand()%height;
        dropPositions.append(QPoint(x, y));
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            ImgErosion.setPixel(i, j, qRgb(0, 0, 0));
        }
    }

    for (const QPointF& dropPosition : dropPositions) {
        int x = dropPosition.x();
        int y = dropPosition.y();

        //while (x >= 0 && x < width && y >= 0 && y < height) {

            ImgErosion.setPixel(x, y, qRgb(255, 255, 255));
        //qDebug() << x << " " << y;

            double pente = static_cast<double>(ImgGradient.pixelColor(x, y).value()) / 255.0 * 2.0 * M_PI - M_PI;

            std::vector<QPoint> positionsList = followGradient(QPoint(x, y), 100);

            //qDebug() << positionsList.size();

            for (int i = 0; i < positionsList.size(); i++) {
                if (positionsList.size() > 10) {
                    ImgErosion.setPixel(positionsList[i].x(), positionsList[i].y(), qRgb(255, 255, 255));
                }//qDebug() << dropPosition.x() << " " << dropPosition.y() << " " << positionsList[i].x() << " " << positionsList[i].y();
            }

            /*qDebug() << "pente : " << pente;

            // Déplacer la goutte vers le voisin avec la plus grande pente descendante
            double meilleurAngle = 0.0;
            double meilleurePente = 0.0;

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx != 0 || dy != 0) {
                        int voisinX = x + dx;
                        int voisinY = y + dy;

                        if (voisinX >= 0 && voisinX < width && voisinY >= 0 && voisinY < height) {
                            double penteVoisin = static_cast<double>(ImgGradient.pixelColor(voisinX, voisinY).value()) / 255.0 * 2.0 * M_PI - M_PI;
                            if (penteVoisin < meilleurePente) {
                                meilleurePente = penteVoisin;
                                meilleurAngle = atan2(dy, dx);
                            }
                        }
                    }
                }
            }

            x += static_cast<int>(cos(meilleurAngle));
            y += static_cast<int>(sin(meilleurAngle));
        }*/
    }

    ImgErosion.save("hydraulicErosion.png");
}

float TerrainMesh::getErosionAt(int i, int j, int resolution) {
    if (!ImgErosion.isNull()) {
            int scaledI = static_cast<int>(i * ImgErosion.width() / resolution);
            int scaledJ = static_cast<int>(j * ImgErosion.height() / resolution);

            if (scaledI > 0 && scaledI < ImgErosion.width() && scaledJ > 0 && scaledJ < ImgErosion.height()) {
            QRgb pixelValue = ImgErosion.pixel(scaledI, scaledJ);
            return static_cast<float>(qGray(pixelValue));
            }
    }
    return 0.0f;
}


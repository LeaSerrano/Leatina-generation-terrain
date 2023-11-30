
#include "perlinNoise.h"
#include <QDebug>

PerlinNoise::PerlinNoise() {
    generatePerlinNoise();
};

unsigned int PerlinNoise::generateRandomSeed() {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<unsigned int> distribution(1, 10000);

    return distribution(rng);
}

double PerlinNoise::noise(int x, int y, int seed) {
    int n = x + y * 57 + seed;
    n = (n << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double PerlinNoise::cubicInterpolate(double beforeP0, double p0, double p1, double afterP1, double t) {
    double c3 = -0.5 * beforeP0 + 1.5 * p0 - 1.5 * p1 + 0.5 * afterP1;
    double c2 = beforeP0 - 2.5 * p0 + 2 * p1 - 0.5 * afterP1;
    double c1 = -0.5 * beforeP0 + 0.5 * p1;
    double c0 = p0;

    return (c3 * t * t * t) + (c2 * t * t) + (c1 * t) + c0;
}

double PerlinNoise::smoothNoiseFirstDim(int x, int y, double fractionalX, int seed) {
    double v0 = noise(x - 1, y, seed);
    double v1 = noise(x, y, seed);
    double v2 = noise(x + 1, y, seed);
    double v3 = noise(x + 2, y, seed);

    return cubicInterpolate(v0, v1, v2, v3, fractionalX);
}

double PerlinNoise::smoothNoise(double x, double y, int seed) {
    int integerX = static_cast<int>(x);
    double fractionalX = x - integerX;

    int integerY = static_cast<int>(y);
    double fractionalY = y - integerY;

    double t0 = smoothNoiseFirstDim(integerX, integerY - 1, fractionalX, seed);
    double t1 = smoothNoiseFirstDim(integerX, integerY, fractionalX, seed);
    double t2 = smoothNoiseFirstDim(integerX, integerY + 1, fractionalX, seed);
    double t3 = smoothNoiseFirstDim(integerX, integerY + 2, fractionalX, seed);

    return cubicInterpolate(t0, t1, t2, t3, fractionalY);
}

double PerlinNoise::perlinNoise(int octaves, double frequency, double persistence, double x, double y, int seed) {
    double r = 0.0;
    double f = frequency;
    double amplitude = 1.0;

    for (int i = 0; i < octaves; i++) {
        int t = i * 4096;
        r += smoothNoise(x * f + t, y * f + t, seed) * amplitude;

        amplitude *= persistence;
        f *= 2.0;
    }

    double result = (r + 1.0) / 2.0;

    return result;
}

void PerlinNoise::generatePerlinNoise() {

    ImgPerlin = QImage(nW, nH, QImage::Format_Grayscale8);

    int octaves = 4;
    double frequency = 0.9;
    double persistence = 0.6;

    seed = generateRandomSeed();

    for (int i = 0; i < nH; ++i) {
        for (int j = 0; j < nW; ++j) {

            double x = static_cast<double>(i) / nW;
            double y = static_cast<double>(j) / nH;

            double perlin = perlinNoise(octaves, frequency, persistence, x, y, seed) * 255;

            if (x < nW / 4) {
                perlin -= 25;
            } else if (x >= 3 * nW / 4) {
                perlin += 25;
            }

            if (perlin > 255) {
                perlin = 255;
            }
            else if (perlin < 0) {
                perlin = 0;
            }

            ImgPerlin.setPixel(j, i, QColor(perlin, perlin, perlin).rgb());

        }
    }

    ImgPerlin.save("perlinNoise.png");
}

float PerlinNoise::getPerlinAt(int i, int j, int resolution) {
    if (!ImgPerlin.isNull()) {
        int scaledI = static_cast<int>(i * ImgPerlin.width() / resolution);
        int scaledJ = static_cast<int>(j * ImgPerlin.height() / resolution);

        if (scaledI > 0 && scaledI < ImgPerlin.width() && scaledJ > 0 && scaledJ < ImgPerlin.height()) {
            QRgb pixelValue = ImgPerlin.pixel(scaledI, scaledJ);
            return static_cast<float>(qGray(pixelValue));
        }
    }
    return 0.0f;
}

int PerlinNoise::getSeed() {
    return seed;
}


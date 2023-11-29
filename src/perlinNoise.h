#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#pragma once

//#include "image_ppm.h"
#include <iostream>
#include <cmath>
#include <random>
#include <QImage>

class PerlinNoise {

public :
    PerlinNoise();

    QImage ImgPerlin;
    void generatePerlinNoise();
    float getPerlinAt(int i, int j, int resolution);
    int seed;

private :
    int nH = 512, nW = 512;


    unsigned int generateRandomSeed();
    double noise(int x, int y, int seed);
    double cubicInterpolate(double beforeP0, double p0, double p1, double afterP1, double t);
    double smoothNoiseFirstDim(int x, int y, double fractionalX, int seed);
    double smoothNoise(double x, double y, int seed);
    double perlinNoise(int octaves, double frequency, double persistence, double x, double y, int seed);
    int getSeed();

};

#endif // PERLINNOISE_H

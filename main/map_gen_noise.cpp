#include <iostream>
#include <cmath>
#include <random>

unsigned int generateRandomSeed() {
    std::random_device rd;
    std::mt19937 rng(rd());
    
    std::uniform_int_distribution<unsigned int> distribution(1, 10000);

    return distribution(rng);
}

double noise(int x, int y, int seed) {
    int n = x + y * 57 + seed;
    n = (n << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double cubicInterpolate(double beforeP0, double p0, double p1, double afterP1, double t) {
    double c3 = -0.5 * beforeP0 + 1.5 * p0 - 1.5 * p1 + 0.5 * afterP1;
    double c2 = beforeP0 - 2.5 * p0 + 2 * p1 - 0.5 * afterP1;
    double c1 = -0.5 * beforeP0 + 0.5 * p1;
    double c0 = p0;

    return (c3 * t * t * t) + (c2 * t * t) + (c1 * t) + c0;
}

double smoothNoiseFirstDim(int x, int y, double fractionalX, int seed) {
    double v0 = noise(x - 1, y, seed);
    double v1 = noise(x, y, seed);
    double v2 = noise(x + 1, y, seed);
    double v3 = noise(x + 2, y, seed);

    return cubicInterpolate(v0, v1, v2, v3, fractionalX);
}

double smoothNoise(double x, double y, int seed) {
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

double perlinNoise(int octaves, double frequency, double persistence, double x, double y, int seed) {
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

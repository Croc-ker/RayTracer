#pragma once
#include <random>
void seedRandom(unsigned int seed)
{
    srand(seed);
}

float random01()
{
    return rand() / (float)RAND_MAX;
}

float random(float min, float max)
{
    if (min > max)
    {
        std::swap(min, max);
    }
    return min + (max - min) * random01();
}

template <typename T>
inline T lerp(const T& a, const T& b, float t) {
    return a + t * (b - a);
}
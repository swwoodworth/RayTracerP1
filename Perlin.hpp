#ifndef PERLIN_H
#define PERLIN_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>       /* floor */

using namespace std;

double noise(double x, double y, double z);

inline float noisef(float x, float y, float z)
{
    return (float) noise((double)x, (double)y, (double)z);
}

#endif
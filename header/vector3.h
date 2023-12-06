#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "def.h"

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

extern const Vector3 ZERO_VECTOR;
extern const Vector3 ONE_VECTOR;
extern const Vector3 X_AXIS;
extern const Vector3 Y_AXIS;
extern const Vector3 Z_AXIS;

Vector3* CreateVect(float, float, float);
void DestroyVect(Vector3*);

Vector3 AddVects(Vector3, Vector3);
Vector3 MultiplyScalarVect(Vector3, float);
Vector3 RotateVect(Vector3, Vector3, float);
Vector3 InverseVect(Vector3);
Vector3 NormalizedVect(Vector3);
Vector3 LerpVect(Vector3, Vector3, float);
Vector3 CrossProduct(Vector3, Vector3);
Vector3 DirectionVect(Vector3, Vector3);
Vector3 BounceVect(Vector3, Vector3);
Vector3 ReflectVect(Vector3, Vector3);

float DotProductVects(Vector3, Vector3);
float MagnitudeSquaredVect(Vector3);
float MagnitudeVect(Vector3);
float AngleVects(Vector3, Vector3);
float DistanceSquaredVects(Vector3, Vector3);
float DistanceVects(Vector3, Vector3);

bool IsZeroVect(Vector3);
bool EqualVects(Vector3, Vector3);
bool IsNormalizedVect(Vector3);

#endif
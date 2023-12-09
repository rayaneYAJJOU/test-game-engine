#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "def.h"

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

extern const Vector3 ZERO_VECTOR3;
extern const Vector3 ONE_VECTOR3;
extern const Vector3 X_AXIS3;
extern const Vector3 Y_AXIS3;
extern const Vector3 Z_AXIS3;

Vector3* CreateVect3(float, float, float);
void DestroyVect3(Vector3*);

float *Vect3ToArray(Vector3);
float *Vect4ToArray(Vector3, float);

Vector3 AddVect3(Vector3, Vector3);
Vector3 MultiplyVect3Scalar(Vector3, float);
Vector3 RotateVect3(Vector3, Vector3, float);
Vector3 InverseVect3(Vector3);
Vector3 NormalizedVect3(Vector3);
Vector3 LerpVect3(Vector3, Vector3, float);
Vector3 CrossProductVect3(Vector3, Vector3);
Vector3 DirectionVect3(Vector3, Vector3);
Vector3 BounceVect3(Vector3, Vector3);
Vector3 ReflectVect3(Vector3, Vector3);

float DotProductVect3(Vector3, Vector3);
float MagnitudeSquaredVect3(Vector3);
float MagnitudeVect3(Vector3);
float AngleVect3(Vector3, Vector3);
float DistanceSquaredVect3(Vector3, Vector3);
float DistanceVect3(Vector3, Vector3);

bool IsZeroVect3(Vector3);
bool EqualVect3(Vector3, Vector3);
bool IsNormalizedVect3(Vector3);

void PrintVect3(Vector3);

#endif
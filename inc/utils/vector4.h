#ifndef VECTOR_4_H
#define VECTOR_4_H

#include "vector3.h"

typedef struct Vector4
{
    float x;
    float y;
    float z;
    float w;
} Vector4;

extern const Vector4 ZERO_VECTOR4;
extern const Vector4 ONE_VECTOR4;
extern const Vector4 X_AXIS4;
extern const Vector4 Y_AXIS4;
extern const Vector4 Z_AXIS4;
extern const Vector4 W_AXIS4;

Vector4* CreateVect4(float, float, float, float);
void DestroyVect4(Vector4*);

float *Vect4ToArray(Vector4);

Vector4 AddVect4(Vector4, Vector4);
Vector4 MultiplyVect4Scalar(Vector4, float);
Vector4 InverseVect4(Vector4);
Vector4 NormalizedVect4(Vector4);
Vector4 LerpVect4(Vector4, Vector4, float);
Vector4 DirectionVect4(Vector4, Vector4);
Vector4 BounceVect4(Vector4, Vector4);
Vector4 ReflectVect4(Vector4, Vector4);
Vector4 ProjectVect4(Vector4, Vector4);
Vector4 ArrayToVect4(float[4]);
Vector4 FromVect3(Vector3);

float DotProductVect4(Vector4, Vector4);
float MagnitudeSquaredVect4(Vector4);
float MagnitudeVect4(Vector4);
float AngleVect4(Vector4, Vector4);
float DistanceSquaredVect4(Vector4, Vector4);
float DistanceVect4(Vector4, Vector4);

bool IsZeroVect4(Vector4);
bool EqualVect4(Vector4, Vector4);
bool IsNormalizedVect4(Vector4);

void PrintVect4(Vector4);


#endif
#ifndef VECTOR2_H_
#define VECTOR2_H_

#include "vector3.h"

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

extern const Vector2 ZERO_VECTOR2;
extern const Vector2 ONE_VECTOR2;
extern const Vector2 X_AXIS2;
extern const Vector2 Y_AXIS2;

Vector2* CreateVect2(float, float);
void DestroyVect2(Vector2*);

float *Vect2ToArray(Vector2);

Vector3 ToVect3(Vector2);
Vector3 CrossProductVect2(Vector2, Vector2);

Vector2 AddVect2(Vector2, Vector2);
Vector2 MultiplyVect2Scalar(Vector2, float);
Vector2 RotateVect2(Vector2, float);
Vector2 InverseVect2(Vector2);
Vector2 NormalizedVect2(Vector2);
Vector2 LerpVect2(Vector2, Vector2, float);
Vector2 DirectionVect2(Vector2, Vector2);
Vector2 BounceVect2(Vector2, Vector2);
Vector2 ReflectVect2(Vector2, Vector2);

float DotProductVect2(Vector2, Vector2);
float MagnitudeSquaredVect2(Vector2);
float MagnitudeVect2(Vector2);
float AngleVect2(Vector2, Vector2);
float DistanceSquaredVect2(Vector2, Vector2);
float DistanceVect2(Vector2, Vector2);

bool IsZeroVect2(Vector2);
bool EqualVect2(Vector2, Vector2);
bool IsNormalizedVect2(Vector2);

void PrintVect2(Vector2);

#endif
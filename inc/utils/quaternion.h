#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "def.h"
#include "vector4.h"
#include "matrix4.h"

typedef struct Quaternion {
    float x;
    float y;
    float z;
    float w;
} Quaternion;

typedef struct Matrix4 Matrix4;

extern const Quaternion IDENTITY_QUAT;
extern const Quaternion ZERO_QUAT;

Quaternion *CreateQuat(float,float,float,float);
void DestroyQuat(Quaternion*);

Quaternion AddQuat(Quaternion, Quaternion);
Quaternion MultiplyQuatScalar(Quaternion, float);
Quaternion MultiplyQuat(Quaternion, Quaternion);
Quaternion AdditiveInverseQuat(Quaternion);
Quaternion ConjugateQuat(Quaternion);
Quaternion InverseQuat(Quaternion);
Quaternion RotationQuat(Vector3, float);
Quaternion FromEulerAnglesQuat(Vector3, EulerOrder);
Quaternion NormalizedQuat(Quaternion);
Quaternion LerpQuat(Quaternion, float);
Quaternion FromVect3Quat(Vector3);
Quaternion FromScalarQuat(float);
Quaternion ExpQuat(Quaternion);
Quaternion LogQuat(Quaternion);
Quaternion MultiplyQuatVect3(Quaternion, Vector3);
Quaternion MultiplyVect3Quat(Vector3, Quaternion);
Quaternion RotateQuat(Quaternion, Vector3, float);
Quaternion GetQuatMat3(Matrix3);

Matrix4 GetMat4Quat(Quaternion);

Matrix3 GetMat3Quat(Quaternion);

Vector3 GetEulerAnglesQuat(Quaternion, EulerOrder);
Vector3 GetVect3PartQuat(Quaternion);
Vector3 RotateVect3Quat(Vector3, Vector3, float);
Vector3 GetAxisQuat(Quaternion);

float DotProductQuat(Quaternion, Quaternion);
float AngleQuat(Quaternion, Quaternion);
float MagnitudeSquaredQuat(Quaternion);
float MagnitudeQuat(Quaternion);
float DistanceSquaredQuat(Quaternion, Quaternion);
float DistanceQuat(Quaternion, Quaternion);
float GetScalarPartQuat(Quaternion);
float GetAngleQuat(Quaternion);

bool IsZeroQuat(Quaternion);
bool EqualQuat(Quaternion, Quaternion);
bool IsNormalizedQuat(Quaternion);

void PrintQuat(Quaternion);

#endif
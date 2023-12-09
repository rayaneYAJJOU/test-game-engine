#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "def.h"
#include "vector3.h"
#include "matrix4.h"

typedef struct Quaternion {
    float x;
    float y;
    float z;
    float w;
} Quaternion;

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
Quaternion FromEulerAnglesQuat(Vector3, EulerOrder);
Quaternion NormalizedQuat(Quaternion);
Quaternion LerpQuat(Quaternion, float);

Matrix4 GetMatrix4Quat(Quaternion);

Vector3 GetEulerAnglesQuat(Quaternion, EulerOrder);

float AngleQuat(Quaternion, Quaternion);
float MagnitudeSquaredQuat(Quaternion);
float MagnitudeQuat(Quaternion);
float DistanceSquaredQuat(Quaternion, Quaternion);
float DistanceQuat(Quaternion, Quaternion);

bool IsZeroQuat(Quaternion);
bool EqualQuat(Quaternion, Quaternion);
bool IsNormalizedQuat(Quaternion);

#endif
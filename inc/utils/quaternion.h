#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "def.h"
#include "vector3.h"

typedef struct Quaternion {
    float x;
    float y;
    float z;
    float w;
} Quaternion;

extern const Quaternion IDENTITY_QUAT;
extern const Quaternion ZERO_QUAT;

Quaternion* CreateQuat(float,float,float,float);
void DestroyQuat(Quaternion*);

Quaternion AddQuats(Quaternion, Quaternion);
Quaternion MultiplyScalarQuat(Quaternion, float);
Quaternion MultiplyQuats(Quaternion, Quaternion);
Quaternion InverseQuat(Quaternion);
Quaternion FromEulerAnglesQuat(Vector3, EulerOrder);

Vector3 GetEulerAnglesQuat(Quaternion, EulerOrder);

float AngleQuats(Quaternion, Quaternion);
float DotProductQuats(Quaternion, Quaternion);
float MagnitudeSquaredQuat(Quaternion);
float MagnitudeQuat(Quaternion);

bool EqualQuats(Quaternion, Quaternion);
bool NormalizedQuat(Quaternion);

#endif
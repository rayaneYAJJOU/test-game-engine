#include "../../inc/utils/quaternion.h"


const Quaternion IDENTITY_QUAT = (Quaternion) {0.0f, 0.0f, 0.0f, 1.0f};
const Quaternion ZERO_QUAT = (Quaternion) {0.0f, 0.0f, 0.0f, 0.0f};

Quaternion *CreateQuat(float x, float y, float z, float w) {

    Quaternion *quat = (Quaternion*)malloc(sizeof(Quaternion));

    if (quat==NULL) {
        fprintf(stderr,"Error allocating memory for struct Quaternion.\n");
        return NULL;
    }

    quat->x = x;
    quat->y = y;
    quat->z = z;
    quat->w = w;

    return quat;
}

void DestroyQuat(Quaternion *quat) {

    if (quat != NULL) {
        free(quat);
    }
}


Quaternion AddQuat(Quaternion quat1, Quaternion quat2) {

    return (Quaternion) {quat1.x + quat2.x, quat1.y + quat2.y, quat1.z + quat2.z, quat1.w + quat2.w};
}

Quaternion MultiplyQuatScalar(Quaternion quat, float k) {

    return (Quaternion) {quat.x * k, quat.y * k, quat.z * k, quat.w * k};
}

Quaternion MultiplyQuat(Quaternion quat1, Quaternion quat2) {

    float x1 = quat1.x;
    float y1 = quat1.y;
    float z1 = quat1.z;
    float w1 = quat1.w;
    float x2 = quat2.x;
    float y2 = quat2.y;
    float z2 = quat2.z;
    float w2 = quat2.w;

    return (Quaternion) {
        w1*w2 - x1*x2 - y1*y2 - z1*z2,
        w1*x2 + x1*w2 + y1*z2 - z1*y1,
        w1*y2 - x1*z2 + y1*w2 + z1*x2,
        w1*z2 + x1*y2 - y1*x2 + z1*w2
    };
}

Quaternion AdditiveInverseQuat(Quaternion quat) {

    return AddQuat(ZERO_QUAT, MultiplyQuatScalar(quat, -1.0f));
}

Quaternion ConjugateQuat(Quaternion quat) {

    return (Quaternion) {-quat.x, -quat.y, -quat.z, quat.w};
}

Quaternion InverseQuat(Quaternion quat) {

    if (IsZeroQuat(quat)) {
        return ZERO_QUAT;
    }
    return MultiplyQuatScalar(ConjugateQuat(quat), 1/MagnitudeSquaredQuat(quat));
}

Quaternion NormalizedQuat(Quaternion quat) {

    if (IsZeroQuat(quat)) {
        return ZERO_QUAT;
    }
    return MultiplyQuatScalar(quat, 1/MagnitudeQuat(quat));
}

Quaternion FromEulerAnglesQuat(Vector3 eulerAngles, EulerOrder order) {

    return ZERO_QUAT;
}


Matrix4 GetMatrix4Quat(Quaternion quat) {

    float x = quat.x;
    float y = quat.y;
    float z = quat.z;
    float w = quat.w;
    return (Matrix4) {{
        {w, -x, -y, -z},
        {x, w, -z, y},
        {y, z, w, -x},
        {z, -y, x, w}
    }};
}


Vector3 GetEulerAnglesQuat(Quaternion quat, EulerOrder order) {

    return ZERO_VECTOR3;
}



float AngleQuat(Quaternion quat1, Quaternion quat2) {

    return 0.0f;
}

float MagnitudeSquaredQuat(Quaternion quat) {

    return quat.x*quat.x + quat.y*quat.y + quat.z*quat.z + quat.w*quat.w;
}

float MagnitudeQuat(Quaternion quat) {

    return sqrt(MagnitudeSquaredQuat(quat));
}

float DistanceSquaredQuat(Quaternion quat1, Quaternion quat2) {

    return MagnitudeSquaredQuat(AddQuat(quat1, AdditiveInverseQuat(quat2)));
}

float DistanceQuat(Quaternion quat1, Quaternion quat2) {

    return sqrt(DistanceSquaredQuat(quat1, quat2));
}



bool IsZeroQuat(Quaternion quat) {

    return fabs(quat.x) < 10e-6 && fabs(quat.y) < 10e-6 && fabs(quat.z) < 10e-6 && fabs(quat.w) < 10e-6;
}

bool EqualQuat(Quaternion quat1, Quaternion quat2) {

    return IsZeroQuat(AddQuat(quat1, AdditiveInverseQuat(quat2)));
}

bool IsNormalizedQuat(Quaternion quat) {

    return EqualQuat(quat, NormalizedQuat(quat));
}
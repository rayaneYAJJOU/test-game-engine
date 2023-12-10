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

Quaternion GetRotationQuat(Vector3 axis, float angle) {

    return AddQuat(FromScalarQuat(cos(angle/2)),FromVect3Quat(MultiplyVect3Scalar(axis, sin(angle/2))));
}

Quaternion FromEulerAnglesQuat(Vector3 eulerAngles, EulerOrder order) {

    float x = eulerAngles.x;
    float y = eulerAngles.y;
    float z = eulerAngles.z;

    Quaternion quatx = GetRotationQuat(X_AXIS3, x);
    Quaternion quaty = GetRotationQuat(Y_AXIS3, y);
    Quaternion quatz = GetRotationQuat(Z_AXIS3, z);
    Quaternion quat = ZERO_QUAT;

    switch (order)
    {
    case EULER_ORDER_XYZ:
        quat = MultiplyQuat(quatz, MultiplyQuat(quaty, quatx));
        break;
    case EULER_ORDER_XZY:
        quat = MultiplyQuat(quaty, MultiplyQuat(quaty, quatx));
        break;
    case EULER_ORDER_YXZ:
        quat = MultiplyQuat(quatz, MultiplyQuat(quatx, quaty));
        break;
    case EULER_ORDER_YZX:
        quat = MultiplyQuat(quatx, MultiplyQuat(quatz, quaty));
        break;
    case EULER_ORDER_ZXY:
        quat = MultiplyQuat(quaty, MultiplyQuat(quatx, quatz));
        break;
    case EULER_ORDER_ZYX:
        quat = MultiplyQuat(quatx, MultiplyQuat(quaty, quatz));
        break;
    }

    return quat;
}

Quaternion FromVect3Quat(Vector3 vect) {

    return (Quaternion) {vect.x, vect.y, vect.z, 0.0f};
}

Quaternion FromScalarQuat(float k) {

    return MultiplyQuatScalar(IDENTITY_QUAT, k);
}

Quaternion ExpQuat(Quaternion quat) {

    float magv = MagnitudeVect3(GetVect3PartQuat(quat));
    if (IsZeroF(magv)) {
        return ZERO_QUAT;
    }

    return MultiplyQuatScalar(AddQuat(FromScalarQuat(cos(magv)),FromVect3Quat(MultiplyVect3Scalar(NormalizedVect3(GetVect3PartQuat(quat)), sin(magv)))), exp(quat.w));
}

Quaternion LogQuat(Quaternion quat) {

    float mag = MagnitudeQuat(quat);

    if (IsZeroF(mag) || MagnitudeVect3(GetVect3PartQuat(quat))) {
        return ZERO_QUAT;
    }

    return AddQuat(FromScalarQuat(log(mag)), FromVect3Quat(MultiplyVect3Scalar(NormalizedVect3(GetVect3PartQuat(quat)), acos(quat.w/mag))));
}

Quaternion MultiplyQuatVector3(Quaternion quat, Vector3 vect) {

    return MultiplyQuat(quat, FromVect3Quat(vect));
}

Quaternion MultiplyVect3Quat(Vector3 vect, Quaternion quat) {

    return MultiplyQuat(FromVect3Quat(vect), quat);
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

    if (!IsNormalizedQuat(quat)) {
        return ZERO_VECTOR3;
    }

    float a1, a2, a3;
    float x = quat.x;
    float y = quat.y;
    float z = quat.z;
    float w = quat.w;

    switch (order) {
    case EULER_ORDER_XYZ:
        a1 = atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
        a2 = asin(fmaxf(fminf(2 * (w * y - z * x), 1.0f), -1.0f));
        a3 = atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));
        break;
    case EULER_ORDER_XZY:
        a1 = atan2(2 * (w * x - z * y), 1 - 2 * (x * x + z * z));
        a2 = asin(fmaxf(fminf(2 * (w * y + x * z), 1.0f), -1.0f));
        a3 = atan2(2 * (w * z + y * x), 1 - 2 * (x * x + y * y));
        break;
    case EULER_ORDER_YXZ:
        a1 = atan2(2 * (w * y + z * x), 1 - 2 * (y * y + z * z));
        a2 = asin(fmaxf(fminf(2 * (w * x - y * z), 1.0f), -1.0f));
        a3 = atan2(2 * (w * z + y * x), 1 - 2 * (x * x + y * y));
        break;
    case EULER_ORDER_YZX:
        a1 = atan2(2 * (w * y - x * z), 1 - 2 * (y * y + z * z));
        a2 = asin(fmaxf(fminf(2 * (w * x + y * z), 1.0f), -1.0f));
        a3 = atan2(2 * (w * z + x * y), 1 - 2 * (x * x + y * y));
        break;
    case EULER_ORDER_ZXY:
        a1 = atan2(2 * (w * z + x * y), 1 - 2 * (x * x + z * z));
        a2 = asin(fmaxf(fminf(2 * (w * x - y * z), 1.0f), -1.0f));
        a3 = atan2(2 * (w * y + z * x), 1 - 2 * (y * y + z * z));
        break;
    case EULER_ORDER_ZYX:
        a1 = atan2(2 * (w * z - y * x), 1 - 2 * (x * x + y * y));
        a2 = asin(fmaxf(fminf(2 * (w * x + z * y), 1.0f), -1.0f));
        a3 = atan2(2 * (w * y + x * z), 1 - 2 * (x * x + z * z));
        break;
    default:
        a1 = atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
        a2 = asin(fmaxf(fminf(2 * (w * y - z * x), 1.0f), -1.0f));
        a3 = atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));
        break;
    }

    return (Vector3) {a1, a2, a3};
}



Vector3 GetVect3PartQuat(Quaternion quat) {

    return (Vector3) {quat.x, quat.y, quat.z};
}

Vector3 RotateVect3Quat(Vector3 vect, Vector3 axis, float angle) {

    Vector3 axisNormalized = NormalizedVect3(axis);

    if (IsZeroVect3(axisNormalized)) {
        return ZERO_VECTOR3;
    }

    Quaternion p = FromVect3Quat(vect);
    Quaternion q = AddQuat(MultiplyQuatScalar(IDENTITY_QUAT, cos(angle/2)), MultiplyQuatScalar(FromVect3Quat(axisNormalized), sin(angle/2)));

    return GetVect3PartQuat(MultiplyQuat(q, MultiplyQuat(p, InverseQuat(q))));
}

Vector3 GetAxisQuat(Quaternion quat) {

    if (IsZeroF(GetAngleQuat(quat))) {
        return ZERO_VECTOR3;
    }

    return MultiplyVect3Scalar(GetVect3PartQuat(quat), 1/sin(GetAngleQuat(quat)/2));
}



float DotProductQuat(Quaternion quat1, Quaternion quat2) {

    return quat1.x*quat2.x, quat1.y*quat2.y, quat1.z*quat2.z, quat1.w*quat2.w;
}

float AngleQuat(Quaternion quat1, Quaternion quat2) {

    return (float)acos((double) DotProductQuat(quat1, quat2)/(MagnitudeQuat(quat1)*MagnitudeQuat(quat2)));
}

float MagnitudeSquaredQuat(Quaternion quat) {

    return DotProductQuat(quat, quat);
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

float GetScalarPartQuat(Quaternion quat) {

    return quat.w;
}

float GetAngleQuat(Quaternion quat) {

    return 2*acos(quat.w);
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


void PrintQuat(Quaternion quat) {

    printf("struct Quaternion: %f + %f*i + %f*j + %f*k\n", quat.w, quat.x, quat.y, quat.z);
}
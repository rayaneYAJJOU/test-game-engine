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

    if (EqualQuat(quat1, IDENTITY_QUAT) || EqualQuat(quat2, IDENTITY_QUAT)) {
        return (EqualQuat(quat1, IDENTITY_QUAT)) ? quat2 : quat1;
    }

    float x1 = quat1.x;
    float y1 = quat1.y;
    float z1 = quat1.z;
    float w1 = quat1.w;
    float x2 = quat2.x;
    float y2 = quat2.y;
    float z2 = quat2.z;
    float w2 = quat2.w;

    return (Quaternion) {
        w1*x2 + x1*w2 + y1*z2 - z1*y1,
        w1*y2 - x1*z2 + y1*w2 + z1*x2,
        w1*z2 + x1*y2 - y1*x2 + z1*w2,
        w1*w2 - x1*x2 - y1*y2 - z1*z2
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
    } else if (IsNormalizedQuat(quat)) {
        return ConjugateQuat(quat);
    }
    return MultiplyQuatScalar(ConjugateQuat(quat), 1/MagnitudeSquaredQuat(quat));
}

Quaternion NormalizedQuat(Quaternion quat) {

    if (IsZeroQuat(quat)) {
        return ZERO_QUAT;
    }
    return MultiplyQuatScalar(quat, 1/MagnitudeQuat(quat));
}

Quaternion RotationQuat(Vector3 axis, float angle) {

    if (!IsNormalizedVect3(axis)) {
        return ZERO_QUAT;
    }

    float s = sin(angle/2);

    return (Quaternion) {
        s*axis.x,
        s*axis.y,
        s*axis.z,
        cos(angle/2)
    };
}

Quaternion GetQuatMat3(Matrix3 mat) {

    if (!IsOrthogonalMat3(mat)) {
        return ZERO_QUAT;
    }

    Vector3 *cols = GetMat3Columns(mat);
    Vector3 RX = *cols;
    Vector3 RY = *(cols+1);
    Vector3 RZ = *(cols+2);
    free(cols);

    float *eig = GetEigenValMat3(mat);

    if (eig == NULL) {
        return ZERO_QUAT;
    }

    float lambda = *eig;
    free(eig);

    RX.x -= lambda;
    RY.y -= lambda;
    RY = AddVect3(RY, MultiplyVect3Scalar(InverseVect3(RX), RY.x/RX.x));
    Vector3 vect = X_AXIS3;
    vect.y = -RY.z / RY.y;
    vect.x = -(RX.y * vect.y + RX.z * vect.z) / RX.x;

    if (IsZeroVect3(vect)) {
        return ZERO_QUAT;
    }

    return RotationQuat(NormalizedVect3(vect), GetAngleMat3(mat));
}

Quaternion RotateQuat(Quaternion quat, Vector3 axis, float angle) {

    if (!IsNormalizedVect3(axis)) {
        return ZERO_QUAT;
    }

    return MultiplyQuat(RotationQuat(axis, angle), quat);
}

Quaternion FromEulerAnglesQuat(Vector3 eulerAngles, EulerOrder order) {

    float x = eulerAngles.x;
    float y = eulerAngles.y;
    float z = eulerAngles.z;

    Quaternion quat = IDENTITY_QUAT;

    switch (order)
    {
    case EULER_ORDER_XYZ:
        quat = RotateQuat(quat, Z_AXIS3, z);
        quat = RotateQuat(quat, Y_AXIS3, y);
        quat = RotateQuat(quat, X_AXIS3, x);
        break;
    case EULER_ORDER_XZY:
        quat = RotateQuat(quat, Y_AXIS3, y);
        quat = RotateQuat(quat, Z_AXIS3, z);
        quat = RotateQuat(quat, X_AXIS3, x);
        break;
    case EULER_ORDER_YXZ:
        quat = RotateQuat(quat, Z_AXIS3, z);
        quat = RotateQuat(quat, X_AXIS3, x);
        quat = RotateQuat(quat, Y_AXIS3, y);
        break;
    case EULER_ORDER_YZX:
        quat = RotateQuat(quat, X_AXIS3, x);
        quat = RotateQuat(quat, Z_AXIS3, z);
        quat = RotateQuat(quat, Y_AXIS3, y);
        break;
    case EULER_ORDER_ZXY:
        quat = RotateQuat(quat, Y_AXIS3, y);
        quat = RotateQuat(quat, X_AXIS3, x);
        quat = RotateQuat(quat, Z_AXIS3, z);
        break;
    case EULER_ORDER_ZYX:
        quat = RotateQuat(quat, X_AXIS3, x);
        quat = RotateQuat(quat, Y_AXIS3, y);
        quat = RotateQuat(quat, Z_AXIS3, z);
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

/** Multiply a Vector3 by a Quaternion
 * Does stuff
 * @param Vector3 vect
 * @param Quaternion quat
 * @return Quaternion
*/
Quaternion MultiplyVect3Quat(Vector3 vect, Quaternion quat) {

    return MultiplyQuat(FromVect3Quat(vect), quat);
}

// Get a (non-unique) Matrix4 From Quaternion quat
Matrix4 GetMat4Quat(Quaternion quat) {

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

// Get a Matrix3 From Quaternion quat
Matrix3 GetMat3Quat(Quaternion quat) {

    float x = quat.x;
    float y = quat.y;
    float z = quat.z;
    float w = quat.w;
    float s = q_rsqrt(MagnitudeSquaredQuat(quat));
    s *= s;
    return (Matrix3) {{
        {1 - 2*s*(y*y + z*z), 2*s*(x*y - z*w), 2*s*(x*z + y*w)},
        {2*s*(x*y + z*w), 1 - 2*s*(x*x + z*z), 2*s*(y*z - x*w)},
        {2*s*(x*z - y*w), 2*s*(y*z + x*w), 1 - 2*s*(x*x + y*y)}
    }};
}


Vector3 GetEulerAnglesQuat(Quaternion quat, EulerOrder order) {

    return GetEulerAnglesMat3(GetMat3Quat(quat), order);
}



Vector3 GetVect3PartQuat(Quaternion quat) {

    return (Vector3) {quat.x, quat.y, quat.z};
}

Vector3 RotateVect3Quat(Vector3 vect, Vector3 axis, float angle) {

    if (!IsNormalizedVect3(axis)) {
        return ZERO_VECTOR3;
    }

    Quaternion p = FromVect3Quat(vect);
    Quaternion q = RotationQuat(axis, angle);

    return GetVect3PartQuat(MultiplyQuat(q, MultiplyQuat(p, InverseQuat(q))));
}

Vector3 GetAxisQuat(Quaternion quat) {

    if (IsZeroF(GetAngleQuat(quat))) {
        return ZERO_VECTOR3;
    }

    return MultiplyVect3Scalar(GetVect3PartQuat(quat), 1/sin(GetAngleQuat(quat)/2));
}



float DotProductQuat(Quaternion quat1, Quaternion quat2) {

    return quat1.x*quat2.x + quat1.y*quat2.y + quat1.z*quat2.z + quat1.w*quat2.w;
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
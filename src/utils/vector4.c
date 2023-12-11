#include "../../inc/utils/vector4.h"


const Vector4 ZERO_VECTOR4 = (Vector4) {0.0f, 0.0f, 0.0f, 0.0f};
const Vector4 ONE_VECTOR4 = (Vector4) {1.0f, 1.0f, 1.0f, 1.0f};
const Vector4 X_AXIS4 = (Vector4) {1.0f, 0.0f, 0.0f, 0.0f};
const Vector4 Y_AXIS4 = (Vector4) {0.0f, 1.0f, 0.0f, 0.0f};
const Vector4 Z_AXIS4 = (Vector4) {0.0f, 0.0f, 0.0f, 1.0f};
const Vector4 W_AXIS4 = (Vector4) {0.0f, 0.0f, 0.0f, 1.0f};



Vector4 *CreateVect4(float x, float y, float z, float w) {

    Vector4 *vect = (Vector4*)malloc(sizeof(Vector4));

    if (vect==NULL) {
        fprintf(stderr,"Error allocating memory for struct Vector4.\n");
        return NULL;
    }

    vect->x = x;
    vect->y = y;
    vect->z = z;
    vect->w = w;

    return vect;
}

void DestroyVect4(Vector4 *vect) {

    if (vect != NULL) {
        free(vect);
    }
}



float *Vect4ToArray(Vector4 vect) {

    static float arr[4];

    arr[0] = vect.x;
    arr[1] = vect.y;
    arr[2] = vect.z;
    arr[3] = vect.w;

    return arr;
}


Vector4 AddVect4(Vector4 vect1, Vector4 vect2) {

    return (Vector4) {vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z, vect1.w + vect2.w};
}

Vector4 MultiplyVect4Scalar(Vector4 vect, float k) {

    return (Vector4) {vect.x*k, vect.y*k, vect.z*k, vect.w*k};
}

Vector4 InverseVect4(Vector4 vect) {

    return (Vector4) {-vect.x, -vect.y, -vect.z, -vect.w};
}

Vector4 NormalizedVect4(Vector4 vect) {

    if (IsZeroVect4(vect)) {
        return ZERO_VECTOR4;
    }
    return MultiplyVect4Scalar(vect, (float)1/MagnitudeVect4(vect));
}

Vector4 LerpVect4(Vector4 from, Vector4 to, float t) {

    return (Vector4) {Lerp(from.x, to.x, t), Lerp(from.y, to.y, t), Lerp(from.z, to.z, t), Lerp(from.w, to.w, t)};
}

Vector4 DirectionVect4(Vector4 from, Vector4 to) {

    return NormalizedVect4(AddVect4(to, InverseVect4(from)));
}

Vector4 ProjectVect4(Vector4 vect, Vector4 on) {

    if (IsZeroF(MagnitudeSquaredVect4(on))) {
        return ZERO_VECTOR4;
    }

    return MultiplyVect4Scalar(on, DotProductVect4(vect, on)/MagnitudeSquaredVect4(on));
}

Vector4 ArrayToVect4(float arr[3]) {

    return (Vector4) {arr[0], arr[1], arr[2]};
}

Vector4 FromVect3(Vector3 vect) {

    return (Vector4) {vect.x, vect.y, vect.z, 0.0f};
}



float DotProductVect4(Vector4 vect1, Vector4 vect2) {

    return vect1.x*vect2.x + vect1.y*vect2.y + vect1.z*vect2.z + vect1.w*vect2.w;
}

float MagnitudeSquaredVect4(Vector4 vect) {

    return DotProductVect4(vect, vect);
}

float MagnitudeVect4(Vector4 vect) {

    return sqrt(MagnitudeSquaredVect4(vect));
}

float AngleVect4(Vector4 vect1, Vector4 vect2) {

    return (float)acos((double) DotProductVect4(vect1, vect2)/(MagnitudeVect4(vect1)*MagnitudeVect4(vect2)));
}

float DistanceSquaredVect4(Vector4 from, Vector4 to) {

    return MagnitudeSquaredVect4(AddVect4(to, InverseVect4(from)));
}

float DistanceVect4(Vector4 from, Vector4 to) {

    return sqrt(DistanceSquaredVect4(from, to));
}



bool IsZeroVect4(Vector4 vect) {

    return fabs(vect.x) < 1e-6 && fabs(vect.y) < 1e-6 && fabs(vect.z) < 1e-6 && fabs(vect.w) < 1e-6;
}

bool EqualVect4(Vector4 vect1, Vector4 vect2) {

    return IsZeroVect4(AddVect4(vect1, InverseVect4(vect2)));
}

bool IsNormalizedVect4(Vector4 vect) {

    return EqualVect4(vect, NormalizedVect4(vect));
}


void PrintVect4(Vector4 vect) {

    printf("struct Vector4: (%f, %f, %f, %f)\n", vect.x, vect.y, vect.z, vect.w);
}
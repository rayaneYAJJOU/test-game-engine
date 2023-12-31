#include "../../inc/utils/vector3.h"


const Vector3 ZERO_VECTOR3 = (Vector3) {0.0f, 0.0f, 0.0f};
const Vector3 ONE_VECTOR3 = (Vector3) {1.0f, 1.0f, 1.0f};
const Vector3 X_AXIS3 = (Vector3) {1.0f, 0.0f, 0.0f};
const Vector3 Y_AXIS3 = (Vector3) {0.0f, 1.0f, 0.0f};
const Vector3 Z_AXIS3 = (Vector3) {0.0f, 0.0f, 1.0f};


float *Vect3ToArray(Vector3 vect) {

    static float arr[3];

    arr[0] = vect.x;
    arr[1] = vect.y;
    arr[2] = vect.z;

    return arr;
}


Vector3* CreateVect3(float x, float y, float z) {

    Vector3 *vect = (Vector3*)malloc(sizeof(Vector3));

    if (vect==NULL) {
        fprintf(stderr,"Error allocating memory for struct Vector3.\n");
        return NULL;
    }

    vect->x = x;
    vect->y = y;
    vect->z = z;

    return vect;
}

void DestroyVect3(Vector3 *vect) {

    if (vect!=NULL) {
        free(vect);
    }
}



Vector3 AddVect3(Vector3 vect1, Vector3 vect2) {

    return (Vector3) {vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z};
}

Vector3 MultiplyVect3Scalar(Vector3 vect, float k) {

    return (Vector3) {vect.x*k, vect.y*k, vect.z*k};
}

Vector3 RotateVect3(Vector3 vect, Vector3 axis, float angle) {

    Vector3 axisNormalized = NormalizedVect3(axis);

    if (IsZeroVect3(axisNormalized)) {
        return ZERO_VECTOR3;
    }

    float a = axisNormalized.x;
    float b = axisNormalized.y;
    float c = axisNormalized.z;
    float x = vect.x;
    float y = vect.y;
    float z = vect.z;

    return (Vector3) {
        x*(cos(angle) + a*a*(1-cos(angle))) + y*(a*b*(1-cos(angle)) - c*sin(angle)) + z*(a*c*(1-cos(angle)) + b*sin(angle)),
        x*(a*b*(1-cos(angle)) + c*sin(angle)) + y*(cos(angle) + b*b*(1-cos(angle))) + z*(b*c*(1-cos(angle)) - a*sin(angle)),
        x*(a*c*(1-cos(angle)) - b*sin(angle)) + y*(b*c*(1-cos(angle)) + a*sin(angle)) + z*(cos(angle) + c*c*(1-cos(angle)))
    };
}

Vector3 InverseVect3(Vector3 vect) {

    return (Vector3) {-vect.x, -vect.y, -vect.z};
}

Vector3 NormalizedVect3(Vector3 vect) {

    if (IsZeroVect3(vect)) {
        return ZERO_VECTOR3;
    }
    return MultiplyVect3Scalar(vect, (float)1/MagnitudeVect3(vect));
}

Vector3 LerpVect3(Vector3 from, Vector3 to, float t) {

    return (Vector3) {Lerp(from.x, to.x, t), Lerp(from.y, to.y, t), Lerp(from.z, to.z, t)};
}

Vector3 CrossProductVect3(Vector3 vect1, Vector3 vect2) {

    if (EqualVect3(vect1,vect2)) {
        return ZERO_VECTOR3;
    }
    return (Vector3) {
        vect1.y*vect2.z - vect1.z*vect2.y,
        vect1.z*vect2.x - vect1.x*vect2.z,
        vect1.x*vect2.y - vect1.y*vect2.x
    };
}

Vector3 DirectionVect3(Vector3 from, Vector3 to) {

    return NormalizedVect3(AddVect3(to, InverseVect3(from)));
}

Vector3 BounceVect3(Vector3 vect, Vector3 normal) {

    return RotateVect3(vect, CrossProductVect3(normal, vect), 2*AngleVect3(vect, normal));
}

Vector3 ReflectVect3(Vector3 vect, Vector3 dir) {

    return BounceVect3(vect, RotateVect3(dir, CrossProductVect3(dir, vect), PI/2));
}

Vector3 ProjectVect3(Vector3 vect, Vector3 on) {

    if (IsZeroF(MagnitudeSquaredVect3(on))) {
        return ZERO_VECTOR3;
    }

    return MultiplyVect3Scalar(on, DotProductVect3(vect, on)/MagnitudeSquaredVect3(on));
}

Vector3 ArrayToVect3(float arr[3]) {

    return (Vector3) {arr[0], arr[1], arr[2]};
}

Vector3 FromVect2(Vector2 vect) {

    return (Vector3) {vect.x, vect.y, 0.0f};
}

Vector3 CrossProductVect2(Vector2 vect1, Vector2 vect2) {

    return CrossProductVect3(FromVect2(vect1), FromVect2(vect2));
}



float DotProductVect3(Vector3 vect1, Vector3 vect2) {

    return vect1.x*vect2.x + vect1.y*vect2.y + vect1.z*vect2.z;
}

float MagnitudeSquaredVect3(Vector3 vect) {

    return DotProductVect3(vect, vect);
}

float MagnitudeVect3(Vector3 vect) {

    return sqrt(MagnitudeSquaredVect3(vect));
}

float AngleVect3(Vector3 vect1, Vector3 vect2) {

    return (float)acos((double) DotProductVect3(vect1, vect2)/(MagnitudeVect3(vect1)*MagnitudeVect3(vect2)));
}

float DistanceSquaredVect3(Vector3 from, Vector3 to) {

    return MagnitudeSquaredVect3(AddVect3(to, InverseVect3(from)));
}

float DistanceVect3(Vector3 from, Vector3 to) {

    return sqrt(DistanceSquaredVect3(from, to));
}

float TripleProductVect3(Vector3 vect1, Vector3 vect2, Vector3 vect3) {

    return DotProductVect3(vect1, CrossProductVect3(vect2, vect3));
}



bool IsZeroVect3(Vector3 vect) {

    return fabs(vect.x) < 1e-6 && fabs(vect.y) < 1e-6 && fabs(vect.z) < 1e-6;
}

bool EqualVect3(Vector3 vect1, Vector3 vect2) {

    return IsZeroVect3(AddVect3(vect1, InverseVect3(vect2)));
}

bool IsNormalizedVect3(Vector3 vect) {

    return EqualVect3(vect, NormalizedVect3(vect));
}


void PrintVect3(Vector3 vect) {

    printf("struct Vector3: (%f, %f, %f)\n", vect.x, vect.y, vect.z);
}
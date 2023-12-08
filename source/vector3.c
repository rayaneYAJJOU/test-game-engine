#include "../header/vector3.h"


const Vector3 ZERO_VECTOR = (Vector3) {0.0, 0.0, 0.0};
const Vector3 ONE_VECTOR = (Vector3) {1.0, 1.0, 1.0};
const Vector3 X_AXIS = (Vector3) {1.0, 0.0, 1.0};
const Vector3 Y_AXIS = (Vector3) {0.0, 1.0, 0.0};
const Vector3 Z_AXIS = (Vector3) {0.0, 0.0, 1.0};



Vector3* CreateVect(float x, float y, float z) {

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

void DestroyVect(Vector3 *vect) {

    if (vect!=NULL) {
        free(vect);
    }
}



Vector3 AddVects(Vector3 vect1, Vector3 vect2) {

    return (Vector3) {vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z};
}

Vector3 MultiplyScalarVect(Vector3 vect, float k) {

    return (Vector3) {vect.x*k, vect.y*k, vect.z*k};
}

Vector3 RotateVect(Vector3 vect, Vector3 axis, float angle) {

    Vector3 axisNormalized = NormalizedVect(axis);
    float a = axisNormalized.x;
    float b = axisNormalized.y;
    float c = axisNormalized.z;
    float x = vect.x;
    float y = vect.y;
    float z = vect.z;

    return (Vector3) {
        x*(cos(angle) + pow(a,2.0)*(1-cos(angle))) + y*(a*b*(1-cos(angle)) - c*sin(angle)) + z*(a*c*(1-cos(angle)) + b*sin(angle)),
        x*(a*b*(1-cos(angle)) + c*sin(angle)) + y*(cos(angle) + pow(b,2.0)*(1-cos(angle))) + z*(b*c*(1-cos(angle)) - a*sin(angle)),
        x*(a*c*(1-cos(angle)) - b*sin(angle)) + y*(b*c*(1-cos(angle)) + a*sin(angle)) + z*(cos(angle) + pow(c,2.0)*(1-cos(angle)))
    };
}

Vector3 InverseVect(Vector3 vect) {

    return (Vector3) {-vect.x, -vect.y, -vect.z};
}

Vector3 NormalizedVect(Vector3 vect) {

    assert(!(IsZeroVect(vect)));
    return MultiplyScalarVect(vect, (float)1/MagnitudeVect(vect));
}

Vector3 LerpVect(Vector3 from, Vector3 to, float t) {

    return (Vector3) {Lerp(from.x, to.x, t), Lerp(from.y, to.y, t), Lerp(from.z, to.z, t)};
}

Vector3 CrossProduct(Vector3 vect1, Vector3 vect2) {

    if (EqualVects(vect1,vect2)) {
        return ZERO_VECTOR;
    }
    return (Vector3) {
        vect1.y*vect2.z - vect1.z*vect2.y,
        vect1.z*vect2.x - vect1.x*vect2.z,
        vect1.x*vect2.y - vect1.y*vect2.x
    };
}

Vector3 DirectionVect(Vector3 from, Vector3 to) {

    return NormalizedVect(AddVects(to, InverseVect(from)));
}

Vector3 BounceVect(Vector3 vect, Vector3 normal) {

    return RotateVect(vect, CrossProduct(normal, vect), 2*AngleVects(vect, normal));
}

Vector3 ReflectVect(Vector3 vect, Vector3 normal) {

    return BounceVect(vect, RotateVect(normal, CrossProduct(normal, vect), PI/2));
}



float DotProductVects(Vector3 vect1, Vector3 vect2) {

    return vect1.x*vect2.x + vect1.y*vect2.y + vect1.z*vect2.z;
}

float MagnitudeSquaredVect(Vector3 vect) {

    return DotProductVects(vect, vect);
}

float MagnitudeVect(Vector3 vect) {

    return sqrt(MagnitudeSquaredVect(vect));
}

float AngleVects(Vector3 vect1, Vector3 vect2) {

    return (float)acos((double) DotProductVects(vect1, vect2)/(MagnitudeVect(vect1)*MagnitudeVect(vect2)));
}

float DistanceSquaredVects(Vector3 from, Vector3 to) {

    return MagnitudeSquaredVect(DirectionVect(from, to));
}

float DistanceVects(Vector3 from, Vector3 to) {

    return sqrt(DistanceSquaredVects(from, to));
}



bool IsZeroVect(Vector3 vect) {

    return fabs(vect.x) < 10e-6 && fabs(vect.y) < 10e-6 && fabs(vect.z) < 10e-6;
}

bool EqualVects(Vector3 vect1, Vector3 vect2) {

    return IsZeroVect(AddVects(vect1, InverseVect(vect2)));
}

bool IsNormalizedVect(Vector3 vect) {

    return EqualVects(vect, NormalizedVect(vect));
}
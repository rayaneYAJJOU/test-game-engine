#include "../../inc/utils/vector2.h"

const Vector2 ZERO_VECTOR2 = (Vector2) {0.0f, 0.0f};
const Vector2 ONE_VECTOR2 = (Vector2) {1.0f, 1.0f};
const Vector2 X_AXIS2 = (Vector2) {1.0f, 0.0f};
const Vector2 Y_AXIS2 = (Vector2) {0.0f, 1.0f};


float *Vect2ToArray(Vector2 vect) {

    static float arr[2];
    arr[0] = vect.x;
    arr[1] = vect.y;

    return arr;
}


Vector2* CreateVect2(float x, float y) {

    Vector2 *vect = (Vector2*)malloc(sizeof(Vector2));

    if (vect == NULL) {
        fprintf(stderr,"Error allocating memory for struct Vector2.\n");
        return NULL;
    }

    vect->x = x;
    vect->y = y;

    return vect;
}

void DestroyVect2(Vector2* vect) {

    if (vect != NULL) {
        free(vect);
    }
}


Vector2 AddVect2(Vector2 vect1, Vector2 vect2) {

    return (Vector2) {vect1.x + vect2.x, vect1.y + vect2.y};
}

Vector2 MultiplyVect2Scalar(Vector2 vect, float k) {

    return (Vector2) {vect.x * k, vect.y * k};
}

Vector2 RotateVect2(Vector2 vect, float angle) {

    return (Vector2) {
        vect.x*cos(angle) - vect.y*sin(angle),
        vect.x*sin(angle) + vect.y*cos(angle)
    };
}

Vector2 InverseVect2(Vector2 vect) {

    return (Vector2) {-vect.x, -vect.y};
}

Vector2 NormalizedVect2(Vector2 vect) {

    if (IsZeroVect2(vect)) {
        return ZERO_VECTOR2;
    }
    return MultiplyVect2Scalar(vect, (float)1/MagnitudeVect2(vect));
}

Vector2 LerpVect2(Vector2 from, Vector2 to, float t) {

    return (Vector2) {Lerp(from.x, to.x, t), Lerp(from.y, to.y, t)};
}

Vector2 DirectionVect2(Vector2 from, Vector2 to) {

    return NormalizedVect2(AddVect2(to, InverseVect2(from)));
}

Vector2 BounceVect2(Vector2 vect, Vector2 normal) {

    return RotateVect2(vect, 2*AngleVect2(vect, normal));
}

Vector2 ReflectVect2(Vector2 vect, Vector2 dir) {

    return BounceVect2(vect, RotateVect2(dir, PI/2));
}

Vector2 ProjectVect2(Vector2 vect, Vector2 on) {

    if (IsZeroF(MagnitudeSquaredVect2(on))) {
        return ZERO_VECTOR2;
    }
    
    return MultiplyVect2Scalar(on, DotProductVect2(vect, on));
}

Vector2 ArrayToVect2(float arr[2]) {

    return (Vector2) {arr[0], arr[1]};
}


float DotProductVect2(Vector2 vect1, Vector2 vect2) {

    return vect1.x*vect2.x + vect1.y*vect2.y;
}

float MagnitudeSquaredVect2(Vector2 vect) {

    return DotProductVect2(vect, vect);
}

float MagnitudeVect2(Vector2 vect) {

    return sqrt(MagnitudeSquaredVect2(vect));
}

float AngleVect2(Vector2 vect1, Vector2 vect2) {

    return (float)acos((double) DotProductVect2(vect1, vect2)/(MagnitudeVect2(vect1)*MagnitudeVect2(vect2)));
}

float DistanceSquaredVect2(Vector2 from, Vector2 to) {

    return MagnitudeSquaredVect2(AddVect2(to, InverseVect2(from)));
}

float DistanceVect2(Vector2 from, Vector2 to) {

    return sqrt(DistanceSquaredVect2(from, to));
}


bool IsZeroVect2(Vector2 vect) {

    return fabs(vect.x) < 1e-6 && fabs(vect.y) < 1e-6;
}

bool EqualVect2(Vector2 vect1, Vector2 vect2) {

    return IsZeroVect2(AddVect2(vect1, InverseVect2(vect2)));
}

bool IsNormalizedVect2(Vector2 vect) {

    return EqualVect2(vect, NormalizedVect2(vect));
}

void PrintVect2(Vector2 vect) {

    printf("struct Vector2: (%f, %f)\n", vect.x, vect.y);
}
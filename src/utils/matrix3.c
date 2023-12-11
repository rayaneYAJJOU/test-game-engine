#include "../../inc/utils/matrix3.h"


const Matrix3 IDENTITY_MAT3 = (Matrix3){{{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}};
const Matrix3 ZERO_MAT3 = (Matrix3){{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}};
const Matrix3 ONE_MAT3 = (Matrix3){{{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}};


Matrix3 *CreateMat3(float matrix[3][3]) {

    Matrix3 *mat = (Matrix3*)malloc(sizeof(Matrix3));

    if (mat == NULL) {
        fprintf(stderr,"Error allocating memory for struct Matrix.\n");
        return NULL;
    }

    memcpy(mat->matrix, matrix, sizeof(float)*9);

    return mat;
}

void DestroyMat3(Matrix3 *mat) {

    if (mat != NULL) {
        free(mat);
    }
}


Matrix3 AddMat3(Matrix3 mat1, Matrix3 mat2) {

    Matrix3 mat = ZERO_MAT3;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            mat.matrix[i][j] = mat1.matrix[i][j] + mat2.matrix[i][j];
        }
    }

    return mat;
}

Matrix3 MultiplyMat3(Matrix3 mat1, Matrix3 mat2) {

    Matrix3 mat = ZERO_MAT3;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            mat.matrix[i][j] = Sum(3, mat1.matrix[i][0]*mat2.matrix[0][j], mat1.matrix[i][1]*mat2.matrix[1][j], mat1.matrix[i][2]*mat2.matrix[2][j]);
        }
    }
    
    return mat;
}

Matrix3 MultiplyMat3Scalar(Matrix3 mat, float k) {

    Matrix3 mat_ = ZERO_MAT3;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            mat_.matrix[i][j] = mat.matrix[i][j] * k;
        }
    }
    
    return mat_;
}

Matrix3 AdditiveInverseMat3(Matrix3 mat) {

    return AddMat3(ZERO_MAT3, MultiplyMat3Scalar(mat, -1.0f));
}

Matrix3 TransposeMat3(Matrix3 mat) {

    Matrix3 tmat = ZERO_MAT3;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            tmat.matrix[i][j] = mat.matrix[j][i];
        }
    }

    return tmat;
}

Matrix3 InverseMat3(Matrix3 mat) {

    if (IsZeroF(DeterminantMat3(mat))) {
        return ZERO_MAT3;
    }
    float cof11 = DeterminantMat2((Matrix2){{{mat.matrix[1][1], mat.matrix[1][2]},{mat.matrix[2][1], mat.matrix[2][2]}}});
    float cof12 = -DeterminantMat2((Matrix2){{{mat.matrix[1][0], mat.matrix[1][2]},{mat.matrix[2][0], mat.matrix[2][2]}}});
    float cof13 = DeterminantMat2((Matrix2){{{mat.matrix[1][0], mat.matrix[1][1]},{mat.matrix[2][0], mat.matrix[2][1]}}});
    float cof21 = -DeterminantMat2((Matrix2){{{mat.matrix[0][1], mat.matrix[0][2]},{mat.matrix[2][1], mat.matrix[2][2]}}});
    float cof22 = DeterminantMat2((Matrix2){{{mat.matrix[0][0], mat.matrix[0][2]},{mat.matrix[2][0], mat.matrix[2][2]}}});
    float cof23 = -DeterminantMat2((Matrix2){{{mat.matrix[0][0], mat.matrix[0][1]},{mat.matrix[2][0], mat.matrix[2][1]}}});
    float cof31 = DeterminantMat2((Matrix2){{{mat.matrix[0][1], mat.matrix[1][2]},{mat.matrix[1][1], mat.matrix[1][2]}}});
    float cof32 = -DeterminantMat2((Matrix2){{{mat.matrix[0][0], mat.matrix[1][2]},{mat.matrix[1][0], mat.matrix[1][2]}}});
    float cof33 = DeterminantMat2((Matrix2){{{mat.matrix[0][0], mat.matrix[1][1]},{mat.matrix[1][0], mat.matrix[1][1]}}});
    return MultiplyMat3Scalar((Matrix3){{{cof11, cof12, cof13},{cof21, cof22, cof23},{cof31, cof32, cof33}}}, 1/DeterminantMat3(mat));
}
/*
Matrix3 RotationMat3Z(float angle) {

    return (Matrix3) {{
        {cos(angle), -sin(angle), 0.0f},
        {sin(angle), cos(angle), 0.0f},
        {0.0f, 0.0f, 1.0f}
    }};
}

Matrix3 RotationMat3Y(float angle) {

    return (Matrix3) {{
        {cos(angle), 0.0f, sin(angle)},
        {0.0f, 1.0f, 0.0f},
        {-sin(angle), 0.0f, cos(angle)}
    }};
}

Matrix3 RotationMat3X(float angle) {

    return (Matrix3) {{
        {1.0f, 0.0f, 0.0f},
        {0.0f, cos(angle), -sin(angle)},
        {0.0f, sin(angle), cos(angle)}
    }};
}
*/

Matrix3 RotationMat3(Vector3 axis, float angle) {

    if (!IsNormalizedVect3(axis)) {
        return ZERO_MAT3;
    }
    float a = axis.x;
    float b = axis.y;
    float c = axis.z;
    float ca = cos(angle);
    float sa = sin(angle);

    return (Matrix3) {{
        {ca + a*a*(1-ca), a*b*(1-ca) - c*sa, a*c*(1-ca) + b*sa},
        {a*b*(1-ca) + c*sa, ca + b*b*(1-ca), b*c*(1-ca) - a*sa},
        {a*c*(1-ca) - b*sa, b*c*(1-ca) + a*sa, ca + c*c*(1-ca)}
    }};
}


Matrix3 FromEulerAnglesMat3(Vector3 eulerAngles, EulerOrder order) {

    float x = eulerAngles.x;
    float y = eulerAngles.y;
    float z = eulerAngles.z;

    Matrix3 R = IDENTITY_MAT3;

    switch (order)
    {
    case EULER_ORDER_XYZ:
        R = RotateMat3(R, Z_AXIS3, z);
        R = RotateMat3(R, Y_AXIS3, y);
        R = RotateMat3(R, X_AXIS3, x);
        break;
    case EULER_ORDER_XZY:
        R = RotateMat3(R, Y_AXIS3, y);
        R = RotateMat3(R, Z_AXIS3, z);
        R = RotateMat3(R, X_AXIS3, x);
        break;
    case EULER_ORDER_YXZ:
        R = RotateMat3(R, Z_AXIS3, z);
        R = RotateMat3(R, X_AXIS3, x);
        R = RotateMat3(R, Y_AXIS3, y);
        break;
    case EULER_ORDER_YZX:
        R = RotateMat3(R, X_AXIS3, x);
        R = RotateMat3(R, Z_AXIS3, z);
        R = RotateMat3(R, Y_AXIS3, y);
        break;
    case EULER_ORDER_ZXY:
        R = RotateMat3(R, Y_AXIS3, y);
        R = RotateMat3(R, X_AXIS3, x);
        R = RotateMat3(R, Z_AXIS3, z);
        break;
    case EULER_ORDER_ZYX:
        R = RotateMat3(R, X_AXIS3, x);
        R = RotateMat3(R, Y_AXIS3, y);
        R = RotateMat3(R, Z_AXIS3, z);
        break;
    }

    return R;
}


Vector3 MultiplyMat3Vect3(Matrix3 mat, Vector3 vect) {

    return (Vector3) {
        mat.matrix[0][0]*vect.x + mat.matrix[0][1]*vect.y + mat.matrix[0][2]*vect.z,
        mat.matrix[1][0]*vect.x + mat.matrix[1][1]*vect.y + mat.matrix[1][2]*vect.z,
        mat.matrix[2][0]*vect.x + mat.matrix[2][1]*vect.y + mat.matrix[2][2]*vect.z
    };
}

Vector3 GetEulerAnglesMat3(Matrix3 mat, EulerOrder order) {

    float a1, a2, a3;
    float R00 = mat.matrix[0][0];
    float R01 = mat.matrix[0][1];
    float R02 = mat.matrix[0][2];
    float R10 = mat.matrix[1][0];
    float R11 = mat.matrix[1][1];
    float R12 = mat.matrix[1][2];
    float R20 = mat.matrix[2][0];
    float R21 = mat.matrix[2][1];
    float R22 = mat.matrix[2][2];

    switch (order) {
    case EULER_ORDER_XYZ:
        a1 = atan2(-R12, R22);
        a2 = asin(fmaxf(fminf(R02, 1.0f), -1.0f));
        a3 = atan2(-R01, R00);
        break;
    case EULER_ORDER_XZY:
        a1 = atan2(R21, R11);
        a3 = asin(fmaxf(fminf(-R01, 1.0f), -1.0f));
        a2 = atan2(R02, R00);
        break;
    case EULER_ORDER_YXZ:
        a2 = atan2(R02, R22);
        a1 = asin(fmaxf(fminf(-R12, 1.0f), -1.0f));
        a3 = atan2(R10, R11);
        break;
    case EULER_ORDER_YZX:
        a2 = atan2(-R21, R00);
        a3 = asin(fmaxf(fminf(R10, 1.0f), -1.0f));
        a1 = atan2(-R12, R11);
        break;
    case EULER_ORDER_ZXY:
        a3 = atan2(R10, R11);
        a1 = asin(fmaxf(fminf(-R20, 1.0f), -1.0f));
        a2 = atan2(R21, R22);
        break;
    case EULER_ORDER_ZYX:
        a3 = atan2(-R01, R11);
        a2 = asin(fmaxf(fminf(R21, 1.0f), -1.0f));
        a1 = atan2(-R20, R22);
        break;
    }

    return (Vector3) {a1, a2, a3};
}

Matrix3 Mat3FromVect3(Vector3 col1, Vector3 col2, Vector3 col3) {

    float *col1Ptr = Vect3ToArray(col1);
    float *col2Ptr = Vect3ToArray(col2);
    float *col3Ptr = Vect3ToArray(col3);
    Matrix3 mat = ZERO_MAT3;

    for (int i=0;i<3;i++) {
        mat.matrix[i][0] = *(col1Ptr+i);
        mat.matrix[i][1] = *(col2Ptr+i);
        mat.matrix[i][2] = *(col3Ptr+i);
    }

    return mat;
}

Matrix3 OrthonormalizeMat3(Matrix3 mat) {

    if (IsOrthogonalMat3(mat)) {
        return mat;
    }

    Vector3 *cols = GetMat3Columns(mat);
    if (cols == NULL) {
        return ZERO_MAT3;
    }
    Vector3 v1 = *cols;
    Vector3 v2 = *(cols+1);
    Vector3 v3 = *(cols+2);
    free(cols);
    
    Vector3 u2 = AddVect3(v2, InverseVect3(ProjectVect3(v2, v1)));
    Vector3 u3 = AddVect3(v3, InverseVect3(ProjectVect3(v3, v1)));
    u3 = AddVect3(u3, InverseVect3(ProjectVect3(v3, u2)));

    return Mat3FromVect3(NormalizedVect3(v1), NormalizedVect3(u2), NormalizedVect3(u3));
}

Matrix3 RotateMat3(Matrix3 mat, Vector3 axis, float angle) {

    if (!IsOrthogonalMat3(mat)) {
        return ZERO_MAT3;
    }

    return MultiplyMat3(RotationMat3(axis, angle), mat);
}

Matrix3 ScaleMat3(Matrix3 mat, Vector3 scale) {

    Matrix3 scal = Mat3FromVect3(MultiplyVect3Scalar(X_AXIS3, mat.matrix[0][0]), ZERO_VECTOR3, ZERO_VECTOR3);
    scal = AddMat3(scal, Mat3FromVect3(ZERO_VECTOR3, MultiplyVect3Scalar(Y_AXIS3, mat.matrix[1][1]), ZERO_VECTOR3));
    scal = AddMat3(scal, Mat3FromVect3(ZERO_VECTOR3, ZERO_VECTOR3, MultiplyVect3Scalar(Z_AXIS3, mat.matrix[2][2])));

    if (!EqualMat3(mat, scal)) {
        return ZERO_MAT3;
    }

    Matrix3 scalv = Mat3FromVect3(MultiplyVect3Scalar(X_AXIS3, scale.x), ZERO_VECTOR3, ZERO_VECTOR3);
    scalv = AddMat3(scalv, Mat3FromVect3(ZERO_VECTOR3, MultiplyVect3Scalar(Y_AXIS3, scale.y), ZERO_VECTOR3));
    scalv = AddMat3(scalv, Mat3FromVect3(ZERO_VECTOR3, ZERO_VECTOR3, MultiplyVect3Scalar(Z_AXIS3, scale.z)));

    return MultiplyMat3(mat, scalv);
}

Matrix3 ScalarMat3(float k) {

    return MultiplyMat3Scalar(IDENTITY_MAT3, k);
}



Vector3 *GetMat3Columns(Matrix3 mat) {

    Matrix3 tmat = TransposeMat3(mat);
    static Vector3 arr[3];

    for (int i=0; i<3; i++) {
        arr[i] = ArrayToVect3(tmat.matrix[i]);
    }

    return arr;
}



float TraceMat3(Matrix3 mat) {

    return mat.matrix[0][0] + mat.matrix[1][1] + mat.matrix[2][2];
}

float DeterminantMat3(Matrix3 mat) {

    Matrix2 com1 = (Matrix2){{{mat.matrix[1][1], mat.matrix[1][2]},{mat.matrix[2][1], mat.matrix[2][2]}}};
    Matrix2 com2 = (Matrix2){{{mat.matrix[1][0], mat.matrix[1][2]},{mat.matrix[2][0], mat.matrix[2][2]}}};
    Matrix2 com3 = (Matrix2){{{mat.matrix[1][0], mat.matrix[1][1]},{mat.matrix[2][0], mat.matrix[2][1]}}};
    return mat.matrix[0][0]*DeterminantMat2(com1) - mat.matrix[0][1]*DeterminantMat2(com2) + mat.matrix[0][2]*DeterminantMat2(com3);
}

float GetAngleMat3(Matrix3 mat) {

    if (!IsOrthogonalMat3(mat)) {
        return 0.0f;
    }

    return acos((TraceMat3(mat)-1)*0.5f);
}

float CharPolMat3(Matrix3 mat, float x) {

    return DeterminantMat3(AddMat3(ScalarMat3(x), AdditiveInverseMat3(mat)));
}


float *GetEigenValMat3(Matrix3 mat) {

    float trace = TraceMat3(mat);
    return GetRootsPol3(-trace, 0.5f*(trace*trace - TraceMat3(MultiplyMat3(mat, mat))), -DeterminantMat3(mat));
}


bool IsOrthogonalMat3(Matrix3 mat) {

    float det = DeterminantMat3(mat);
    return IsZeroF(det*det - 1);
}

bool IsZeroMat3(Matrix3 mat) {

    Vector3 *cols = GetMat3Columns(mat);
    return IsZeroVect3(*cols) && IsZeroVect3(*(cols+1)) && IsZeroVect3(*(cols+2));
}

bool EqualMat3(Matrix3 mat1, Matrix3 mat2) {

    return IsZeroMat3(AddMat3(mat1, AdditiveInverseMat3(mat2)));
}


void PrintMat3(Matrix3 mat) {

    printf("struct Matrix3: \n");
    for (int i=0; i<3; i++) {
        printf("[");
        for (int j=0; j<3; j++) {
            if (j==2) {
                printf("%f]",mat.matrix[i][j]);
            } else {
                printf("%f, ",mat.matrix[i][j]);
            }
        }
        printf("\n");
    }
}
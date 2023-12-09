#include "../../inc/utils/matrix3.h"


const Matrix3 IDENTITY_MAT3 = (Matrix3){{{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}};
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


Vector3 MultiplyMat3Vect3(Matrix3 mat, Vector3 vect) {

    return (Vector3) {
        mat.matrix[0][0]*vect.x + mat.matrix[0][1]*vect.y + mat.matrix[0][2]*vect.z,
        mat.matrix[1][0]*vect.x + mat.matrix[1][1]*vect.y + mat.matrix[1][2]*vect.z,
        mat.matrix[2][0]*vect.x + mat.matrix[2][1]*vect.y + mat.matrix[2][2]*vect.z
    };
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
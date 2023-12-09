#include "../../inc/utils/matrix2.h"


const Matrix2 IDENTITY_MAT2 = (Matrix2){{{1.0f, 0.0f}, {0.0f, 1.0f}}};
const Matrix2 ZERO_MAT2 = (Matrix2){{{0.0f, 0.0f}, {0.0f, 0.0f}}};
const Matrix2 ONE_MAT2 = (Matrix2){{{1.0f, 1.0f}, {1.0f, 1.0f}}};


Matrix2 *CreateMat2(float matrix[2][2]) {

    Matrix2 *mat = (Matrix2*)malloc(sizeof(Matrix2));

    if (mat == NULL) {
        fprintf(stderr,"Error allocating memory for struct Matrix.\n");
        return NULL;
    }

    memcpy(mat->matrix, matrix, sizeof(float)*4);

    return mat;
}

void DestroyMat2(Matrix2 *mat) {

    if (mat != NULL) {
        free(mat);
    }
}


Matrix2 AddMat2(Matrix2 mat1, Matrix2 mat2) {

    Matrix2 mat = ZERO_MAT2;

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            mat.matrix[i][j] = mat1.matrix[i][j] + mat2.matrix[i][j];
        }
    }

    return mat;
}

Matrix2 MultiplyMat2(Matrix2 mat1, Matrix2 mat2) {

    Matrix2 mat = ZERO_MAT2;

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            mat.matrix[i][j] = Sum(2, mat1.matrix[i][0]*mat2.matrix[0][j], mat1.matrix[i][1]*mat2.matrix[1][j]);
        }
    }
    
    return mat;
}

Matrix2 MultiplyMat2Scalar(Matrix2 mat, float k) {

    Matrix2 mat_ = ZERO_MAT2;

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            mat_.matrix[i][j] = mat.matrix[i][j] * k;
        }
    }
    
    return mat_;
}

Matrix2 AdditiveInverseMat2(Matrix2 mat) {

    return AddMat2(ZERO_MAT2, MultiplyMat2Scalar(mat, -1.0f));
}

Matrix2 TransposeMat2(Matrix2 mat) {

    Matrix2 tmat = ZERO_MAT2;

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            tmat.matrix[i][j] = mat.matrix[j][i];
        }
    }

    return tmat;
}

Matrix2 InverseMat2(Matrix2 mat) {

    if (IsZeroF(DeterminantMat2(mat))) {
        return ZERO_MAT2;
    }
    return MultiplyMat2Scalar((Matrix2){{{mat.matrix[1][1], -mat.matrix[0][1]}, {-mat.matrix[1][0], mat.matrix[0][0]}}}, 1.0f/DeterminantMat2(mat));
}


Vector2 MultiplyMat2Vect2(Matrix2 mat, Vector2 vect) {

    return (Vector2) {
        mat.matrix[0][0]*vect.x + mat.matrix[0][1]*vect.y,
        mat.matrix[1][0]*vect.x + mat.matrix[1][1]*vect.y
    };
}


float TraceMat2(Matrix2 mat) {

    return mat.matrix[0][0] + mat.matrix[1][1];
}

float DeterminantMat2(Matrix2 mat) {

    return mat.matrix[0][0]*mat.matrix[1][1] - mat.matrix[0][1]*mat.matrix[1][0];
}



void PrintMat2(Matrix2 mat) {

    printf("struct Matrix2: \n");
    for (int i=0; i<2; i++) {
        printf("[");
        for (int j=0; j<2; j++) {
            if (j==1) {
                printf("%f]",mat.matrix[i][j]);
            } else {
                printf("%f, ",mat.matrix[i][j]);
            }
        }
        printf("\n");
    }
}
#include "../../inc/utils/matrix4.h"


const Matrix4 IDENTITY_MAT4 = (Matrix4) {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}};
const Matrix4 ZERO_MAT4 = (Matrix4){{{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}}};
const Matrix4 ONE_MAT4 = (Matrix4){{{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}};


Matrix4 *CreateMat4(float matrix[4][4]) {

    Matrix4 *mat = (Matrix4*)malloc(sizeof(Matrix4));

    if (mat == NULL) {
        fprintf(stderr,"Error allocating memory for struct Matrix.\n");
        return NULL;
    }

    memcpy(mat->matrix, matrix, sizeof(float)*16);

    return mat;
}

void DestroyMat4(Matrix4 *mat) {

    if (mat != NULL) {
        free(mat);
    }
}


Matrix4 AddMat4(Matrix4 mat1, Matrix4 mat2) {

    Matrix4 mat = ZERO_MAT4;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            mat.matrix[i][j] = mat1.matrix[i][j] + mat2.matrix[i][j];
        }
    }

    return mat;
}

Matrix4 MultiplyMat4(Matrix4 mat1, Matrix4 mat2) {

    Matrix4 mat = ZERO_MAT4;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            mat.matrix[i][j] = Sum(3, mat1.matrix[i][0]*mat2.matrix[0][j], mat1.matrix[i][1]*mat2.matrix[1][j], mat1.matrix[i][2]*mat2.matrix[2][j], mat1.matrix[i][3]*mat2.matrix[3][j]);
        }
    }
    
    return mat;
}

Matrix4 MultiplyMat4Scalar(Matrix4 mat, float k) {

    Matrix4 mat_ = ZERO_MAT4;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            mat_.matrix[i][j] = mat.matrix[i][j] * k;
        }
    }
    
    return mat_;
}

Matrix4 AdditiveInverseMat4(Matrix4 mat) {

    return AddMat4(ZERO_MAT4, MultiplyMat4Scalar(mat, -1.0f));
}

Matrix4 TransposeMat4(Matrix4 mat) {

    Matrix4 tmat = ZERO_MAT4;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            tmat.matrix[i][j] = mat.matrix[j][i];
        }
    }

    return tmat;
}

Matrix4 InverseMat4(Matrix4 mat) {

    if (IsZeroF(DeterminantMat4(mat))) {
        return ZERO_MAT4;
    }
    
    float cof11 = DeterminantMat3((Matrix3){{{mat.matrix[1][1], mat.matrix[1][2], mat.matrix[1][3]}, {mat.matrix[2][1], mat.matrix[2][2], mat.matrix[2][3]},{mat.matrix[3][1], mat.matrix[3][2], mat.matrix[3][3]}}});
    float cof12 = -DeterminantMat3((Matrix3){{{mat.matrix[1][0], mat.matrix[1][2], mat.matrix[1][3]}, {mat.matrix[2][0], mat.matrix[2][2], mat.matrix[2][3]},{mat.matrix[3][0], mat.matrix[3][2], mat.matrix[3][3]}}});
    float cof13 = DeterminantMat3((Matrix3){{{mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][3]}, {mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][3]},{mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][3]}}});
    float cof14 = -DeterminantMat3((Matrix3){{{mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][2]}, {mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][2]},{mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][2]}}});

    float cof21 = -DeterminantMat3((Matrix3){{{mat.matrix[0][1], mat.matrix[0][2], mat.matrix[0][3]}, {mat.matrix[2][1], mat.matrix[2][2], mat.matrix[2][3]},{mat.matrix[3][1], mat.matrix[3][2], mat.matrix[3][3]}}});
    float cof22 = DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][2], mat.matrix[0][3]}, {mat.matrix[2][0], mat.matrix[2][2], mat.matrix[2][3]},{mat.matrix[3][0], mat.matrix[3][2], mat.matrix[3][3]}}});
    float cof23 = -DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][1], mat.matrix[0][3]}, {mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][3]},{mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][3]}}});
    float cof24 = DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][1], mat.matrix[0][2]}, {mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][2]},{mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][2]}}});

    float cof31 = DeterminantMat3((Matrix3){{{mat.matrix[0][1], mat.matrix[0][2], mat.matrix[0][3]}, {mat.matrix[1][1], mat.matrix[1][2], mat.matrix[1][3]},{mat.matrix[3][1], mat.matrix[3][2], mat.matrix[3][3]}}});
    float cof32 = -DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][2], mat.matrix[0][3]}, {mat.matrix[1][0], mat.matrix[1][2], mat.matrix[1][3]},{mat.matrix[3][0], mat.matrix[3][2], mat.matrix[3][3]}}});
    float cof33 = DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][1], mat.matrix[0][3]}, {mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][3]},{mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][3]}}});
    float cof34 = -DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][1], mat.matrix[0][2]}, {mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][2]},{mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][2]}}});

    float cof41 = -DeterminantMat3((Matrix3){{{mat.matrix[0][1], mat.matrix[0][2], mat.matrix[0][3]}, {mat.matrix[1][1], mat.matrix[1][2], mat.matrix[1][3]},{mat.matrix[2][1], mat.matrix[2][2], mat.matrix[2][3]}}});
    float cof42 = DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][2], mat.matrix[0][3]}, {mat.matrix[1][0], mat.matrix[1][2], mat.matrix[1][3]},{mat.matrix[2][0], mat.matrix[2][2], mat.matrix[2][3]}}});
    float cof43 = -DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][1], mat.matrix[0][3]}, {mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][3]},{mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][3]}}});
    float cof44 = DeterminantMat3((Matrix3){{{mat.matrix[0][0], mat.matrix[0][1], mat.matrix[0][2]}, {mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][2]},{mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][2]}}});

    return MultiplyMat4Scalar((Matrix4){{{cof11, cof12, cof13, cof14},{cof21, cof22, cof23, cof24},{cof31, cof32, cof33, cof34},{cof41, cof42, cof43, cof44}}}, 1/DeterminantMat4(mat));
}

Matrix4 Mat4FromVect4(Vector4 col1, Vector4 col2, Vector4 col3, Vector4 col4) {

    float *col1Ptr = Vect4ToArray(col1);
    float *col2Ptr = Vect4ToArray(col2);
    float *col3Ptr = Vect4ToArray(col3);
    float *col4Ptr = Vect4ToArray(col4);
    Matrix4 mat = ZERO_MAT4;

    for (int i=0;i<4;i++) {
        mat.matrix[i][0] = *(col1Ptr+i);
        mat.matrix[i][1] = *(col2Ptr+i);
        mat.matrix[i][2] = *(col3Ptr+i);
        mat.matrix[i][3] = *(col4Ptr+i);
    }

    return mat;
}

Matrix4 OrthonormalizeMat4(Matrix4 mat) {

    if (IsOrthogonalMat4(mat)) {
        return mat;
    }

    Vector4 v1 = (Vector4) {mat.matrix[0][0], mat.matrix[1][0], mat.matrix[2][0], mat.matrix[3][0]};
    Vector4 v2 = (Vector4) {mat.matrix[0][1], mat.matrix[1][1], mat.matrix[2][1], mat.matrix[3][1]};
    Vector4 v3 = (Vector4) {mat.matrix[0][2], mat.matrix[1][2], mat.matrix[2][2], mat.matrix[3][2]};
    Vector4 v4 = (Vector4) {mat.matrix[0][3], mat.matrix[1][3], mat.matrix[2][3], mat.matrix[3][3]};
    
    Vector4 u2 = AddVect4(v2, InverseVect4(ProjectVect4(v2, v1)));
    Vector4 u3 = AddVect4(v3, InverseVect4(ProjectVect4(v3, v1)));
    u3 = AddVect4(u3, InverseVect4(ProjectVect4(v3, u2)));
    Vector4 u4 = AddVect4(v4, InverseVect4(ProjectVect4(v2, v1)));
    u4 = AddVect4(u4, InverseVect4(ProjectVect4(v4, u2)));
    u4 = AddVect4(u4, InverseVect4(ProjectVect4(v4, u3)));

    return Mat4FromVect4(NormalizedVect4(v1), NormalizedVect4(u2), NormalizedVect4(u3), NormalizedVect4(u4));
}


Vector4 MultiplyMat4Vect4(Matrix4 mat, Vector4 vect) {

    return (Vector4) {
        mat.matrix[0][0]*vect.x + mat.matrix[0][1]*vect.y + mat.matrix[0][2]*vect.z + mat.matrix[0][3]*vect.w,
        mat.matrix[1][0]*vect.x + mat.matrix[1][1]*vect.y + mat.matrix[1][2]*vect.z + mat.matrix[1][3]*vect.w,
        mat.matrix[2][0]*vect.x + mat.matrix[2][1]*vect.y + mat.matrix[2][2]*vect.z + mat.matrix[2][3]*vect.w,
        mat.matrix[3][0]*vect.x + mat.matrix[3][1]*vect.y + mat.matrix[3][2]*vect.z + mat.matrix[3][3]*vect.w
    };
}


Vector4 *GetMat4Columns(Matrix4 mat) {

    Matrix4 tmat = TransposeMat4(mat);
    static Vector4 arr[4];

    for (int i=0; i<4; i++) {
        arr[i] = ArrayToVect4(tmat.matrix[i]);
    }

    return arr;
}


float TraceMat4(Matrix4 mat) {

    return mat.matrix[0][0] + mat.matrix[1][1] + mat.matrix[2][2] + mat.matrix[3][3];
}

float DeterminantMat4(Matrix4 mat) {

    Matrix3 com1 = (Matrix3){{
        {mat.matrix[1][1], mat.matrix[1][2], mat.matrix[1][3]}, 
        {mat.matrix[2][1], mat.matrix[2][2], mat.matrix[2][3]},
        {mat.matrix[3][1], mat.matrix[3][2], mat.matrix[3][3]}
        }};
    Matrix3 com2 = (Matrix3){{
        {mat.matrix[1][0], mat.matrix[1][2], mat.matrix[1][3]}, 
        {mat.matrix[2][0], mat.matrix[2][2], mat.matrix[2][3]},
        {mat.matrix[3][0], mat.matrix[3][2], mat.matrix[3][3]}
        }};
    Matrix3 com3 = (Matrix3){{
        {mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][3]}, 
        {mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][3]},
        {mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][3]}
        }};
    Matrix3 com4 = (Matrix3){{
        {mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][2]}, 
        {mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][2]},
        {mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][2]}
        }};
    
    return mat.matrix[0][0]*DeterminantMat3(com1) - mat.matrix[0][1]*DeterminantMat3(com2) + mat.matrix[0][2]*DeterminantMat3(com3) - mat.matrix[0][3]*DeterminantMat3(com4);
}


bool IsOrthogonalMat4(Matrix4 mat) {

    float det = DeterminantMat4(mat);
    return IsZeroF(det*det - 1);
}


void PrintMat4(Matrix4 mat) {

    printf("struct Matrix4: \n");
    for (int i=0; i<4; i++) {
        printf("[");
        for (int j=0; j<4; j++) {
            if (j==3) {
                printf("%f]",mat.matrix[i][j]);
            } else {
                printf("%f, ",mat.matrix[i][j]);
            }
        }
        printf("\n");
    }
}
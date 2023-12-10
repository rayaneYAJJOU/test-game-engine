#ifndef MATRIX3_H_
#define MATRIX3_H_

#include "matrix2.h"
#include "vector3.h"

typedef struct Matrix3 {
    float matrix[3][3];
} Matrix3;

extern const Matrix3 IDENTITY_MAT3;
extern const Matrix3 ZERO_MAT3;
extern const Matrix3 ONE_MAT3;

Matrix3 *CreateMat3(float[3][3]);
void DestroyMat3(Matrix3*);

Matrix3 AddMat3(Matrix3, Matrix3);
Matrix3 MultiplyMat3(Matrix3, Matrix3);
Matrix3 MultiplyMat3Scalar(Matrix3, float);
Matrix3 AdditiveInverseMat3(Matrix3);
Matrix3 TransposeMat3(Matrix3);
Matrix3 InverseMat3(Matrix3);
Matrix3 RotationMat3(Vector3, float);
Matrix3 FromEulerAnglesMat3(Vector3, EulerOrder);
Matrix3 OrthonormalizeMat3(Matrix3);
Matrix3 Mat3FromVect3(Vector3, Vector3, Vector3);
Matrix3 RotateMat3(Matrix3, Vector3, float);
Matrix3 ScaleMat3(Matrix3, Vector3);

Vector3 MultiplyMat3Vect3(Matrix3, Vector3);
Vector3 GetEulerAnglesMat3(Matrix3, EulerOrder);

Vector3 *GetMat3Columns(Matrix3);

float TraceMat3(Matrix3);
float DeterminantMat3(Matrix3);
float GetAngleMat3(Matrix3);

bool IsOrthogonalMat3(Matrix3);
bool IsZeroMat3(Matrix3);
bool EqualMat3(Matrix3, Matrix3);

void PrintMat3(Matrix3);

#endif
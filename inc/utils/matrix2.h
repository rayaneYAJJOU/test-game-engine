#ifndef MATRIX2_H_
#define MATRIX2_H_

#include "def.h"
#include "vector2.h"

typedef struct Matrix2 {
    float matrix[2][2];
} Matrix2;

extern const Matrix2 IDENTITY_MAT2;
extern const Matrix2 ZERO_MAT2;
extern const Matrix2 ONE_MAT2;

Matrix2 *CreateMat2(float[2][2]);
void DestroyMat2(Matrix2*);

Matrix2 AddMat2(Matrix2, Matrix2);
Matrix2 MultiplyMat2(Matrix2, Matrix2);
Matrix2 MultiplyMat2Scalar(Matrix2, float);
Matrix2 AdditiveInverseMat2(Matrix2);
Matrix2 TransposeMat2(Matrix2);
Matrix2 InverseMat2(Matrix2);
Matrix2 RotationMat2(float);
Matrix2 Mat2FromVect2(Vector2, Vector2);
Matrix2 OrthonormalizeMat2(Matrix2);
Matrix2 RotateMat2(Matrix2, float);
Matrix2 ScaleMat2(Matrix2, Vector2);

Vector2 MultiplyMat2Vect2(Matrix2, Vector2);

Vector2 *GetMat2Columns(Matrix2);

float TraceMat2(Matrix2);
float DeterminantMat2(Matrix2);
float GetAngleMat2(Matrix2);

bool IsOrthogonalMat2(Matrix2);
bool IsZeroMat2(Matrix2);
bool EqualMat2(Matrix2, Matrix2);

void PrintMat2(Matrix2);

#endif
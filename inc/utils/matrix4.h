#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "matrix3.h"
#include "vector4.h"

typedef struct Matrix4
{
    float matrix[4][4];
} Matrix4;

typedef struct Quaternion Quaternion;


extern const Matrix4 IDENTITY_MAT4;
extern const Matrix4 ZERO_MAT4;
extern const Matrix4 ONE_MAT4;

Matrix4 *CreateMat4(float[4][4]);
void DestroyMat4(Matrix4*);

Matrix4 AddMat4(Matrix4, Matrix4);
Matrix4 MultiplyMat4(Matrix4, Matrix4);
Matrix4 MultiplyMat4Scalar(Matrix4, float);
Matrix4 AdditiveInverseMat4(Matrix4);
Matrix4 TransposeMat4(Matrix4);
Matrix4 InverseMat4(Matrix4);
Matrix4 OrthonormalizeMat4(Matrix4);
Matrix4 Mat4FromVect4(Vector4, Vector4, Vector4, Vector4);

Vector4 MultiplyMat4Vect4(Matrix4, Vector4);

Vector4 *GetMat4Columns(Matrix4);

float TraceMat4(Matrix4);
float DeterminantMat4(Matrix4);

bool IsOrthogonalMat4(Matrix4);
bool IsZeroMat4(Matrix4);
bool EqualMat4(Matrix4, Matrix4);

void PrintMat4(Matrix4);

#endif
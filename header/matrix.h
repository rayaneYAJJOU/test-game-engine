#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "def.h"
#include "vector3.h"

typedef struct Matrix
{
    int size;
    float **mat;
} Matrix;

extern const Matrix IDENTITY_MAT3;
extern const Matrix IDENTITY_MAT4;
extern const Matrix ZERO_MAT3;
extern const Matrix ZERO_MAT4;
extern const Matrix ONE_MAT3;
extern const Matrix ONE_MAT4;

Matrix* CreateMat(int,float**,float*);
void DestroyMat(Matrix*);

Matrix AddMats(Matrix, Matrix);

#endif
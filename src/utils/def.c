#include "../../inc/utils/def.h"


int exitCode = SUCCESS;
bool running = true;


// Famous fast inverse square root algorithm
float q_rsqrt(float number) {
    
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

float DegreesToRadians(float a) {

    return (a*PI)/180;
}

float RadiansToDegrees(float a) {

    return (a*180)/PI;
}

float Maximum(int numArgs, ...) {

    va_list ap;
    va_start(ap,numArgs);
    float max = va_arg(ap, double);
    float temp = max;

    for (int i=1;i<numArgs;i++) {
        temp = va_arg(ap, double);
        if (temp>max) {
            max = temp;
        }
    }

    return max;
}

float Minimum(int numArgs, ...) {
    
    va_list ap;
    va_start(ap,numArgs);
    float min = va_arg(ap, double);
    float temp = min;

    for (int i=1;i<numArgs;i++) {
        temp = va_arg(ap, double);
        if (temp<min) {
            min = temp;
        }
    }

    return min;
}

float Sum(int numArgs, ...) {

    va_list ap;
    va_start(ap,numArgs);
    float sum = va_arg(ap, double);

    for (int i=1;i<numArgs;i++) {
        sum += va_arg(ap, double);
    }

    return sum;
}

float Prod(int numArgs, ...) {

    va_list ap;
    va_start(ap,numArgs);
    float prod = va_arg(ap, double);

    for (int i=1;i<numArgs;i++) {
        prod *= va_arg(ap, double);
    }

    return prod;
}

float Lerp(float x, float y, float t) {
    
    assert(t>=0 && t<=1);
    return (1-t)*x + t*y;
}

float SumArray(int size, float *arr) {

    float sum = 0.0f;

    for (int i=0; i<size; i++) {

        sum += *(arr+i);
    }

    return sum;
}

float *ProductArrays(int size, float *arr1, float *arr2) {

    float *prod = (float*)malloc(sizeof(float)*size);
    
    if (prod == NULL) {
        fprintf(stderr,"Error allocating memory for product of arrays.\n");
        return NULL;
    }

    for (int i=0; i<size; i++) {

        *(prod+i) = (*(arr1+i)) * (*(arr2+i));
    }

    return prod;
}

float *SumArrays(int size, float *arr1, float *arr2) {

    float *sum = (float*)malloc(sizeof(float)*size);

    if (sum == NULL) {
        fprintf(stderr,"Error allocating memory for sum of arrays.\n");
        return NULL;
    }

    for (int i=0; i<size; i++) {

        *(sum+i) = (*(arr1+i)) + (*(arr2+i));
    }

    return sum;
}


bool IsZeroF(float x) {

    return fabs(x) < 10e-6;
}
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

float *ProductArrays(uint32_t size, float *arr1, float *arr2) {

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

float *SumArrays(uint32_t size, float *arr1, float *arr2) {

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

float *GetRootsPol2(float a1, float a0) {

    float delta = a1*a1 - 4*a0;

    float *roots = NULL;

    if (IsZeroF(delta)) {

        roots = (float*)malloc(sizeof(float));
        
        if (roots == NULL) {
            fprintf(stderr,"Error allocating memory for GetRootsPol2.\n");
            return NULL;
        }

        *roots = -a1*0.5f;
    } else if (delta > 0.0f) {

        roots = (float*)malloc(sizeof(float)*2);

        if (roots == NULL) {
            fprintf(stderr,"Error allocating memory for GetRootsPol2.\n");
            return NULL;
        }

        delta = sqrt(delta);
        *roots = 0.5f*(-a1 + delta);
        *(roots+1) = 0.5f*(-a1 - delta);
    }

    return roots;
}

float *GetRootsPol3(float a2, float a1, float a0) {

    float *roots = NULL;

    float oneThird = 0.33333333333333333f;
    float oneNinth = 0.11111111111111111f;
    float oneSixth = 0.16666666666666666f;
    float one27 = 0.037037037037037037f;

    float q = a1*oneThird - a2*a2*oneNinth;
    float r = (a1*a2 - 3*a0)*oneSixth - a2*a2*a2*one27;

    float dec = r*r + q*q*q;

    float A = cbrt(fabs(r) + sqrt(dec));

    float t = A - q*(1/A);
    t = (r >= 0.0f) ? t : -t;

    float z0 = t - a2*oneThird;

    if (dec > 0.0f) {

        roots = (float*)malloc(sizeof(float));

        if (roots == NULL) {
            fprintf(stderr,"Error allocating memory for GetRootsPol2.\n");
            return NULL;
        }

        *roots = z0;
    } else {

        roots = (float*)malloc(sizeof(float)*3);

        if (roots == NULL) {
            fprintf(stderr,"Error allocating memory for GetRootsPol2.\n");
            return NULL;
        }

        float *r2 = GetRootsPol2(z0+a2, z0*(z0+a2) + a1);

        *roots = z0;
        *(roots+1) = *r2;
        *(roots+2) = *(r2+1);

        free(r2);
    }

    return roots;
}

double arcsinex(double x) {

    return asin(fmod(x, 1));
}

double arccosinex(double x) {

    return acos(fmod(x, 1));
}


bool IsZeroF(float x) {

    return fabs(x) < 1e-6;
}

bool IsZeroD(double x) {

    return fabs(x) < 1e-15;
}
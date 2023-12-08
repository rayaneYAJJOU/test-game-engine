#include "../../inc/utils/def.h"


int exitCode = SUCCESS;
bool running = true;

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

float Lerp(float x, float y, float t) {
    
    assert(t>=0 && t<=1);
    return (1-t)*x + t*y;
}
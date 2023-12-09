#ifndef DEF_H_
#define DEF_H_

#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define WIDTH 1080
#define HEIGHT 720
#define PI 3.1415926535897932384626433
#define PHYSICS_PROCESS 240.0f
#define PHYSICS_PROCESS_TIME_MS 1000.0f/PHYSICS_PROCESS
#define FRAMERATE 60
#define MS_PER_FRAME (Uint32) 1000/FRAMERATE

typedef enum EulerOrder {
    EULER_ORDER_XYZ = 0,
    EULER_ORDER_XZY = 1,
    EULER_ORDER_YXZ = 2,
    EULER_ORDER_YZX = 3,
    EULER_ORDER_ZXY = 4,
    EULER_ORDER_ZYX = 5,
} EulerOrder;

typedef enum ExitCode {
    SUCCESS = 0,
    INIT_FAIL = 1,
    WINDOW_FAIL = 2,
    RENDERER_FAIL = 3,
    GAME_FAIL = 4,
    ENTITY_FAIL = 5
} ExitCode;

extern int exitCode;
extern bool running;

float DegreesToRadians(float);
float RadiansToDegrees(float);
float q_rsqrt(float);
float Maximum(int, ...);
float Minimum(int, ...);
float Sum(int, ...);
float Prod(int, ...);
float Lerp(float, float, float);
float SumArray(int, float*);
float *ProductArrays(int, float*, float*);
float *SumArrays(int, float*, float*);

bool IsZeroF(float);

#endif
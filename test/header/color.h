#ifndef COLOR_H_
#define COLOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

#include "def.h"

typedef uint8_t Uint8;

typedef struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

extern Color BLACK;
extern Color BLUE;
extern Color BROWN;
extern Color CYAN;
extern Color GOLD;
extern Color GRAY;
extern Color GREEN;
extern Color LIME;
extern Color MAGENTA;
extern Color ORANGE;
extern Color PURPLE;
extern Color RED;
extern Color WHITE;
extern Color YELLOW;

Color *CreateColorRGBA(Uint8, Uint8, Uint8, Uint8);
void DestroyColor(Color*);

Color LerpColor(Color, Color, float);
Color fromHSV(float, float, float);
Color InverseColor(Color);

#endif
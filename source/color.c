#include "../header/color.h"


Color BLACK = (Color) {0, 0, 0, 255};
Color BLUE = (Color) {0, 0, 255, 255};
Color BROWN = (Color) {165, 42, 42, 255};
Color CYAN = (Color) {0, 255, 255, 255};
Color GOLD = (Color) {255, 215, 0, 255};
Color GRAY = (Color) {128, 128, 128, 255};
Color GREEN = (Color) {0, 255, 0, 255};
Color LIME = (Color) {50, 205, 50, 255};
Color MAGENTA = (Color) {255, 0, 255, 255};
Color ORANGE = (Color) {255, 165, 0, 255};
Color PURPLE = (Color) {128, 0, 128, 255};
Color RED = (Color) {255, 0, 0, 255};
Color WHITE = (Color) {255, 255, 255, 255};
Color YELLOW = (Color) {255, 255, 0, 255};


Color *CreateColorRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {

    Color *color = malloc(sizeof(Uint8)*4);

    if (color == NULL) {
        fprintf(stderr,"Error allocating memory for struct Color.\n");
        return NULL;
    }

    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;

    return color;
}

void DestroyColor(Color *color) {

    if (color != NULL) {
        free(color);
    }
}



Color LerpColor(Color c1, Color c2, float t) {

    return (Color) {(Uint8)Lerp(c1.r, c2.r, t), (Uint8)Lerp(c1.g, c2.g, t), (Uint8)Lerp(c1.b, c2.b, t), (Uint8)Lerp(c1.a, c2.a, t)};
}

Color fromHSV(float h, float s, float v) {

    float chroma = s * v;
    float hprime = h/60;
    float m = v - chroma;
    float x = chroma * (1 - fabs(fmod(hprime,2.0) - 1));

    float r1 = ((hprime>=0 && hprime<2) || (hprime>=4 && hprime<6)) ? (((hprime>=0 && hprime<1) || (hprime>=5 && hprime<6)) ? chroma : x) : 0;
    float g1 = ((hprime>=0 && hprime<4)) ? (((hprime>=0 && hprime<1) || (hprime>=3 && hprime<4)) ? x : chroma) : 0;
    float b1 = ((hprime>=2 && hprime<6)) ? (((hprime>=2 && hprime<3) || (hprime>=5 && hprime<6)) ? x : chroma) : 0;

    r1 += m;
    g1 += m;
    b1 += m;

    return (Color) {(Uint8)r1*255, (Uint8)g1*255, (Uint8)b1*255, 255};
}

Color InverseColor(Color c) {
    
    return (Color) {255-c.r, 255-c.g, 255-c.b, c.a};
}
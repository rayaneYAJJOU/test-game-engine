#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <stdio.h>

#include "def.h"
#include "color.h"
#include "vector3.h"

extern SDL_Renderer *renderer;

void *InitRenderer(SDL_Window*, int, Uint32);
void CloseRenderer();
void Render();

#endif
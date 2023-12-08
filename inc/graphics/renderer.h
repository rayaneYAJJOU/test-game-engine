#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <stdio.h>

#include "../game.h"
#include "../physics/particle.h"
#include "../utils/color.h"
#include "../utils/def.h"
#include "../utils/vector3.h"

extern SDL_Renderer *renderer;
typedef struct Game Game;

void InitRenderer(SDL_Window*, int, Uint32);
void CloseRenderer();
void Render(Game*);

#endif
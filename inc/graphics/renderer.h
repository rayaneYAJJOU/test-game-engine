#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <stdio.h>

#include "../game.h"
#include "../utils/def.h"

extern SDL_Renderer *renderer;
typedef struct Game Game;

void InitRenderer(SDL_Window*, int, Uint32);
void CloseRenderer();
void Render(Game*);

#endif
#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>

#include "../utils/def.h"

extern SDL_Window *window;

void InitWindow(const char*, int, int, int, int, Uint32, Uint32);
void CloseWindow();

#endif
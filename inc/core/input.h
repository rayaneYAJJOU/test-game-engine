#ifndef INPUT_H_
#define INPUT_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "../game.h"
#include "../utils/def.h"

extern bool holdingMB1;

typedef struct Game Game;

void HandleInput(Game*);

#endif
#ifndef INPUT_H_
#define INPUT_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "def.h"
#include "handler.h"
#include "particle.h"
#include "vector3.h"
#include "color.h"

extern bool holdingMB1;

void HandleInput(Game*);

#endif
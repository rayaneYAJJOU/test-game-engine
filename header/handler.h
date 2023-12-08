#ifndef HANDLER_H_
#define HANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "def.h"
#include "renderer.h"
#include "window.h"
#include "particle.h"

typedef struct Game {
    Particle **particleArr;
    Uint32 numParticles;
    SDL_Renderer *renderer;
    SDL_Window *window;
} Game;

Game *InitGame(Particle**, Uint32, SDL_Renderer*, SDL_Window*);
void UpdateGame(Game*, float);
void RenderGame(Game*);
void InputGame(Game*, SDL_Event);
void CloseGame(Game*);
void AddParticle(Game*, Particle*);
void RemoveParticle(Game*, Particle*);
void CheckParticlesBound(Game*);

#endif
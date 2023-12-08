#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "def.h"
#include "timer.h"
#include "vector3.h"
#include "color.h"

typedef struct Particle {
    float mass;
    Vector3 position;
    Vector3 velocity;
    Color color;
} Particle;

Particle *CreateParticle(float, Vector3, Color);
void UpdateParticle(Particle*, float);
void RenderParticle(SDL_Renderer*, Particle*);
void InputParticle(SDL_Event, Particle*);
void DestroyParticle(Particle*);

#endif
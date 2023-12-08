#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "../core/timer.h"
#include "../utils/def.h"
#include "../utils/color.h"
#include "../utils/vector3.h"

typedef struct Particle {
    float mass;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    Color color;
} Particle;

Particle *CreateParticle(float, Vector3, Color);
void UpdateParticle(Particle*, float);
void RenderParticle(SDL_Renderer*, Particle*);
void InputParticle(SDL_Event, Particle*);
void DestroyParticle(Particle*);
void ApplyForce(Particle*, Vector3, float);

#endif
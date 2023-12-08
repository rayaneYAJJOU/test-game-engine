#include "../../inc/physics/particle.h"


Particle *CreateParticle(float mass, Vector3 pos, Color c) {

    Particle *p = (Particle*)malloc(sizeof(Particle));

    if (p == NULL) {
        fprintf(stderr,"Error allocating memory for struct Particle.\n");
        return NULL;
    }

    p->mass = mass;
    p->position = pos;
    p->velocity = ZERO_VECTOR;
    p->acceleration = ZERO_VECTOR;
    p->color = c;

    return p;
}

void UpdateParticle(Particle *p, float delta) {

    p->position.x += p->velocity.x*delta + 0.5f*p->acceleration.x*delta*delta;
    p->position.y += p->velocity.y*delta + 0.5f*p->acceleration.y*delta*delta;
    p->position.z += p->velocity.z*delta + 0.5f*p->acceleration.z*delta*delta;
}

void RenderParticle(SDL_Renderer *renderer, Particle *p) {

    SDL_SetRenderDrawColor(renderer, p->color.r, p->color.g, p->color.b, p->color.a);
    SDL_RenderDrawPoint(renderer, p->position.x, p->position.y);
    SDL_RenderDrawPoint(renderer, p->position.x+1, p->position.y+1);
    SDL_RenderDrawPoint(renderer, p->position.x+1, p->position.y);
    SDL_RenderDrawPoint(renderer, p->position.x, p->position.y+1);
}

void InputParticle(SDL_Event e, Particle *p) {

    return;
}

void DestroyParticle(Particle *p) {

    if (p != NULL) {
        free(p);
    }
}

void ApplyForce(Particle *p, Vector3 force, float delta) {

    p->acceleration.x = (1/p->mass)*force.x;
    p->acceleration.y = (1/p->mass)*force.y;
    p->acceleration.z = (1/p->mass)*force.z;

    p->velocity.x += p->acceleration.x*delta;
    p->velocity.y += p->acceleration.y*delta;
    p->velocity.z += p->acceleration.z*delta;
}
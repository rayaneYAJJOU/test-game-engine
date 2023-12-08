#include "../header/handler.h"


Game *InitGame(Particle **particleArr, Uint32 particleNum, SDL_Renderer *renderer, SDL_Window *window) {

    Game *game = (Game*)malloc(sizeof(Particle**) + sizeof(Uint32) + sizeof(SDL_Renderer*) + sizeof(SDL_Window*));

    if (game == NULL) {
        fprintf(stderr,"Error initializing game: memory was not properly allocated.\n");
        exitCode = GAME_FAIL;
        return NULL;
    }

    game->particleArr = particleArr;
    game->numParticles = particleNum;
    game->renderer = renderer;
    game->window = window;

    return game;
}

void UpdateGame(Game *game, float delta) {

    if (game == NULL) {
        fprintf(stderr,"Error updating game: game is not properly initialized.\n");
        exitCode = GAME_FAIL;
        return;
    }

    for (int i=0; i<game->numParticles; i++) {
        ApplyForce(*(game->particleArr+i), (Vector3){0.0f, 50.0f*(*(game->particleArr+i))->mass, 0.0f}, delta);
        UpdateParticle(*(game->particleArr+i), delta);
    }
}

void RenderGame(Game *game) {

    if (game == NULL) {
        fprintf(stderr,"Error rendering game: game is not properly initialized.\n");
        exitCode = GAME_FAIL;
        return;
    }

    for (int i=0; i<game->numParticles; i++) {
        RenderParticle(game->renderer, *(game->particleArr+i));
    }
}

void InputGame(Game *game, SDL_Event e) {

    if (game == NULL) {
        fprintf(stderr,"Error handling input for game: game is not properly initialized.\n");
        exitCode = GAME_FAIL;
        return;
    }

    for (int i=0; i<game->numParticles; i++) {
        InputParticle(e, *(game->particleArr+i));
    }
}

void CloseGame(Game *game) {

    if (game == NULL) {
        fprintf(stderr,"Error closing game: game is not properly initialized.\n");
        exitCode = GAME_FAIL;
        return;
    }

    if (game->renderer==NULL) {
        fprintf(stderr,"Error closing game: renderer is not properly initialized.\n");
        exitCode = RENDERER_FAIL;
        return;
    }

    if (game->window==NULL) {
        fprintf(stderr,"Error closing game: window is not properly initialized.\n");
        exitCode = WINDOW_FAIL;
        return;
    }

    if (game->particleArr==NULL) {
        fprintf(stderr,"Error closing game: entity collection is not properly initialized.\n");
        exitCode = ENTITY_FAIL;
        return;
    }

    for (int i=0; i<game->numParticles; i++) {
        if (*(game->particleArr+i) == NULL) {
            fprintf(stderr,"Error closing game: entity is not properly initialized.\n");
            exitCode = ENTITY_FAIL;
            break;
        }
        DestroyParticle(*(game->particleArr+i));
    }

    free(game->particleArr);
    free(game);
    CloseRenderer();
    CloseWindow();
    SDL_Quit();
}

void AddParticle(Game *game, Particle *p) {

    //Particle **pArr = (Particle**)realloc(game->particleArr, sizeof(Particle*)*(game->numParticles++));
    //Particle **pArr = (Particle**)malloc(sizeof(Particle*)*(game->numParticles++));
    game->particleArr = (Particle**)realloc(game->particleArr, sizeof(Particle*)*(++game->numParticles));

    if (game->particleArr == NULL) {
        fprintf(stderr,"Error reallocating memory for new particle.\n");
        exitCode = ENTITY_FAIL;
        return;
    }

    /*
    for (int i=0;i<game->numParticles-1;i++) {
        *(pArr+i) = *(game->particleArr+i);
        DestroyParticle(*(game->particleArr+i));
    }

    free(game->particleArr);

    if (game->particleArr != NULL) {
        fprintf(stderr,"Error freeing memory for particle array.\n");
        exitCode = ENTITY_FAIL;
        return;
    }
    */

    *(game->particleArr + game->numParticles-1) = p;
}

void RemoveParticle(Game *game, Particle *p) {

    int slot = -1;
    for (int i = 0; i < game->numParticles; i++) {
        if (*(game->particleArr + i) == p) {
            slot = i;
            break;
        }
    }

    if (slot != -1) {
        DestroyParticle(p);
        for (int i = slot; i < game->numParticles - 1; i++) {
            *(game->particleArr + i) = *(game->particleArr + i + 1);
        }
    }
    
    Particle **pArr = (Particle**)realloc(game->particleArr, sizeof(Particle*)*(game->numParticles--));

    if (pArr == NULL) {
        fprintf(stderr,"Error reallocating memory for new particle.\n");
        exitCode = ENTITY_FAIL;
        return;
    }

    game->particleArr = pArr;
}

void CheckParticlesBound(Game *game) {

    for (int i=0; i<game->numParticles; i++) {
        if ((*(game->particleArr+i))->position.x > WIDTH || (*(game->particleArr+i))->position.y > HEIGHT) {
            RemoveParticle(game, *(game->particleArr+i));
        }
    }
}
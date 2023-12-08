#include "../../inc/core/input.h"


bool holdingMB1 = false;

void HandleInput(Game *game) {
    
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        InputGame(game, e);
        switch (e.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            holdingMB1 = (e.button.button==SDL_BUTTON_LEFT) ? true : holdingMB1;
            break;
        case SDL_MOUSEBUTTONUP:
            holdingMB1 = (e.button.button==SDL_BUTTON_LEFT) ? false: holdingMB1;
            break;
        }
        if (holdingMB1) {
            AddParticle(game, CreateParticle(1.0f, (Vector3){e.button.x, e.button.y, 0.0f}, RED));
        }
    }
}
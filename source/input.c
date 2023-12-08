#include "../header/input.h"


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
            AddParticle(game, CreateParticle(1, (Vector3){e.button.x, e.button.y, 0.0f}, RED));
            break;
        }
    }
}
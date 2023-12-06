#include "../header/input.h"


void HandleInput() {
    
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        }
    }
}
#include "../../inc/graphics/renderer.h"


SDL_Renderer *renderer;

void InitRenderer(SDL_Window *window, int index, Uint32 flags) {

    renderer = SDL_CreateRenderer(window, index, flags);

    if (renderer == NULL) {
        fprintf(stderr,"Error initializing renderer: %s\n",SDL_GetError());
        exitCode = RENDERER_FAIL;
        SDL_DestroyWindow(window);
        return;
    }
}

void CloseRenderer() {

    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
}

void Render(Game *game) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    RenderGame(game);

    SDL_RenderPresent(renderer);
}
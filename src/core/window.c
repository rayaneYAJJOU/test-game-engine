#include "../../inc/core/window.h"


SDL_Window *window;

void InitWindow(const char *title, int x, int y, int w, int h, Uint32 flagsWin, Uint32 flagsInit) {

    if (SDL_Init(flagsInit) < 0) {
        fprintf(stderr,"Error initializing SDL2 library: %s\n",SDL_GetError());
        exitCode = INIT_FAIL;
        return;
    }

    window = SDL_CreateWindow(title, x, y, w, h, flagsWin);

    if (window == NULL) {
        fprintf(stderr,"Error initializing SLD2 window: %s\n",SDL_GetError());
        exitCode = WINDOW_FAIL;
        return;
    }
}

void CloseWindow() {

    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
}
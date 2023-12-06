#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "header/def.h"
#include "header/input.h"
#include "header/renderer.h"
#include "header/timer.h"
#include "header/window.h"

int main(int argc, char *argv[]) {

    InitWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL, SDL_INIT_EVERYTHING);
    InitRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    const Uint32 MS_PER_FRAME = (Uint32) 1000/FRAMERATE;

    Uint32 frameTime;
    Uint32 frameStart;

    while (running) {

        if (exitCode != 0) {
            break;
        }

        frameStart = SDL_GetTicks();

        HandleInput();

        UpdateDeltaTime();

        Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - frameTime);
        }
    }

    CloseRenderer();
    CloseWindow();
    SDL_Quit();

    return exitCode;
}
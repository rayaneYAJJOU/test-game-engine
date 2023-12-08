#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "header/def.h"
#include "header/handler.h"
#include "header/input.h"
#include "header/renderer.h"
#include "header/timer.h"
#include "header/window.h"
#include "header/particle.h"
#include "header/color.h"

int main(int argc, char *argv[]) {

    InitWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL, SDL_INIT_EVERYTHING);
    InitRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Uint32 frameTime;
    Uint32 frameStart;

    Game *game = InitGame(NULL, 0, renderer, window);

    while (running) {

        if (exitCode != 0) {
            break;
        }

        frameStart = SDL_GetTicks();

        HandleInput(game);

        UpdateDeltaTime();

        CheckParticlesBound(game);

        Render(game);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - frameTime);
        }
    }

    CloseGame(game);

    return exitCode;
}
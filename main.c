#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "inc/game.h"
#include "inc/core/input.h"
#include "inc/core/timer.h"
#include "inc/core/window.h"
#include "inc/graphics/renderer.h"
#include "inc/physics/particle.h"
#include "inc/utils/def.h"
#include "inc/utils/color.h"

int main(int argc, char *argv[]) {

    // Initialization
    InitWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL, SDL_INIT_EVERYTHING);
    InitRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Game *game = InitGame(NULL, 0, renderer, window);

    // Main loop of the game engine
    MainLoop(game);

    // Close game once loop is complete
    CloseGame(game);

    return exitCode;
}
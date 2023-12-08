#include "../../inc/core/timer.h"


static float delta;

void UpdateDeltaTime() {

    static Uint32 prevTime = 0;
    Uint32 currentTime = SDL_GetTicks();
    delta = (currentTime-prevTime)/1000.0f;
    prevTime = currentTime;
}

float GetDeltaTime() {
    return delta;
}
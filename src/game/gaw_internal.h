#pragma once

#include "gaw_config.h"
#include "gaw_framework.h"

#include <stdint.h>

typedef struct Game_GlobalState
{
    struct SDL_Window* window;
    struct GraphicsState* graphics;
    struct GameStateMachine* state;
    uint64_t frameTime;
    bool shouldQuit;
} Game_GlobalState;

extern Game_GlobalState g_GameState;

Game_GlobalState* Game_GetGlobalState(void);
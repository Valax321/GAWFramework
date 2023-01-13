#include "gaw_internal.h"
#include "gamestate/game_state_machine.h"

#include <SDL.h>
#include <stdio.h>

const static double g_FrameRate = 1 / 60.0;
const static uint32_t g_DisabledSDLModules = SDL_INIT_HAPTIC;
const static int g_GameWidth = 800;
const static int g_GameHeight = 600;

#if defined(GAME_BUILD_FOR_DESKTOP)
const static uint32_t g_WindowFlags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;
#else
const static uint32_t g_WindowFlags = SDL_WINDOW_ALLOW_HIGHDPI;
#endif

Game_GlobalState g_GameState;

void Game_PollEvents(void);
void Game_Update(void);
void Game_Tick(void);
void Game_Render(void);

void Game_ToggleFullscreen(SDL_Event* ev);

bool Game_Init(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING & ~(g_DisabledSDLModules)) != 0)
    {
        printf("Failed to init SDL: %s\n", SDL_GetError());
        return false;
    }

    g_GameState.window = SDL_CreateWindow(GAME_DISPLAY_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_GameWidth, g_GameHeight, g_WindowFlags);
    if (g_GameState.window == NULL)
    {
        char msg[512];
        SDL_snprintf(msg, sizeof(msg), "Failed to create window: %s", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", msg, g_GameState.window);
        printf("%s\n", msg);
        return false;
    }

    g_GameState.renderer = SDL_CreateRenderer(g_GameState.window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (g_GameState.renderer == NULL)
    {
        char msg[512];
        SDL_snprintf(msg, sizeof(msg), "Failed to create renderer: %s", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", msg, g_GameState.window);
        printf("%s\n", msg);
        return false;
    }

    g_GameState.state = GameStateMachine_Create();

    // Ensure we don't do a ton of updates at first to catch up
    g_GameState.frameTime = SDL_GetPerformanceCounter();

    printf("Initialization completed successfully\n");

    return true;
}

void Game_Quit(void)
{
    printf("Beginning shutdown...\n");
    if (g_GameState.state)
    {
        GameStateMachine_Destroy(g_GameState.state);
        g_GameState.state = NULL;
    }

    if (g_GameState.renderer)
    {
        SDL_DestroyRenderer(g_GameState.renderer);
        g_GameState.renderer = NULL;
    }

    if (g_GameState.window)
    {
        SDL_DestroyWindow(g_GameState.window);
        g_GameState.window = NULL;
    }

    SDL_Quit();
}

void Game_Frame(void)
{
    Game_PollEvents();
    Game_Update();
    Game_Render();
}

void Game_PollEvents(void)
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        Game_ToggleFullscreen(&ev);
        switch (ev.type)
        {
            case SDL_QUIT:
            g_GameState.shouldQuit = true;
            break;
        }
    }
}

void Game_Update(void)
{
    static double accum;
    int tickCount = 0;

    uint64_t curTime = SDL_GetPerformanceCounter();
    uint64_t timeDiff = curTime - g_GameState.frameTime;

    g_GameState.frameTime = curTime;
    double deltaSeconds = timeDiff / (double)SDL_GetPerformanceFrequency();
    accum += deltaSeconds;
    while (accum >= g_FrameRate)
    {
        tickCount++;
        Game_Tick();
        accum -= g_FrameRate;
        if (tickCount > 4)
        {
            #if defined(_DEBUG)
            printf("Warning! Cannot keep up with tickrate! Expect slowdown!\n");
            #endif
            accum = 0;
        }
    }
}

void Game_Tick(void)
{
    if (g_GameState.state)
    {
        GameStateMachine_UpdateQueuedStates(g_GameState.state);
        GameStateMachine_CallTick(g_GameState.state);
    }
}

void Game_Render(void)
{
    /*
    TODO: on desktop we need an intermediate backbuffer that's always 800x600 since the window is resizable.
    Maybe even on web if we make the canvas resizable.
    */

    SDL_SetRenderDrawColor(g_GameState.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(g_GameState.renderer);
    SDL_SetRenderDrawColor(g_GameState.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    {
        if (g_GameState.state)
            GameStateMachine_CallFrame(g_GameState.state);
    }
    SDL_RenderPresent(g_GameState.renderer);
}

void Game_ToggleFullscreen(SDL_Event* ev)
{
    if (ev->type == SDL_KEYDOWN)
    {
        if (ev->key.keysym.scancode == SDL_SCANCODE_F11)
        {
            bool isFullscreen = SDL_GetWindowFlags(g_GameState.window) & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP);
            SDL_SetWindowFullscreen(g_GameState.window, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
            printf("%s fullscreen\n", isFullscreen ? "Disabled" : "Enabled");
        }
    }
}

bool Game_ShouldQuit(void)
{
    return g_GameState.shouldQuit;
}
#include "menu_state.h"
#include "gaw_internal.h"

#include "rlgl.h"

#include <SDL.h>

typedef struct MenuState
{
    bool unused;
} MenuState;

void* Menu_Init(void* _unused)
{
    MenuState* ctx = SDL_malloc(sizeof(MenuState*));
    *ctx = (MenuState){0};

    return ctx;
}

void Menu_Exit(void* ctx)
{
    if (ctx)
        SDL_free(ctx);
}

void Menu_Tick(void* ctx)
{

}

void Menu_Frame(void* ctx)
{
    rlClearColor(255, 0, 0, 255);
    rlClearScreenBuffers();
}

const GameState g_MenuState = {
    "Menu",
    &Menu_Init,
    &Menu_Exit,
    &Menu_Tick,
    &Menu_Frame
};
#include "gaw_framework.h"

#include <emscripten.h>

void Game_Web_Update_Handler(void);

int main()
{
    if (!Game_Init(0, 0))
        return -1;

    // NOTE: nothing after this function will ever be called!
    emscripten_set_main_loop(&Game_Web_Update_Handler, -1, true);
}

void Game_Web_Update_Handler(void)
{
    Game_Frame();
    if (Game_ShouldQuit())
    {
        Game_Quit();
        emscripten_cancel_main_loop();
    }
}
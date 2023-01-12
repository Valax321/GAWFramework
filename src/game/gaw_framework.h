#pragma once

#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

bool Game_Init(int argc, char* argv[]);
void Game_Quit(void);
void Game_Frame(void);
bool Game_ShouldQuit(void);

#if defined(__cplusplus)
}
#endif
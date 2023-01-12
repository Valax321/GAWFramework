#include "gaw_framework.h"

#include <SDL_main.h>
#include <stdio.h>

#if defined(_WIN32) && defined(_DEBUG)
#define LOG_TO_WINDBG

#define UNICODE
#include <Windows.h>

void OpenWindowsConsole(void)
{
    if (!AllocConsole())
        return;

    SetConsoleTitle(L"Debug Window");
    EnableMenuItem(GetSystemMenu(GetConsoleWindow(), false), SC_CLOSE, MF_GRAYED);
    DrawMenuBar(GetConsoleWindow());

    CONSOLE_SCREEN_BUFFER_INFO conInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
    conInfo.dwSize.Y = 5000;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);

    // Why is almost every online example of doing this way more fucked up, this is way more simple lol
    FILE* fp = freopen("CONOUT$", "w", stdout);
    fp = freopen("CONIN$", "r", stdin);
    fp = freopen("CONOUT$", "w", stderr);
}

#endif

int main(int argc, char* argv[])
{
    #if defined(LOG_TO_WINDBG)
    OpenWindowsConsole();
    #endif

    if (!Game_Init(argc, argv))
        return -1;

    while (!Game_ShouldQuit())
    {
        Game_Frame();
    }

    Game_Quit();
    return 0;
}
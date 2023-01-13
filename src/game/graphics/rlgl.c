#include <SDL.h>

#include <stdarg.h>
#include <stdio.h>

void Game_GLPrintf(const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    vprintf(msg, ap);
    va_end(ap);

    printf("\n");
}

#define RL_MALLOC(sz) SDL_malloc(sz)
#define RL_CALLOC(n,sz) SDL_calloc(n, sz)
#define RL_REALLOC(n,sz) SDL_realloc(n, sz)
#define RL_FREE(p) SDL_free(p)

#define TRACELOG(level, ...) Game_GLPrintf(__VA_ARGS__)
#define TRACELOGD(...) Game_GLPrintf(__VA_ARGS__)

#if defined(__EMSCRIPTEN__)
#define GRAPHICS_API_OPENGL_ES2
#else
#define GRAPHICS_API_OPENGL_33
#endif

#define RLGL_IMPLEMENTATION
#include "rlgl.h"
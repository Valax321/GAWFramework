#include "stream_rwops.h"
#include "stream.h"

#include <SDL.h>

void* Stream_RWops_OpenRead(const char* path)
{
    return SDL_RWFromFile(path, "rb");
}

void Stream_RWops_Close(void* handle)
{
    SDL_RWclose(handle);
}

void Stream_RWops_Read(void* handle, void* dest, size_t size, size_t count)
{
    SDL_RWread(handle, dest, size, count);
}

void Stream_RWops_Seek(void* handle, uint32_t seekMode, ptrdiff_t count)
{
    int whence;
    switch (seekMode)
    {
    case STREAM_SEEK_SET:
        whence = RW_SEEK_SET;
        break;
    case STREAM_SEEK_CURRENT:
        whence = RW_SEEK_CUR;
        break;
    case STREAM_SEEK_END:
        whence = RW_SEEK_END;
        break;
    }

    SDL_RWseek(handle, count, whence);
}
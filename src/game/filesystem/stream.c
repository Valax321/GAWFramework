#include "stream.h"
#include "gaw_internal.h"

#include "stream_rwops.h"

typedef void (*Stream_ReadFunc)(void* handle, void* dest, size_t size, size_t count);
typedef void (*Stream_SeekFunc)(void* handle, uint32_t seekMode, ptrdiff_t distance);
typedef void (*Stream_Close)(void* handle);

typedef struct Stream
{
    void* handle;
    Stream_ReadFunc read;
    Stream_SeekFunc seek;
    Stream_Close close;

    uint32_t mode;
} Stream;

Stream* Stream_OpenFileRead(const char* path)
{
    Stream* stream = SDL_malloc(sizeof(Stream));
    stream->handle = Stream_RWops_OpenRead(path);
    stream->mode = STREAM_MODE_READ;
    stream->read = &Stream_RWops_Read;
    stream->seek = &Stream_RWops_Seek;
    stream->close = &Stream_RWops_Close;
    return stream;
}

void Stream_Destroy(Stream* stream)
{
    if (!stream)
        return;

    stream->close(stream->handle);
}

void Stream_Read(Stream* stream, void* dest, size_t size, size_t count)
{
    if (!stream)
        return;

    stream->read(stream->handle, dest, size, count);
}

void Stream_Seek(Stream* stream, uint32_t seekMode, ptrdiff_t distance)
{
    if (!stream)
        return;

    stream->seek(stream->handle, seekMode, distance);
}
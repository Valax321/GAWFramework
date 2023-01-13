#pragma once

#include <stddef.h>
#include <stdint.h>

enum
{
    STREAM_SEEK_SET,
    STREAM_SEEK_CURRENT,
    STREAM_SEEK_END
};

enum
{
    STREAM_MODE_READ = 1 << 0,
    STREAM_MODE_WRITE = 1 << 1
};

typedef struct Stream Stream;

Stream* Stream_OpenFileRead(const char* path);
void Stream_Destroy(Stream* stream);

void Stream_Read(Stream* stream, void* dest, size_t size, size_t count);
void Stream_Seek(Stream* stream, uint32_t seekMode, ptrdiff_t distance);
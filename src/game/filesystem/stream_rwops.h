#pragma once

#include <stddef.h>
#include <stdint.h>

void* Stream_RWops_OpenRead(const char* path);
void Stream_RWops_Close(void* handle);

void Stream_RWops_Read(void* handle, void* dest, size_t size, size_t count);
void Stream_RWops_Seek(void* handle, uint32_t seekMode, ptrdiff_t count);
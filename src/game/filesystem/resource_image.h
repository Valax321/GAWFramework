#pragma once

#include <stdint.h>

#define ImageResource_ID (('I' << 24) | ('M' << 16) | ('G' << 8) | (' '))

enum
{
    IMG_FMT_RGB,
    IMG_FMT_RGBA,
    IMG_FMT_MAX
};

typedef struct ImageResource
{
    struct SDL_Texture* texture;
    uint32_t width;
    uint32_t height;
    uint8_t format;
} ImageResource;

ImageResource* ImageResource_Read(struct Stream* stream);
void ImageResource_Destroy(ImageResource* image);
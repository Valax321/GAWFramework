#pragma once

#include <stdint.h>

typedef struct FileContainer_Header
{
    uint32_t fileCount; // Number of file entries in the container
    uint32_t entryStart; // Position within the file where the entries begin
} FileContainer_Header;

typedef struct FileContainer_Entry
{
    uint64_t fileNameHash; // Hash of the relative path of this asset.
    uint32_t type; // RIFF-style id for what type of file this is
    uint32_t offset; // Position within the container where the file starts
    uint32_t size; // On disk size of the file
} FileContainer_Entry;

typedef struct FileContainer
{
    FileContainer_Header header;
    FileContainer_Entry* files;
    struct Resource* resources;
} FileContainer;
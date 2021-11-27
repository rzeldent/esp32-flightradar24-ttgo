#pragma once

#include <memory>

// Data is stored as RLE (Run Length Encoding)
typedef struct
{
    const unsigned short *data;
    unsigned short width;
    unsigned short height;
} image_t;

extern std::unique_ptr<image_t> rle_decode(const image_t* rle_image);
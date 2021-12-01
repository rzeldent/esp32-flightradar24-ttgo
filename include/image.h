#pragma once

#include <memory>

// Data is stored as RLE (Run Length Encoding)
typedef struct
{
    const unsigned char *data;
    unsigned short width;
    unsigned short height;
} image_data_t;

typedef struct image
{
    const unsigned short *data;
    unsigned short width;
    unsigned short height;

    ~image()
    {
        delete[] data;
    }
} image_t;

extern std::unique_ptr<image_t> rle_decode(const image_data_t *rle_image);
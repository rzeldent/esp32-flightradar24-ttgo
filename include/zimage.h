#pragma once

#include <memory>
#include <vector>

// Data is stored as RLE (Run Length Encoding)
typedef struct
{
    const unsigned char *compressed_data;
    const unsigned int compressed_size;
    const unsigned short width;
    const unsigned short height;
} z_image_data_t;

extern unsigned short* z_image_decode(const z_image_data_t *z_image);

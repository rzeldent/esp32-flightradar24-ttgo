#pragma once

#include <miniz.h>

// Data is stored as GZIP compressed data.
typedef struct
{
    const unsigned char *compressed_data;
    const mz_ulong compressed_size;
    const unsigned short width;
    const unsigned short height;
} z_image_data_t;

inline unsigned short* z_image_decode(const z_image_data_t *z_image_data)
{
    auto image = new unsigned short[z_image_data->width * z_image_data->height];
    mz_ulong uncompressed_len = z_image_data->width * z_image_data->height * sizeof(unsigned short);
    auto status = uncompress((unsigned char*)image, &uncompressed_len, z_image_data->compressed_data, z_image_data->compressed_size);
    return image;
}
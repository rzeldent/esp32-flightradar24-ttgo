#pragma once

#include <stdint.h>

typedef struct
{
    const uint16_t *data;
    uint16_t width;
    uint16_t height;
} image_t;

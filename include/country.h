#pragma once

#include <timage.h>

typedef struct country
{
    const char *iso3166;
    const char *name;
    const tImage *flag;
} country_t;

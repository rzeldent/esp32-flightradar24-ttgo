#pragma once

#include <country.h>

typedef struct airport
{
    const char iata_airport[3];
    const char *name;
    const char *city;
    const char *region;
    const country_code_t country;
    const float latitude;
    const float longitude;
    const int16_t elevation_ft;
} airport_t;

extern const airport_t *lookup_airport(const char* iata_airport);
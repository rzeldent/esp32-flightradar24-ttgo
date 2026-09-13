#pragma once

#include <stddef.h>

#include <country.h>

typedef struct airport
{
    const char iata_airport[3];
    const char *name;
    const char *city;
    const char *region;
    const country_code_t country;
    const int32_t latitude;      // scaled by 1,000,000 (e.g., 40.7128 * 1000000 = 40712800)
    const int32_t longitude;     // scaled by 1,000,000 (e.g., -74.0060 * 1000000 = -74006000)
    const int16_t elevation_ft;
} airport_t;

// All airports, sorted on the IATA code
extern const airport_t airports[];
extern const size_t airport_count;
extern const airport_t *lookup_airport(const char* iata_airport);
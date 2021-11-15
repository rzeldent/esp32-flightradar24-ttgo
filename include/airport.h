#pragma once

#include <country.h>

typedef struct airport
{
    const char *iata_airport;
    const char *name;
    const char *city;
    const char *region;
    const country_t *country;
    double latitude;
    double longitude;
    int elevation_ft;
} airport_t;

extern const airport_t *lookupAirport(const char* iata_airport);
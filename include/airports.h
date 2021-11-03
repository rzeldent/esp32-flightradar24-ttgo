#pragma once

#include <Arduino.h>
#include <timage.h>

typedef struct airport
{
    const char *iata_airport;
    const char *name;
    const char *city;
    const char *country;
    double lon;
    double lat;
    const tImage *flag;
} airport_t;

extern const airport_t *lookupAirport(const char* iata_airport);
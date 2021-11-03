#pragma once

#include <Arduino.h>
#include <timage.h>

typedef struct airline
{
    const char *iata_airline;
    const char *callsign;
    const char *name;
    const char *country;
    const tImage *logo;
} airline_t;

extern const airline_t *lookupAirline(const char *iata_code);
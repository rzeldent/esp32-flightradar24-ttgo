#pragma once

#include <country.h>

typedef struct airline
{
    const char *iata_airline;
    const char *callsign;
    const char *name;
    const country_t *country;
    const image_data_t *logo;
} airline_t;

extern const airline_t *lookupAirline(const char *iata_code);
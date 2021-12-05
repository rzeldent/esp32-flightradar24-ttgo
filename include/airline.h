#pragma once

#include <country.h>

typedef struct airline
{
    const char *icao_airline;
    const char *iata_airline;
    const char *name;
    const char *callsign;
    const country_t *country;
    const z_image_data_t *logo;
} airline_t;

extern const airline_t *lookupAirline(const char *iata_code);
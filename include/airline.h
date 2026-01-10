#pragma once

#include <country.h>

typedef struct airline
{
    const char icao_airline[3];
    char iata_airline[2];
    const char *name;
    const char *call_sign;
    const country_code_t country;
    const lv_img_dsc_t logo;
} airline_t;

extern const airline_t *lookup_airline(const char *icao_airline);
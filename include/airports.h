#pragma once

#include <Arduino.h>

#include <timage.h>

struct airport
{
    const char* iata;
    const char* name;
    const char* city;
    const char* country;
    double lon;
    double lat;
    const tImage* flag;
};

extern const airport *lookupAirport(const String &id);
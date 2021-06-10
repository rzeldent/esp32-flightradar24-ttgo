#pragma once

#include <Arduino.h>

struct airport
{
    const char* iata;
    const char* name;
    const char* city;
    const char* country;
    const char* flag;
};

extern const airport *lookupAirport(const String &id);
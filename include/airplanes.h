#pragma once

#include <Arduino.h>

struct airplane
{
    const char* id;
    const char* name;
};

extern const airplane *lookupAirplane(const String &id);
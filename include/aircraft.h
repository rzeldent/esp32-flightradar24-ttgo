#pragma once

typedef struct aircraft
{
    const char *type_designator;
    const char *manufacturer;
    const char *type;
    const char *description;
    const char *engine_type;
    const char engine_count;
} aircraft_t;

extern const aircraft_t *lookup_aircraft(const char *type_designator);
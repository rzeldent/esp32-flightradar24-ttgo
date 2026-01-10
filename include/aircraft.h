#pragma once

#include <cstdint>

typedef enum
{
    ENGINE_TYPE_NONE,
    ENGINE_TYPE_PISTON,
    ENGINE_TYPE_JET,
    ENGINE_TYPE_TURBOPROP,
    ENGINE_TYPE_ELECTRIC,
    ENGINE_TYPE_ROCKET
} engine_type_t;

typedef enum
{
    AIRCRAFT_TYPE_LANDPLANE,
    AIRCRAFT_TYPE_SEAPLANE,
    AIRCRAFT_TYPE_AMPHIBIAN,
    AIRCRAFT_TYPE_HELICOPTER,
    AIRCRAFT_TYPE_GYROCOPTER,
    AIRCRAFT_TYPE_TILTROTOR,
    AIRCRAFT_TYPE_MAULE,
    AIRCRAFT_TYPE_RILEY,
    AIRCRAFT_TYPE_HARMON,
    AIRCRAFT_TYPE_GLIDER,
    AIRCRAFT_TYPE_DRONE
} aircraft_type_t;

typedef struct aircraft
{
    const char *aircraft_code;
    const char *manufacturer;
    const char *type;
    const aircraft_type_t aircraft_type;
    const engine_type_t engine_type;
    const uint8_t engine_count;
} aircraft_t;

extern const aircraft_t *lookup_aircraft(const char *aircraft_code);
extern const char *engine_type_to_string(engine_type_t engine_type);
extern const char *aircraft_type_to_string(aircraft_type_t aircraft_type);
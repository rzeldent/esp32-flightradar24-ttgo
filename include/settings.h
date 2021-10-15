#pragma once

#include <Arduino.h>

// Center (Amsterdam Airport Schiphol: 52.45-52.15,4.44-5.05
constexpr auto center_latitude = 52.3f;
constexpr auto center_longitude = 4.75f;

// Range: .1 degree is approx 10km (0.008998 degrees)
constexpr auto range_latitude = 0.15f;
constexpr auto range_longitude = 0.6f;

// Refresh database every 2 minutes
constexpr auto refresh_flights_milliseconds = 120000ul;
// Allow 4 cycles of each flight
constexpr auto display_cycles = 4;
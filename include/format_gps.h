#pragma once

#include <Arduino.h>

String format_degrees(float value)
{
    char buffer[10]; // "DDD°MM.MM"
    int degrees = value;
    int minutes = (value - degrees) * 60;
    int seconds = (value - degrees - minutes / 60.0) * 60.0 * 60.0;
    // \u00b0 = degree symbol
    snprintf(buffer, sizeof(buffer), "%d\u00b0%02d'%02d\"", degrees, minutes, seconds);
    return buffer;
}

String format_lonlat(float lat, char pos, char neg)
{
    return lat >= 0 ? format_degrees(lat) + pos : format_degrees(-lat) + neg;
}

String format_lat(float lat)
{
    return format_lonlat(lat, 'N', 'S');
}

String format_lon(float lon)
{
    return format_lonlat(lon, 'E', 'W');
}

String format_gps_location(float lat, float lon)
{
    return format_lat(lat) + " " + format_lon(lon);
}

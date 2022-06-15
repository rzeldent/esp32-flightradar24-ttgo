#pragma once

#include <stdio.h>
#include <string>

std::string format_degrees(float value)
{
    char buffer[10]; // "DDD°MM.MM"
    int degrees = value;
    int minutes = (value - degrees) * 60;
    int seconds = (value - degrees - minutes / 60.0) * 3600;
    snprintf(buffer, sizeof(buffer), "%d`%02d'%02d\"", degrees, minutes, seconds);
    return buffer;
}

std::string format_lonlat(float lat, char pos, char neg)
{
    return lat >= 0 ? format_degrees(lat) + pos : format_degrees(-lat) + neg;
}

std::string format_lat(float lat)
{
    return format_lonlat(lat, 'N', 'S');
}

std::string format_lon(float lon)
{
    return format_lonlat(lon, 'E', 'W');
}

std::string format_gps_location(float lat, float lon)
{
    return format_lat(lat) + " " + format_lon(lon);
}

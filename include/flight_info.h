#pragma once

#include <list>
#include <string>

struct flight_info
{
    long icao;                   //  0 => ICAO 24-BIT ADDRESS - 4CA853
    float latitude;              //  1 => LAT - 52.3247
    float longitude;             //  2 => LON - 4.9812
    int track;                   //  3 => TRACK - 263 (Degrees)
    int altitude;                //  4 => ALTITUDE - 2100  (Feet)
    int speed;                   //  5 => SPEED - 144 (Knots)
    ushort squawk;               //  6 => SQUAWK -
    std::string radar;           //  7 => RADAR -
    std::string type_designator; //  8 => TYPE - B744 => Boeing 747-4B5(BCF)
    std::string registration;    //  9 => REGISTRATION - N709CK
    time_t timestamp;            // 10 => TIMSTAMP - 1593976456
    std::string from;            // 11 => FROM - AMS
    std::string to;              // 12 => TO - JFK
    std::string flight;          // 13 => FLIGHT NUMBER - LH8160
                                 // 14 =>
    std::string flight_operator; // 15 => OPERATOR - RYR
};

std::list<flight_info> get_flights(float latitude, float longitude, float range_latitude, float range_longitude);
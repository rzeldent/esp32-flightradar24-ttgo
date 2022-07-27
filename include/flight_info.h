#pragma once

#include <Arduino.h>
#include <list>
struct flight_info
{
    int32_t icao;           //  0 => ICAO 24-BIT ADDRESS - 4CA853
    float latitude;         //  1 => LAT - 52.3247
    float longitude;        //  2 => LON - 4.9812
    int track;              //  3 => TRACK - 263 (Degrees)
    int altitude;           //  4 => ALTITUDE - 2100  (Feet)
    int speed;              //  5 => SPEED - 144 (Knots)
    ushort squawk;          //  6 => SQUAWK -
    String radar;           //  7 => RADAR -
    String type_designator; //  8 => TYPE - B744 => Boeing 747-4B5(BCF)
    String registration;    //  9 => REGISTRATION - N709CK
    time_t timestamp;       // 10 => TIMSTAMP - 1593976456
    String from;            // 11 => FROM - AMS
    String to;              // 12 => TO - JFK
    String flight;          // 13 => FLIGHT NUMBER - LH8160
                            // 14 =>
    String flight_operator; // 15 => OPERATOR - RYR
};

extern bool get_flights(float latitude, float longitude, float range_latitude, float range_longitude, std::list<flight_info> &flights, String &error_message);
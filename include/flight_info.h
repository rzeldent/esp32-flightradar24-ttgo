#pragma once

#include <Arduino.h>
#include <memory>
#include <list>
#include <ArduinoJson.h>

struct flight_info
{
    String icao;            //  0 => ICAO 24-BIT ADDRESS - 4CA853
    String latitude;        //  1 => LAT - 52.3247
    String longitude;       //  2 => LON - 4.9812
    String track;           //  3 => TRACK - 263 (Degrees)
    String altitude;        //  4 => ALTITUDE - 2100  (Feet)
    String speed;           //  5 => SPEED - 144 (Knots)
    String squawk;          //  6 => SQUAWK -
    String radar;           //  7 => RADAR -
    String type;            //  8 => TYPE - B744 => Boeing 747-4B5(BCF)
    String registration;    //  9 => REGISTRATION - N709CK
    String timestamp;       // 10 => TIMSTAMP - 1593976456
    String from;            // 11 => FROM - AMS
    String to;              // 12 => TO - JFK
    String flight;          // 13 => FLIGHT NUMBER - LH8160
                            // 14 =>
    String flight_operator; // 15 => OPERATOR - RYR
};

std::shared_ptr<std::list<flight_info>> get_flights(float latitude, float longitude, float range_latitude, float range_longitude);
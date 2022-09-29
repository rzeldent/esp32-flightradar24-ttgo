#pragma once

#include <Arduino.h>
#include <list>

// Database of airplanes from https://openflights.org/data.html
#include <aircraft.h>
#include <airline.h>
#include <airport.h>

// Conversions to metric
#define FT_TO_M 0.3048
#define KTS_TO_KMH 1.852f

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

    int altitude_metric() const { return altitude * FT_TO_M; }
    int speed_metric() const { return speed * KTS_TO_KMH; }

    bool squawk_hijack() const { return squawk == 7500; }
    bool squawk_lost_communication_atc() const { return squawk == 7600; }
    bool squawk_emergency() const { return squawk == 7700; }

    const aircraft_t *aircraft_type() const { return type_designator.isEmpty() ? nullptr : lookup_aircraft(type_designator.c_str()); }
    const airline_t *airline() const { return flight_operator.isEmpty() ? nullptr : lookup_airline(flight_operator.c_str()); }
    const airport_t *from_airport() const { return from.isEmpty() ? nullptr : lookup_airport(from.c_str()); }
    const airport_t *to_airport() const { return to.isEmpty() ? nullptr : lookup_airport(to.c_str()); }
};

extern bool get_flights(float latitude, float longitude, float range_latitude, float range_longitude, std::list<flight_info> &flights, String &error_message);
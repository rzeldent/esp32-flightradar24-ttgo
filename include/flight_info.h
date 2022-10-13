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
    String icao_address;                //  0 => ICAO 24BIT ADDRESS - 4CA853
    float latitude;                     //  1 => LAT - 52.3247
    float longitude;                    //  2 => LON - 4.9812
    int heading;                        //  3 => TRACK - 263 (Degrees)
    int altitude;                       //  4 => ALTITUDE - 2100  (Feet)
    int ground_speed;                   //  5 => SPEED - 144 (Knots)
    String squawk;                      //  6 => SQUAWK -
    String radar;                       //  7 => RADAR -
    String aircraft_code;               //  8 => TYPE - B744 => Boeing 747-4B5(BCF)
    String registration;                //  9 => REGISTRATION - N709CK
    time_t timestamp;                   // 10 => TIMSTAMP - 1593976456
    String iata_origin_airport;         // 11 => FROM - AMS
    String iata_destination_airport;    // 12 => TO - JFK
    String flight;                      // 13 => FLIGHT NUMBER - LH8160
    bool on_ground;                     // 14 => ON GROUND - 0
    int vertical_speed;                 // 15 => VSPEED - 0
    String call_sign;                   // 16 => TRA822
    String icao_airline;                // 18 => OPERATOR - RYR

    String toString() const;

    int altitude_metric() const { return altitude * FT_TO_M; }
    int ground_speed_metric() const { return ground_speed * KTS_TO_KMH; }
    int vertical_speed_metric() const { return vertical_speed * KTS_TO_KMH; }

    bool squawk_hijack() const { return squawk == "7500"; }
    bool squawk_radio_failure() const { return squawk == "7600"; }
    bool squawk_emergency() const { return squawk == "7700"; }

    const aircraft_t *aircraft_type() const { return aircraft_code.isEmpty() ? nullptr : lookup_aircraft(aircraft_code.c_str()); }
    const airline_t *airline() const { return icao_airline.isEmpty() ? nullptr : lookup_airline(icao_airline.c_str()); }
    const airport_t *origin_airport() const { return iata_origin_airport.isEmpty() ? nullptr : lookup_airport(iata_origin_airport.c_str()); }
    const airport_t *destination_airport() const { return iata_destination_airport.isEmpty() ? nullptr : lookup_airport(iata_destination_airport.c_str()); }
};

extern bool get_flights(float latitude, float longitude, float range_latitude, float range_longitude, std::list<flight_info> &flights, String &error_message);
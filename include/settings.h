#pragma once

#include <timezones.h>

constexpr auto wifi_ssid_name = "<wifi_ssid_name>";
constexpr auto wifi_ssid_password = "<wifi_ssid_password>";

// There must always be 3 NTP servers. Remove or replace by null if not required
constexpr auto ntp_server_1 = "europe.pool.ntp.org";
constexpr auto ntp_server_2 = "0.pool.ntp.org";
constexpr auto ntp_server_3 = "1.pool.ntp.org";

// Center Amsterdam Airport Schiphol
constexpr auto center_location = "Amsterdam Schiphol";
constexpr auto center_latitude = 52.308601f;
constexpr auto center_longitude = 4.76389f;
#define LOCAL_TZ TZ_CE

// Center Charles de Gaulle International Airport
//constexpr auto center_location = "Charles de Gaulle International";
//constexpr auto center_latitude = 49.012798f;
//constexpr auto center_longitude = 2.55000f;
//#define LOCAL_TZ TZ_CE

// Center JFK Airport
//constexpr auto center_location = "John F Kennedy International";
//constexpr auto center_latitude = 40.639801f;
//constexpr auto center_longitude = -73.7789f;
//#define LOCAL_TZ TZ_usET

// Center LAX Airport:
//constexpr auto center_location = "Los Angeles International";
//constexpr auto center_latitude = 33.942501f;
//constexpr auto center_longitude = -118.407997f;
//#define LOCAL_TZ TZ_usPT

// Range: .1 degree is approx 10km (0.008998 degrees)
constexpr auto range_latitude = 0.15f;
constexpr auto range_longitude = 0.6f;

// Refresh database every 3 minutes
constexpr auto refresh_flights_milliseconds = 180000ul;
// Allow 4 cycles of each flight
constexpr auto display_cycles = 4;
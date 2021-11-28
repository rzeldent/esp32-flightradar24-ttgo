#pragma once

#include <Timezone.h>

constexpr auto wifi_ssid_name = "<wifi_ssid_name>";
constexpr auto wifi_ssid_password = "<wifi_ssid_password>";

// There must always be 3 NTP servers. Remove or replace by null if not required
constexpr auto ntp_server_1 = "europe.pool.ntp.org";
constexpr auto ntp_server_2 = "0.pool.ntp.org";
constexpr auto ntp_server_3 = "1.pool.ntp.org";

// Center Amsterdam Airport Schiphol: 52.308601, 4.76389
//constexpr auto center_location = "Amsterdam Schiphol";
//constexpr auto center_latitude = 52.308601f;
//constexpr auto center_longitude = 4.76389f;
// DST start and end (Central European Standard Time)
//constexpr TimeChangeRule dst_begin = {"CET", Last, Sun, Mar, 2, 120};    // UTC + 2 hours
//constexpr TimeChangeRule dst_end = {"CEST ", Last, Sun, Oct, 3, 60};     // UTC + 1 hour

// Center JFK Airport: 40.639801, -73.7789
//constexpr auto center_location = "John F Kennedy International";
//constexpr auto center_latitude = 40.639801f;
//constexpr auto center_longitude = -73.7789f;
// DST start and end (Eastern Time)
//constexpr TimeChangeRule dst_begin = {"EDT", Second, Sun, Mar, 2, -240};   // UTC - 4 hours
//constexpr TimeChangeRule dst_end = {"EST ", First, Sun, Nov, 2, -300};     // UTC - 5 hours

// Center LAX Airport:
constexpr auto center_location = "Los Angeles International";
constexpr auto center_latitude = 33.942501f;
constexpr auto center_longitude = -118.407997f;
// DST start and end (Eastern Time)
constexpr TimeChangeRule dst_begin = {"PDT", Second, Sun, Mar, 2, -420}; // UTC - 7 hours
constexpr TimeChangeRule dst_end = {"PST ", First, Sun, Nov, 2, -480};   // UTC - 8 hours

// Range: .1 degree is approx 10km (0.008998 degrees)
constexpr auto range_latitude = 0.15f;
constexpr auto range_longitude = 0.6f;

// Refresh database every 3 minutes
constexpr auto refresh_flights_milliseconds = 180000ul;
// Allow 4 cycles of each flight
constexpr auto display_cycles = 4;
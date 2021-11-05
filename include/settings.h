#pragma once

// https://github.com/JChristensen/Timezone
#include <Timezone.h>

constexpr auto wifi_ssid_name = "<wifi_ssid_name>";
constexpr auto wifi_ssid_password = "<wifi_ssid_password>";

// There must always be 3 NTP servers. Remove or replace by null if not required
constexpr auto ntp_server_1 = "europe.pool.ntp.org";
constexpr auto ntp_server_2 = "0.pool.ntp.org";
constexpr auto ntp_server_3 = "1.pool.ntp.org";

// DST start and end (Central European Standard Time)
constexpr TimeChangeRule dst_begin = {"CEST", Last, Sun, Mar, 2, 120};
constexpr TimeChangeRule dst_end = {"CET ", Last, Sun, Oct, 3, 60};

// Center (Amsterdam Airport Schiphol: 52.45-52.15,4.44-5.05
constexpr auto center_latitude = 52.3f;
constexpr auto center_longitude = 4.75f;

// Range: .1 degree is approx 10km (0.008998 degrees)
constexpr auto range_latitude = 0.15f;
constexpr auto range_longitude = 0.6f;

// Refresh database every 3 minutes
constexpr auto refresh_flights_milliseconds = 180000ul;
// Allow 4 cycles of each flight
constexpr auto display_cycles = 4;
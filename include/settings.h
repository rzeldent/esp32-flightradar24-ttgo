#pragma once

#define APP_TITLE "FlightRadar"
#define APP_VERSION "1.2"

#define WIFI_SSID "FlightRadar"
#define WIFI_PASSWORD nullptr
#define CONFIG_VERSION "1.5"

// One degree is 110.567 km (69.091 miles)

#define DEGREES_TO_KM 110.567
#define DEGREES_TO_MI 69.091

// Time servers
#define NTP_SERVER_1 "nl.pool.ntp.org"
#define NTP_SERVER_2 "europe.pool.ntp.org"
#define NTP_SERVER_3 "time.nist.gov"
#define NTP_SERVERS NTP_SERVER_1, NTP_SERVER_2, NTP_SERVER_3

// Amsterdam Airport Schiphol
#define DEFAULT_LOCATION "Amsterdam Schiphol Airport"
#define DEFAULT_LATITUDE 52.308601
#define DEFAULT_LONGITUDE 4.76389
#define DEFAULT_AIR true
#define DEFAULT_GROUND false
#define DEFAULT_GLIDERS true
#define DEFAULT_VEHICLES false
#define DEFAULT_TIMEZONE "Europe/Amsterdam"
#define DEFAULT_METRIC true
// By default take a 10km range
#define DEFAULT_RANGE_LATITUDE 0.1
#define DEFAULT_RANGE_LONGITUDE 0.1

// Charles de Gaulle International Airport
//#define DEFAULT_LOCATION "Charles de Gaulle International"
//#define DEFAULT_LATITUDE 49.012798
//#define DEFAULT_LONGITUDE 2.55000
//#define DEFAULT_AIR true
//#define DEFAULT_GROUND false
//#define DEFAULT_GLIDERS true
//#define DEFAULT_VEHICLES false
//#define DEFAULT_TIMEZONE "Europe/Paris"
//#define DEFAULT_METRIC true
// By default take a 10km range
//#define DEFAULT_RANGE_LATITUDE 0.1
//#define DEFAULT_RANGE_LONGITUDE 0.1

// Venice Marco Polo Airport
//#define DEFAULT_LOCATION "Venice Marco Polo Airport"
//#define DEFAULT_LATITUDE 45.50299
//#define DEFAULT_LONGITUDE 12.3519
//#define DEFAULT_AIR true
//#define DEFAULT_GROUND false
//#define DEFAULT_GLIDERS true
//#define DEFAULT_VEHICLES false
//#define DEFAULT_TIMEZONE "Europe/Rome"
//#define DEFAULT_METRIC true
// By default take a 10km range
//#define DEFAULT_RANGE_LATITUDE 0.1
//#define DEFAULT_RANGE_LONGITUDE 0.1

// JFK Airport
//#define DEFAULT_LOCATION "John F Kennedy International"
//#define DEFAULT_LATITUDE 40.639801
//#define DEFAULT_LONGITUDE -73.7789
//#define DEFAULT_AIR true
//#define DEFAULT_GROUND false
//#define DEFAULT_GLIDERS true
//#define DEFAULT_VEHICLES false
//#define DEFAULT_TIMEZONE "America/New_York"
//#define DEFAULT_METRIC false
// By default take a 5mile range
//#define DEFAULT_RANGE_LATITUDE 0.05
#//define DEFAULT_RANGE_LONGITUDE 0.05

// LAX Airport:
//#define DEFAULT_LOCATION "Los Angeles International"
//#define DEFAULT_LATITUDE 33.942501
//#define DEFAULT_LONGITUDE -118.407997
//#define DEFAULT_AIR true
//#define DEFAULT_GROUND false
//#define DEFAULT_GLIDERS true
//#define DEFAULT_TIMEZONE "America/Los_Angeles"
//#define DEFAULT_METRIC false
// By default take a 5mile range
//#define DEFAULT_RANGE_LATITUDE 0.05
//#define DEFAULT_RANGE_LONGITUDE 0.05

// Refresh screen every 10 seconds
constexpr auto flight_milliseconds = 15 * 1000ul;
constexpr auto flight_milliseconds_error = 120 * 1000ul;
constexpr auto  flight_milliseconds_noflights= 30 * 1000ul;
// Allow 4 cycles of each flight
constexpr auto display_cycles = 4;

// Backlight dimming: the backlight LED (TFT_BL) is driven with PWM so the
// brightness can be changed with the upper (brighter) and lower (dimmer) buttons.
constexpr auto backlight_pwm_frequency = 5000;   // PWM frequency in Hz (outside the audible range)
constexpr auto backlight_pwm_resolution = 8;     // PWM resolution in bits (duty cycle 0..255)
constexpr auto backlight_max_level = 255;        // full brightness
constexpr auto backlight_step = 8;               // brightness delta per button action
constexpr auto backlight_debounce_ms = 20;       // button debounce time
constexpr auto backlight_repeat_delay_ms = 500;  // hold time before auto-repeat starts
constexpr auto backlight_repeat_rate_ms = 100;   // auto-repeat interval while holding a button
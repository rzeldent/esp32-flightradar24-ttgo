#pragma once

// The SSID and password of the accesspoint to connect to
#define WIFI_SSID "<your wifi ssid>"
#define WIFI_PASSWORD "<your wifi password>"

// Center (Amsterdam Airport Schiphol: 52.45-52.15,4.44-5.05
#define LATITUDE 52.3f
#define LONGITUDE 4.75f

// Range: .1 degree is approx 10km (0.008998 degrees)
#define RANGE_LATITUDE 0.15f
#define RANGE_LONGITUDE 0.6f

// Refresh database every 2 minutes
#define UPDATE_FLIGHTS_MILLISECONDS 120000
// Allow 4 cycles of each flight
#define CYCLES_PER_FLIGHT 4
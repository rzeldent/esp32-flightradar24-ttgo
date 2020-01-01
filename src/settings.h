#pragma once

// The SSID and password of the accesspoint to connect to
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// NTP pool to use for the time synchronisation
#define NTP_POOL "europe.pool.ntp.org"
// The offset in seconds from UTC (+1)
#define NTP_TIMEOFFSET 3600
// Synchronize interval in milliseconds (every 30 minutes)
#define NTP_UPDATE_MILLISECONDS (30 * 60 * 1000)

// Center (Amsterdam Airport Schiphol: 52.45,52.15,4.44,5.05
#define LATTITUDE 52.3f
#define LONGITUDE 4.75f

// Range: .1 degree is approx 10km (0.008998 degrees)
#define RANGE_LATTITUDE 0.15
#define RANGE_LONGITUDE 0.6

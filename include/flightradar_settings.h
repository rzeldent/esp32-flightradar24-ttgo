#pragma once

#define SSID_MAX_LEN            32
#define PASS_MAX_LEN            64

#define NUM_WIFI_CREDENTIALS      1

// Magic salt to verify the settings
constexpr const int kSaltEEPROMSettings = 0xB7CA;

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_password  [PASS_MAX_LEN];
}  wifi_credentials_t;

typedef struct
{
    wifi_credentials_t wifi_credentials[NUM_WIFI_CREDENTIALS];
    float latitude;
    float longitude;
    char location[32];
    int time_zone;
    int salt = kSaltEEPROMSettings;
} flight_radar_settings_t;
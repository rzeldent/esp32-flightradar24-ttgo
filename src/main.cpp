#include <Arduino.h>
#include <SPI.h>

// Settings for the display are defined in platformio.ini
#include <TFT_eSPI.h>
#include <TFT_eFEX.h>

#include <Button2.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Run Task
// PlatformIO/Build Filesystem Image
// PlatformIO/Upload Filesystem Image
#include <FS.h>
#include <SPIFFS.h>

#include <map>
#include <flight_info.h>

// Database of airplanes from https://openflights.org/data.html
#include <airplanes.h>
#include <airports.h>

// This is a copy of the setting.h. Made hidden so does not ends up in repository.
#include ".settings.h"

#define BUTTON_1 35
#define BUTTON_2 0

// Screen is 240 * 135 pixels (rotated)
#define BACKGROUND_COLOR TFT_BLACK
#define TEXT_COLOR TFT_WHITE

#define FLAG_WIDTH 20
#define FLAG_HEIGHT 13

#define FLAG_MARGIN_X 4
#define FLAG_MARGIN_Y 1

// Use hardware SPI
auto tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
auto fex = TFT_eFEX(&tft);

Button2 button1(BUTTON_1);
Button2 button2(BUTTON_2);

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  esp_log_level_set("*", ESP_LOG_VERBOSE);

  log_i("CPU Freq = %d Mhz", getCpuFrequencyMhz());
  log_i("Starting Flightradar...");

  if (!SPIFFS.begin(true))
    log_e("SPIFFS initialization failed");

  tft.init();
  tft.setRotation(1);
  tft.setTextDatum(TL_DATUM); // Top Left
  tft.setTextColor(TEXT_COLOR);
  tft.setTextWrap(false, false);

  // Show logo
  fex.drawBmp("/startup.bmp", 0, 0);
  // Font(4) = 26px
  tft.setTextFont(4);
  tft.println("Flight Radar");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Show logo for one second
  delay(2500);
}

#define UPDATE_FLIGHTS_MILLISECONDS 90000
unsigned long last_update_flights;
#define UPDATE_FLIGHT_MILLISECONDS 10000
unsigned long last_update_flight;

#define LOOP_MILLISECONDS 1000

void clear()
{
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, BACKGROUND_COLOR);
  tft.setCursor(0, 0);
}

void display_flight(const flight_info &flight_info)
{
  log_i("Showing flight info ICAO: %s", flight_info.icao);
  clear();

  auto airplane = lookupAirplane(flight_info.type);
  auto from = lookupAirport(flight_info.from);
  auto to = lookupAirport(flight_info.to);

  auto flight = flight_info.flight;

  // Font(4) = 26px
  tft.setTextFont(4);
  tft.println(flight + "  " + flight_info.from + ">" + flight_info.to);

  // Font(2) = 16px
  tft.setTextFont(2);
  tft.println(flight_info.registration + " - " + (airplane ? airplane->name : flight_info.type));

  tft.setCursor(0, 26 + 16 + 8);
  if (from != nullptr)
  {
    tft.println(from->name);
    if (from->flag)
    {
      auto flag = String("/flags/" + String(from->flag) + ".bmp");
      auto cursor_x = tft.getCursorX(), cursor_y = tft.getCursorY();
      fex.drawBmp(flag, cursor_x, cursor_y + FLAG_MARGIN_Y);
      tft.setCursor(cursor_x + FLAG_WIDTH + FLAG_MARGIN_X, cursor_y);
    }
    tft.println(from->country);
  }

  tft.setCursor(0, 26 + 4 * 16);
  if (to != nullptr)
  {
    tft.println(to->name);
    if (from->flag)
    {
      auto flag = String("/flags/" + String(to->flag) + ".bmp");
      auto cursor_x = tft.getCursorX(), cursor_y = tft.getCursorY();
      fex.drawBmp(flag, cursor_x, cursor_y + FLAG_MARGIN_Y);
      tft.setCursor(cursor_x + FLAG_WIDTH + FLAG_MARGIN_X, cursor_y);
    }
    tft.println(to->country);
  }
}

void loop()
{
  static std::shared_ptr<std::list<flight_info>> flights;
  static std::list<flight_info>::const_iterator it;

  auto now = millis();

  if (WiFi.isConnected())
  {
    if (last_update_flights == 0 || now - last_update_flights > UPDATE_FLIGHTS_MILLISECONDS)
    {
      log_i("Updating flights");
      // update flights
      flights = get_flights(LATITUDE, LONGITUDE, RANGE_LATITUDE, RANGE_LONGITUDE);
      // Remove all the flights without flight number
      flights->remove_if([](const flight_info &f)
                         { return f.flight.isEmpty(); });
      it = flights->begin();
      last_update_flights = now;
    }

    if (last_update_flight == 0 || now - last_update_flight > UPDATE_FLIGHT_MILLISECONDS)
    {
      if (it != flights->end())
      {
        display_flight(*it);
        if (++it == flights->end())
          it = flights->begin();
      }
      else
      {
        clear(); // Font(4) = 26px
        tft.setTextFont(4);
        tft.println("No flights in range: " + String(LATITUDE) + "/" + String(LONGITUDE));
      }

      last_update_flight = now;
    }
  }
  else
  {
    log_i("Connecting to: " WIFI_SSID);
  }

  delay(LOOP_MILLISECONDS);
}
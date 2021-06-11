#include <Arduino.h>
#include <SPI.h>
#include <FS.h>
#include <SPIFFS.h>
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

  if (!SPIFFS.begin())
  {
    log_e("SPIFFS initialization failed");
  }

  tft.init();
  //tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
  tft.setRotation(1);
  tft.setTextDatum(TL_DATUM); // Top Left
  tft.setTextColor(TEXT_COLOR);
  tft.setTextWrap(false, false);

  // Clear the screen
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, BACKGROUND_COLOR);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
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
  clear();
  // Font(2) = 16px
  tft.setTextFont(2);

  auto airplane = lookupAirplane(flight_info.type);
  tft.println(flight_info.registration + " - " + (airplane ? airplane->name : flight_info.type));
  auto from = lookupAirport(flight_info.from);
  auto to = lookupAirport(flight_info.to);

  auto flight = flight_info.flight;
  if (!flight.isEmpty())
  {
    tft.println(String("Flight: ") + flight + " (" + flight_info.from + "->" + flight_info.to + ")");

    if (from != nullptr)
    {
      tft.println("From:");
      tft.println(from->name);
      if (from->flag)
      {
        auto flag = String("/flags/" + String(from->flag) + ".bmp");
        auto cursor_x = tft.getCursorX();
        auto cursor_y = tft.getCursorY();
        fex.drawBmp(flag, 3 * 16, cursor_y);
        tft.setCursor(cursor_x + 20, cursor_y);
      }
      tft.println(from->country);
    }

    if (to != nullptr)
    {
      tft.println("To: ");
      tft.println(to->name);
      tft.println(to->country);
    }
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
        clear();
        tft.println("No flights in range: " + String(LATITUDE) + "/" + String(LONGITUDE));
      }

      last_update_flight = now;
    }
  }
  else
  {
    tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, BACKGROUND_COLOR);
    tft.setCursor(0, 0);
    tft.println("Connecting to: " WIFI_SSID);
  }

  delay(LOOP_MILLISECONDS);
}
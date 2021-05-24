#include <Arduino.h>
#include <SPI.h>
#include <FS.h>
#include <SPIFFS.h>
// Setting for the display are defined in platformio.ini
#include <TFT_eSPI.h>

#include <Button2.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

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
Button2 button1(BUTTON_1);
Button2 button2(BUTTON_2);
WiFiUDP ntpUDP;

#define LATITUDE_MIN String(LATITUDE - RANGE_LATITUDE)
#define LONGITUDE_MIN String(LONGITUDE - RANGE_LONGITUDE)
#define LATITUDE_MAX String(LATITUDE + RANGE_LATITUDE)
#define LONGITUDE_MAX String(LONGITUDE + RANGE_LONGITUDE)

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  esp_log_level_set("*", ESP_LOG_VERBOSE);

  log_i("CPU Freq = %d Mhz", getCpuFrequencyMhz());
  log_i("Starting Flightradar...");

  tft.init();
  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
  tft.setRotation(1);
  tft.setTextDatum(TL_DATUM); // Top Left
  tft.setTextColor(TEXT_COLOR);

  // Clear the screen
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, BACKGROUND_COLOR);

  // Wait 30 seconds for a connection, otherwise reset
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  auto i = 30;
  do
  {
    if (!i--)
      ESP.restart();

    sleep(1);
  } while (!WiFi.isConnected());

  log_i("Connected");
}

std::shared_ptr<std::list<flight_info>> flights;
std::list<flight_info>::const_iterator it;

#define UPDATE_FLIGHTS_MILLISECONDS 90000
unsigned long last_update_flights;
#define UPDATE_FLIGHT_MILLISECONDS 10000
unsigned long last_update_flight;

#define LOOP_MILLISECONDS 1000

void loop()
{
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
      log_i("Updating flight");

      tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, BACKGROUND_COLOR);
      tft.setCursor(0, 0);
      // Font(2) = 16px
      tft.setTextFont(2);

      if (it != flights->end())
      {
        auto airplane = lookupAirplane(it->type);
        tft.println(it->registration + " - " + (airplane ? airplane->name : it->type));
        auto from = lookupAirport(it->from);
        auto to = lookupAirport(it->to);

        auto flight = it->flight;
        if (!flight.isEmpty())
          tft.println(String("Flight: ") + flight + " (" + it->from + "->" + it->to + ")");
  
        if (from != nullptr)
        {
          tft.println("From:");
          tft.println(from->name);
          tft.println(from->country);
        }

        if (to != nullptr)
        {
          tft.println("To: ");
          tft.println(to->name);
          tft.println(to->country);
        }

        if (++it == flights->end())
          it = flights->begin();
      }
      else
        tft.println("No flights in range: " + String(LATITUDE) + "/" + String(LONGITUDE));

      last_update_flight = now;
    }
  }
  else
    tft.println("Cannot connect to accesspoint: " WIFI_SSID);

  delay(LOOP_MILLISECONDS);
}
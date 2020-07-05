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

#include <NTPClient.h>
#include <Timelib.h>
#include <Timezone.h> // https://github.com/JChristensen/Timezone

#include <map>

// Database of airplanes
#include <airplanes.h>

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
// Synchronize time every hour
NTPClient timeClient(ntpUDP, NTP_POOL, NTP_TIMEOFFSET, NTP_UPDATE_MILLISECONDS);
TimeChangeRule dstBegin = DST_BEGIN;
TimeChangeRule dstEnd = DST_END;
Timezone timeZone(dstBegin, dstEnd);

#define LATTITUDE_MIN String(LATTITUDE - RANGE_LATTITUDE)
#define LONGITUDE_MIN String(LONGITUDE - RANGE_LONGITUDE)
#define LATTITUDE_MAX String(LATTITUDE + RANGE_LATTITUDE)
#define LONGITUDE_MAX String(LONGITUDE + RANGE_LONGITUDE)

void setup()
{
  Serial.begin(115200);

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

  // Start the timeclient
  timeClient.begin();

  Serial.println("Connected");
}

DynamicJsonDocument doc_flight_data(8192);
std::map<String, JsonArray> flights;
std::map<String, JsonArray>::const_iterator current_flight;

void update_flights()
{
  // gnd=0 means no items on the ground
  const static String flight_data_url("http://data-live.flightradar24.com/zones/fcgi/feed.js?bounds=" + LATTITUDE_MAX + "," + LATTITUDE_MIN + "," + LONGITUDE_MIN + "," + LONGITUDE_MAX + "&faa=1&satellite=1&mlat=1&flarm=1&adsb=1&gnd=0&air=1&vehicles=0&estimated=1&maxage=14400&gliders=1&stats=0");

  flights.clear();

  HTTPClient client;
  Serial.println(("Request states=" + flight_data_url).c_str());
  client.begin(flight_data_url);
  const auto code = client.GET();
  Serial.println(("Get states code=" + String(code)).c_str());
  if (code == HTTP_CODE_OK)
  {
    String response = client.getString();
    Serial.println(("Response states=" + response).c_str());
    // Parse JSON states object
    const auto error = deserializeJson(doc_flight_data, response);
    Serial.println(error.c_str());
    if (error == DeserializationError::Ok)
    {
      JsonObject flight_data_root = doc_flight_data.as<JsonObject>();

      for (JsonPair kvp : flight_data_root)
      {
        if (!kvp.value().is<JsonArray>())
          continue;

        Serial.println(kvp.key().c_str());
        auto items = kvp.value().as<JsonArray>();
        flights.insert(std::pair<String, JsonArray>(kvp.key().c_str(), items));
      }

      current_flight = flights.begin();
    }
  }
  client.end();
}

#define UPDATE_FLIGHTS_MILLISECONDS 90000
unsigned long last_update_flights;
#define UPDATE_FLIGHT_MILLISECONDS 10000
unsigned long last_update_flight;

#define LOOP_MILLISECONDS 1000

void loop()
{
  auto now = millis();

  if (!timeClient.update())
    timeClient.forceUpdate();

  if (WiFi.isConnected())
  {
    if (last_update_flights == 0 || now - last_update_flights > UPDATE_FLIGHTS_MILLISECONDS)
    {
      Serial.println(" Updating flights");
      // update flights
      update_flights();
      last_update_flights = now;
    }
  }

  if (last_update_flight == 0 || now - last_update_flight > UPDATE_FLIGHT_MILLISECONDS)
  {
    Serial.println(" Updating flight");

    if (flights.size())
    {
      tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, BACKGROUND_COLOR);
      tft.setCursor(0, 0);
      tft.setTextFont(4);

      if (current_flight != flights.end())
      {
        //  0 => ICAO 24-BIT ADDRESS - 4CA853
        //  1 => LAT - 52.3247
        //  2 => LON - 4.9812
        //  3 => TRACK - 263 (Degrees)
        //  4 => ALTITUDE - 2100  (Feet)
        //  5 => SPEED - 144 (Knots)
        //  6 => SQUAWK - 
        //  7 => RADAR - 
        //  8 => TYPE - B744 => Boeing 747-4B5(BCF)
        //  9 => REGISTRATION - N709CK
        // 10 => TIMSTAMP - 1593976456
        // 11 => FROM - AMS
        // 12 => TO - JFK
        // 13 => FLIGHT NUMBER - LH8160
        // 14 => 
        // 15 => OPERATOR - RYR


        //tft.println(current_flight->first.c_str());
        auto airplane = (airplanes.find(current_flight->second[8].as<char *>()));
        tft.println(airplane != airplanes.end() ? airplane->second : current_flight->second[8].as<char *>()); 
        tft.println(current_flight->second[9].as<char *>());
        tft.println((String(current_flight->second[11].as<char *>()) + " => " + String(current_flight->second[12].as<char *>())).c_str());
        tft.println(current_flight->second[13].as<char *>()); // Flight number

        if (++current_flight == flights.end())
          current_flight = flights.begin();
      }
      else
      {
        tft.println("No flights");
      }
    }
    last_update_flight = now;
  }

  Serial.print(".");
  delayMicroseconds(1000 * LOOP_MILLISECONDS);
}
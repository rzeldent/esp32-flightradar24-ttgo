#include <Arduino.h>
#include <soc/rtc_cntl_reg.h>
#include <SPI.h>

// Settings for the display are defined in platformio.ini
#include <TFT_eSPI.h>
#include <TFT_eFEX.h>
#include <ttgo_backlight.h>

#define FONT_16PT 2
#define FONT_26PT 4
#define FONT_48PT 6
#define FONT_48PT_LCD 7

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

// GPIO of the buttons on the TTGO Display
#define BUTTON_1 35
#define BUTTON_2 0

// Screen is 240 * 135 pixels (rotated)
#define BACKGROUND_COLOR TFT_BLACK
#define TEXT_COLOR TFT_WHITE

#define FLAG_WIDTH 20
#define FLAG_HEIGHT 13

#define FLAG_MARGIN_X 4
#define FLAG_MARGIN_Y 2

// Use hardware SPI
auto tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
auto fex = TFT_eFEX(&tft);
byte lcd_backlight_intensity = TTGO_DEFAULT_BACKLIGHT_INTENSITY;

Button2 button1(BUTTON_1);
Button2 button2(BUTTON_2);

void setup()
{
  // Disable brownout
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  esp_log_level_set("*", ESP_LOG_VERBOSE);

  log_i("CPU Freq = %d Mhz", getCpuFrequencyMhz());
  log_i("Starting Flightradar...");

  if (!SPIFFS.begin(true))
    log_e("SPIFFS initialization failed");

  // Start Display
  ttgo_backlight_init();
  ttgo_backlight_intensity(lcd_backlight_intensity);
  tft.init();
  tft.setRotation(1);
  tft.setTextDatum(TL_DATUM); // Top Left
  tft.setTextColor(TEXT_COLOR);
  tft.setTextWrap(false, false);

  // Show logo
  fex.drawBmp("/startup.bmp", 0, 0);
  tft.setTextFont(FONT_26PT);
  tft.println("Flight Radar");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Show logo for one second
  delay(2500);
}

unsigned long last_update_flights;

void clear()
{
  log_d("Clear screen");
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

  tft.setTextFont(FONT_26PT);
  tft.println(flight + "  " + flight_info.from + ">" + flight_info.to);

  tft.setTextFont(FONT_16PT);
  tft.println(flight_info.registration + " - " + (airplane ? airplane->name : flight_info.type));

  tft.setCursor(0, 26 + 16 + 8);
  if (from != nullptr)
  {
    tft.println(from->name);
    if (from->flag)
    {
      auto flag = String("/flags/" + String(from->flag) + ".bmp");
      log_d("Display bitmap %s", flag.c_str());
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
      log_d("Display bitmap %s", flag.c_str());
      auto cursor_x = tft.getCursorX(), cursor_y = tft.getCursorY();
      fex.drawBmp(flag, cursor_x, cursor_y + FLAG_MARGIN_Y);
      tft.setCursor(cursor_x + FLAG_WIDTH + FLAG_MARGIN_X, cursor_y);
    }
    tft.println(to->country);
  }
}

// Time per flight
unsigned long update_flights_milliseconds;

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
      log_d("Remove flights without flight number");
      flights->remove_if([](const flight_info &f)
                         { return f.flight.isEmpty(); });

      log_i("Number of flights to display: %d", flights->size());
      auto num_flights = flights->size();
      if (num_flights == 0)
      {
        delay(UPDATE_FLIGHTS_MILLISECONDS / 2);
        return;
      }

      update_flights_milliseconds = (UPDATE_FLIGHTS_MILLISECONDS / CYCLES_PER_FLIGHT) / num_flights;
      log_i("Duration to show each flight: %d milliseconds", update_flights_milliseconds);

      it = flights->begin();
      last_update_flights = now;
    }

    if (it != flights->end())
    {
      display_flight(*it);
      if (++it == flights->end())
      {
        log_d("Restart with first flight");
        it = flights->begin();
      }
    }
    else
    {
      log_d("No flights in range");
      clear();
      tft.setTextFont(FONT_26PT);
      tft.println("No flights in range");
    }

    delay(update_flights_milliseconds);
  }
  else
  {
    log_i("Connecting to: " WIFI_SSID);
    delay(100);
  }
}

#include <Arduino.h>
#include <soc/rtc_cntl_reg.h>
#include <SPI.h>

// Settings for the display are defined in platformio.ini
#include <TFT_eSPI.h>
#include <TFT_eFEX.h>
#include <ttgo_backlight.h>

constexpr auto font_16pt = 2;
constexpr auto font_26pt = 4;
constexpr auto font_48pt = 6;
constexpr auto font_48pt_lcd = 7;

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
constexpr auto button_top = 35;
constexpr auto button_bottom = 0;

// Screen is 240 * 135 pixels (rotated)
constexpr auto background_color = TFT_BLACK;
constexpr auto text_color = TFT_WHITE;

constexpr auto flag_width_px = 20;
constexpr auto flag_height_px = 13;

constexpr auto flag_margin_x_px = 4;
constexpr auto flag_margin_y_px = 2;

// Use hardware SPI
auto tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
auto fex = TFT_eFEX(&tft);
auto lcd_backlight_intensity = TTGO_DEFAULT_BACKLIGHT_INTENSITY;

Button2 button1(button_top);
Button2 button2(button_bottom);

void setup()
{
  // Disable brownout
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  esp_log_level_set("*", ESP_LOG_VERBOSE);

  log_i("CPU Freq = %d Mhz", getCpuFrequencyMhz());
  log_i("Starting Flight Radar...");

  if (!SPIFFS.begin(true))
    log_e("SPIFFS initialization failed");

  // Start Display
  ttgo_backlight_init();
  ttgo_backlight_intensity(lcd_backlight_intensity);
  tft.init();
  tft.setRotation(1);         // Landscape
  tft.setTextDatum(TL_DATUM); // Top Left
  tft.setTextColor(text_color);
  tft.setTextWrap(false, false);

  // Show logo
  fex.drawBmp("/startup.bmp", 0, 0);
  tft.setTextFont(font_26pt);
  tft.print("Flight Radar");

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);

  // Show logo for 2.5 seconds
  delay(2500);
}

unsigned long last_update_flights;

void clear()
{
  log_d("Clear screen");
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, background_color);
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

  tft.setTextFont(font_26pt);
  tft.println(flight + "  " + flight_info.from + ">" + flight_info.to);

  tft.setTextFont(font_16pt);
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
      fex.drawBmp(flag, cursor_x, cursor_y + flag_margin_y_px);
      tft.setCursor(cursor_x + flag_width_px + flag_margin_x_px, cursor_y);
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
      fex.drawBmp(flag, cursor_x, cursor_y + flag_margin_y_px);
      tft.setCursor(cursor_x + flag_width_px + flag_margin_x_px, cursor_y);
    }
    tft.println(to->country);
  }
}

// Time per flight
unsigned long update_flight_milliseconds;

void loop()
{
  static std::shared_ptr<std::list<flight_info>> flights;
  static std::list<flight_info>::const_iterator it;

  auto now = millis();

  if (WiFi.isConnected())
  {
    if (last_update_flights == 0 || now - last_update_flights > refresh_flights_milliseconds)
    {
      log_i("Updating flights");
      // update flights
      flights = get_flights(center_latitude, center_longitude, range_latitude, range_longitude);
      log_d("Remove flights without flight number");
      flights->remove_if([](const flight_info &f)
                         { return f.flight.isEmpty(); });

      log_i("Number of flights to display: %d", flights->size());
      auto num_flights = flights->size();
      if (num_flights == 0)
      {
        delay(refresh_flights_milliseconds);
        return;
      }

      update_flight_milliseconds = refresh_flights_milliseconds / display_cycles / num_flights;
      log_i("Duration to show each flight: %d milliseconds", update_flight_milliseconds);

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
      tft.setTextFont(font_26pt);
      tft.println("No flights in range");
    }

    delay(update_flight_milliseconds);
  }
  else
  {
    log_i("Connecting to: %s", wifi_ssid);
    delay(100);
  }
}

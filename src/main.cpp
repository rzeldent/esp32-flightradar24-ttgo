#include <Arduino.h>
#include <soc/rtc_cntl_reg.h>
#include <SPI.h>

// Settings for the display are defined in platformio.ini
#include <TFT_eSPI.h>
#include <ttgo_backlight.h>

constexpr auto font_16pt = 2;
constexpr auto font_26pt = 4;
constexpr auto font_48pt = 6;
constexpr auto font_48pt_lcd = 7;

#include <Button2.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include <map>
#include <flight_info.h>

// Database of airplanes from https://openflights.org/data.html
#include <aircrafts.h>
#include <airports.h>
#include <airlines.h>
#include <images.h>

#include <math.h>

// Make a copy of the file settings.h and change the name to .settings.h (hidden so does not ends up in repository).
#include <.settings.h>

// GPIO of the buttons on the TTGO Display
constexpr auto button_top = 35;
constexpr auto button_bottom = 0;

// Screen is 240 * 135 pixels (rotated)
constexpr auto background_color = TFT_BLACK;
constexpr auto text_color = TFT_WHITE;

// Flag
constexpr auto flag_margin_x_px = 4;
constexpr auto flag_margin_y_px = 2;

constexpr auto logo_width_px = 32;
constexpr auto logo_height_px = 32;

// Use hardware SPI
auto tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
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

  // Start Display
  ttgo_backlight_init();
  ttgo_backlight_intensity(lcd_backlight_intensity);
  tft.init();
  // Swap the colour byte order when rendering
  tft.setSwapBytes(true);
  tft.setRotation(1);         // Landscape
  tft.setTextDatum(TL_DATUM); // Top Left
  tft.setTextColor(text_color);
  tft.setTextWrap(false, false);

  // Show splash screen
  tft.pushImage(0, 0, image_splash.width, image_splash.height, image_splash.data);
  tft.setTextFont(font_26pt);
  tft.print("Flight Radar");

  WiFi.mode(WIFI_STA);
  // SSID_NAME and SSID_PASSWORD should come from build flags settings
  WiFi.begin(wifi_ssid_name, wifi_ssid_password);
  // Show logo for 2.5 seconds
  delay(2500);
}

void clear()
{
  log_d("Clear screen");
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, background_color);
  tft.setCursor(0, 0);
}

void arrow(int x2, int y2, int x1, int y1, int alength, int awidth, int colour)
{
  float distance;
  int dx, dy, x2o, y2o, x3, y3, x4, y4, k;
  distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
  dx = x2 + (x1 - x2) * alength / distance;
  dy = y2 + (y1 - y2) * alength / distance;
  k = awidth / alength;
  x2o = x2 - dx;
  y2o = dy - y2;
  x3 = y2o * k + dx;
  y3 = x2o * k + dy;
  //
  x4 = dx - y2o * k;
  y4 = dy - x2o * k;
  tft.drawLine(x1, y1, x2, y2, colour);
  tft.drawLine(x1, y1, dx, dy, colour);
  tft.drawLine(x3, y3, x4, y4, colour);
  tft.drawLine(x3, y3, x2, y2, colour);
  tft.drawLine(x2, y2, x4, y4, colour);
}

void draw_compass(int32_t x, int32_t y, int32_t w, int32_t h, float heading, ushort color_border, ushort color_arrow)
{
  // TFT is rotated 90 degrees; correct angle
  heading -= 90;
  // convert to radians: 0-360 => 0 - 2*PI
  auto radians = heading / 360 * 2 * M_PI;
  struct point
  {
    int x;
    int y;
  };
  point center = {x + w / 2, y + h / 2};
  // draw border
  tft.drawCircle(center.x, center.y, w / 2, color_border);

  auto arrow_length = w / 2 - 1;
   auto tip_height = arrow_length/4;
   auto tip_width = arrow_length/4;

  double value_sin = sin(radians);
  double value_cos = cos(radians);

  auto transform = [center, value_sin, value_cos](point p)
  {
    return point{(int)(center.x + p.x * value_cos - p.y * value_sin), (int)(center.y + p.x * value_sin + p.y * value_cos)};
  };

  // End of arrow
  auto arrow_end = transform(point{arrow_length, 0});
  auto arrow_tip_left = transform(point{arrow_length - tip_height, -tip_width / 2});
  auto arrow_tip_right = transform(point{arrow_length - tip_height, tip_width / 2});
  // Draw from center to end
  tft.drawLine(center.x, center.y, arrow_end.x, arrow_end.y, color_arrow);
  // Draw tip
  tft.fillTriangle(arrow_tip_left.x, arrow_tip_left.y, arrow_tip_right.x, arrow_tip_right.y, arrow_end.x, arrow_end.y, color_arrow);
}

String format_degrees(float latlon)
{
  auto degrees = (int)latlon;
  latlon -= degrees;
  latlon *= 60;
  auto minutes = (int)latlon;
  auto seconds = (int)((latlon - minutes) * 60);
  return String(degrees) + "`" + String(minutes) + "'" + String(seconds) + "''";
}

String format_latitude(float lat)
{
  return lat >= 0 ? format_degrees(lat) + "N" : format_degrees(-lat) + "S";
}

String format_longitude(float lon)
{
  return lon >= 0 ? format_degrees(lon) + "E" : format_degrees(-lon) + "W";
}

String format_latitude_longitude(float lat, float lon)
{
  return format_latitude(lat) + " " + format_longitude(lon);
}

void display_flight(const flight_info &flight_info)
{
  log_i("Showing flight info ICAO: %s", flight_info.icao);
  clear();

  auto aircraft = lookupAircraft(flight_info.type_designator.c_str());
  auto from = lookupAirport(flight_info.from.c_str());
  auto to = lookupAirport(flight_info.to.c_str());
  auto airline = lookupAirline(flight_info.flight_operator.c_str());

  tft.setTextFont(font_26pt);
  tft.println(flight_info.flight + "  " + flight_info.from + ">" + flight_info.to);

  auto y = tft.getCursorY();
  tft.setCursor(0, tft.getCursorY() + 2);
  tft.println(String(flight_info.altitude) + "ft  " + String(flight_info.speed) + "kts " + String(flight_info.track) + "`");
  tft.setCursor(0, tft.getCursorY() + 2);

  // clear();
  // tft.println(String(flight_info.track) + "`");
  // draw_compass((TFT_HEIGHT - TFT_WIDTH) / 2, 0, TFT_WIDTH, TFT_WIDTH, flight_info.track, TFT_LIGHTGREY, TFT_YELLOW);
  // return;

  constexpr auto compass_width = 20;
  draw_compass(TFT_HEIGHT - 28, y, compass_width, compass_width, flight_info.track, TFT_LIGHTGREY, TFT_YELLOW);

  if (airline != nullptr && airline->logo != nullptr)
    tft.pushImage(TFT_HEIGHT - airline->logo->width, tft.getCursorY(), airline->logo->width, airline->logo->height, airline->logo->data);

  tft.setTextFont(font_16pt);
  tft.println(flight_info.registration + " " + format_latitude_longitude(flight_info.latitude, flight_info.longitude));
  tft.setCursor(0, tft.getCursorY() + 4);
  tft.println((aircraft ? String(aircraft->manufacturer) + " " + aircraft->type + " " + aircraft->engine_type : flight_info.type_designator));
  tft.setCursor(0, tft.getCursorY() + 8);

  if (from != nullptr)
  {
    //tft.println(from->name);
    auto cursor_y = tft.getCursorY();
    tft.pushImage(0, cursor_y + flag_margin_y_px, from->flag->width, from->flag->height, from->flag->data);
    tft.setCursor(from->flag->width + flag_margin_x_px, cursor_y);
    tft.println(from->city + String(", ") + from->country);
  }

  tft.setCursor(0, tft.getCursorY() + 2);
  if (to != nullptr)
  {
    //tft.println(to->name);
    auto cursor_y = tft.getCursorY();
    tft.pushImage(0, cursor_y + flag_margin_y_px, to->flag->width, to->flag->height, to->flag->data);
    tft.setCursor(to->flag->width + flag_margin_x_px, cursor_y);
    tft.println(to->city + String(", ") + to->country);
  }
}

unsigned long last_update_flights;
// Time per flight
unsigned long update_flight_milliseconds;
std::list<flight_info> flights;
std::list<flight_info>::const_iterator it;

void loop()
{
  auto now = millis();

  if (WiFi.isConnected())
  {
    if (last_update_flights == 0 || now - last_update_flights > refresh_flights_milliseconds)
    {
      log_i("Updating flights");
      // update flights
      flights = get_flights(center_latitude, center_longitude, range_latitude, range_longitude);
      log_d("Remove flights without flight number");
      flights.remove_if([](const flight_info &f)
                        { return f.flight.isEmpty(); });

      log_i("Number of flights to display: %d", flights.size());
      if (flights.empty())
      {
        log_d("No flights in range");
        clear();
        tft.drawCentreString("No flights in range", TFT_HEIGHT / 2, TFT_WIDTH / 2, font_26pt);
        tft.drawCentreString(format_latitude_longitude(center_longitude, center_latitude), TFT_HEIGHT / 2, TFT_WIDTH / 2 + 26, font_16pt);
        delay(refresh_flights_milliseconds);
        return;
      }

      update_flight_milliseconds = refresh_flights_milliseconds / display_cycles / flights.size();
      log_i("Duration to show each flight: %d milliseconds", update_flight_milliseconds);

      it = flights.begin();
      last_update_flights = now;
    }

    if (it != flights.end())
    {
      display_flight(*it);
      if (++it == flights.end())
      {
        log_d("Restart with first flight");
        it = flights.begin();
      }
    }

    delay(update_flight_milliseconds);
  }
  else
  {
    log_i("Connecting to: %s", wifi_ssid_name);
    // Show Dinosour / cactus image and wait
    tft.pushImage(0, 0, image_no_internet.width, image_no_internet.height, image_no_internet.data);
    // Show for 5 seconds
    delay(5000);
  }
}

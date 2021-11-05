#include <soc/rtc_cntl_reg.h>
#include <SPI.h>
#include <TimeLib.h>

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

#include <time.h>

#include <map>
#include <string>
#include <sstream>

template <typename T>
std::string to_string(const T &t)
{
  std::ostringstream os;
  os << t;
  return os.str();
}

#include <flight_info.h>

// Database of airplanes from https://openflights.org/data.html
#include <aircrafts.h>
#include <airports.h>
#include <airlines.h>
#include <images.h>

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

Timezone timeZone(dst_begin, dst_end);

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
  log_w("Waiting for WiFi connection");
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    log_w("Connection Failed! Rebooting...");
    // Show Dinosour / cactus image, wait an reset
    tft.pushImage(0, 0, image_no_internet.width, image_no_internet.height, image_no_internet.data);
    delay(10000);
    ESP.restart();
  }

  log_i("WiFi connected. IP: %s", WiFi.localIP().toString().c_str());

  // Set the time servers
  configTime(0, 0, ntp_server_1, ntp_server_2, ntp_server_3);

  // Show logo for 2.5 seconds
  delay(2500);
}

void clear()
{
  log_d("Clear screen");
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, background_color);
  tft.setCursor(0, 0);
}

std::string format_degrees(float value)
{
  char buffer[10]; // "DDD°MM.MM"
  int degrees = value;
  int minutes = (value - degrees) * 60;
  int seconds = (value - degrees - minutes / 60.0) * 3600;
  snprintf(buffer, sizeof(buffer), "%d`%02d'%02d\"", degrees, minutes, seconds);
  return buffer;
}

std::string format_lonlat(float lat, char pos, char neg)
{
  return lat >= 0 ? format_degrees(lat) + pos : format_degrees(-lat) + neg;
}

std::string format_gps_location(float lat, float lon)
{
  return format_lonlat(lat, 'N', 'S') + " " + format_lonlat(lon, 'E', 'W');
}

void display_flight(const flight_info &flight_info)
{
  char time_buffer[20];
  strftime(time_buffer, sizeof(time_buffer), "%F %T", localtime(&flight_info.timestamp));
  log_i("Flight info. Seen: %s. ICAO (%06x): %s from %s to %s, Squawk: %04d, Radar: %s, Registration: %s, GPS: %s, Altitude: %d ft, Speed: %d kts, Heading: %d degrees, Type: %s, Operator: %s", time_buffer, flight_info.icao, flight_info.flight.c_str(), flight_info.from.c_str(), flight_info.to.c_str(), flight_info.squawk, flight_info.radar.c_str(), flight_info.registration.c_str(), format_gps_location(flight_info.latitude, flight_info.longitude).c_str(), flight_info.altitude, flight_info.speed, flight_info.track, flight_info.type_designator.c_str(), flight_info.flight_operator.c_str());
  clear();

  auto aircraft = lookupAircraft(flight_info.type_designator.c_str());
  if (aircraft == nullptr)
    log_w("Aircraft (%s) not found", flight_info.type_designator.c_str());

  auto from = lookupAirport(flight_info.from.c_str());
  if (from == nullptr)
    log_w("From airport (%s) not found", flight_info.from.c_str());

  auto to = lookupAirport(flight_info.to.c_str());
  if (to == nullptr)
    log_w("To airport (%s) not found", flight_info.to.c_str());

  auto airline = lookupAirline(flight_info.flight_operator.c_str());
  if (airline == nullptr)
    log_w("Airline (%s) not found", flight_info.flight_operator.c_str());

  tft.setTextFont(font_26pt);

  if (flight_info.flight.length())
    tft.print((flight_info.flight + " ").c_str());

  tft.println((flight_info.from + ">" + flight_info.to).c_str());

  tft.println((to_string(flight_info.altitude) + "ft  " + to_string(flight_info.speed) + "kts " + to_string(flight_info.track) + "`").c_str());
  tft.setCursor(0, tft.getCursorY() + 4);

  if (airline != nullptr)
  {
    log_i("Airline (%s): Callsign: %s. %s - %s. Logo: %s", airline->iata_airline, airline->callsign, airline->name, airline->country, airline->logo ? "present" : "not available");
    if (airline->logo != nullptr)
      tft.pushImage(TFT_HEIGHT - airline->logo->width, tft.getCursorY(), airline->logo->width, airline->logo->height, airline->logo->data);
    else
      log_w("No logo present for airline: %s", airline->iata_airline);
  }

  tft.setTextFont(font_16pt);

  tft.println((flight_info.registration + " " + format_gps_location(flight_info.latitude, flight_info.longitude)).c_str());
  tft.setCursor(0, tft.getCursorY() + 4);
  if (aircraft != nullptr)
  {
    log_i("Aircraft (%s): %s %s. Type: %s, Engine: %s, Number of engines: %c", aircraft->type_designator, aircraft->manufacturer, aircraft->type, aircraft->description, aircraft->engine_type, aircraft->engine_count);
    tft.println((aircraft->manufacturer + std::string(" ") + aircraft->type + " " + aircraft->engine_type + " " + aircraft->engine_count).c_str());
  }
  else
  {
    tft.println(flight_info.type_designator.c_str());
  }

  tft.setCursor(0, tft.getCursorY() + 8);

  if (from != nullptr)
  {
    log_i("From %s: %s - %s (%s) %s", from->iata_airport, from->name, from->city, from->country, format_gps_location(from->lat, from->lon).c_str());
    //tft.println(from->name);
    auto cursor_y = tft.getCursorY();
    tft.pushImage(0, cursor_y + flag_margin_y_px, from->flag->width, from->flag->height, from->flag->data);
    tft.setCursor(from->flag->width + flag_margin_x_px, cursor_y);
    tft.println((from->city + std::string(", ") + from->country).c_str());
  }

  tft.setCursor(0, tft.getCursorY() + 2);
  if (to != nullptr)
  {
    log_i("To %s: %s - %s (%s) %s", to->iata_airport, to->name, to->city, to->country, format_gps_location(to->lat, to->lon).c_str());
    //tft.println(to->name);
    auto cursor_y = tft.getCursorY();
    tft.pushImage(0, cursor_y + flag_margin_y_px, to->flag->width, to->flag->height, to->flag->data);
    tft.setCursor(to->flag->width + flag_margin_x_px, cursor_y);
    tft.println((to->city + std::string(", ") + to->country).c_str());
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
      //log_d("Remove flights without flight number");
      //  flights.remove_if([](const flight_info &f)
      //                  { return f.flight.empty(); });

      log_i("Number of flights to display: %d", flights.size());
      if (flights.empty())
      {
        log_d("No flights in range");
        clear();

        auto now = time(nullptr);
        TimeChangeRule *tcr;
        auto local = timeZone.toLocal(now, &tcr);
        char time_buffer[20];
        strftime(time_buffer, sizeof(time_buffer), "%F   %R", gmtime(&local));
        tft.drawCentreString(time_buffer, TFT_HEIGHT / 2, 0, font_26pt);

        tft.setTextColor(TFT_ORANGE);
        tft.drawCentreString("No flights in range", TFT_HEIGHT / 2, TFT_WIDTH / 2 - 26, font_26pt);
        tft.setTextColor(text_color);
        tft.drawCentreString(format_gps_location(center_latitude, center_longitude).c_str(), TFT_HEIGHT / 2, TFT_WIDTH / 2, font_16pt);

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

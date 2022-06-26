#include <flightradar.h>

#include <SPI.h>
#include <soc/rtc_cntl_reg.h>

#include <ttgo_display.h>

// Settings for the display are defined in platformio.ini
#include <TFT_eSPI.h>
#include <ttgo_backlight.h>

constexpr auto font_16pt = 2;
constexpr auto font_26pt = 4;
constexpr auto font_48pt = 6;
constexpr auto font_48pt_lcd = 7;

#include <Button2.h>
#include <flight_info.h>
#include <time.h>

#include <IotWebConf.h>
#include <IotWebConfOptionalGroup.h>
#include <IotWebConfUsing.h>

// Database of airplanes from https://openflights.org/data.html
#include <aircraft.h>
#include <airline.h>
#include <airport.h>

#include <gps_formatting.h>
#include <images.h>

#include <timezonedb.h>

// Conversions to metric
constexpr float ft_to_m = 0.3048;
constexpr float kts_to_kmh = 1.852f;

// Web server
DNSServer dnsServer;
WebServer server(80);
IotWebConf iotWebConf(WIFI_SSID, &dnsServer, &server, WIFI_PASSWORD, CONFIG_VERSION);

char param_location[32];
char param_latitude[12];
char param_longitude[12];
char param_time_zone[sizeof(timezone_location_t)];
char param_metric[9];

auto param_group_location = IotWebConfParameterGroup("flightradar", "");
auto iotWebParamLocation = IotWebConfTextParameter("Location", "location", param_location, sizeof(param_location), DEFAULT_LOCATION);
auto iotWebParamLatitude = IotWebConfNumberParameter("Latitude", "latitude", param_latitude, sizeof(param_latitude), DEFAULT_LATITUDE, nullptr, "step=\"0.000001\"");
auto iotWebParamLongitude = IotWebConfNumberParameter("Longitude", "longitude", param_longitude, sizeof(param_longitude), DEFAULT_LONGITUDE, nullptr, "step=\"0.00001\"");
auto iotWebParamTimeZone = IotWebConfSelectParameter("Time zone", "time_zone", param_time_zone, sizeof(timezonelocation_t), (const char *)timezonedb, (const char *)timezonedb, sizeof(timezonedb) / sizeof(timezonedb[0]), sizeof(timezonelocation_t), DEFAULT_TIMEZONE);
auto iotWebParamMetric = IotWebConfCheckboxParameter("Metric units", "metric", param_metric, sizeof(param_metric), DEFAULT_METRIC);

// Run time parameters. Are set in connected callback
float latitude;
float longitude;
bool metric_units;

// Screen is 240 * 135 pixels (rotated)
constexpr auto background_color = TFT_BLACK;
constexpr auto text_color = TFT_WHITE;

// Flag
constexpr auto flag_margin_x_px = 4;
constexpr auto flag_margin_y_px = 2;

constexpr auto airline_logo_width_px = 40;
constexpr auto airline_logo_height_px = 40;

// Use hardware SPI
auto tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
auto lcd_backlight_intensity = TTGO_DEFAULT_BACKLIGHT_INTENSITY;

// Buttons
Button2 button1(GPIO_BUTTON_TOP, INPUT);
Button2 button2(GPIO_BUTTON_BOTTOM, INPUT);

// Variables for flight info
unsigned long next_refresh_flights;
unsigned long next_update_flight;
// Time per flight
unsigned long update_flight_milliseconds;
// List of flights
std::list<flight_info> flights;
// Flight to display
std::list<flight_info>::const_iterator it;
// Index
unsigned flight_index;

// Variables for Clock
int last_minute = -1;

typedef enum display_state
{
  display_airtraffic,
  display_time,
  display_info
} display_state_t;

// Current display state
display_state_t display_state = display_state_t::display_airtraffic;

bool time_valid()
{
  // Value of time_t for 2000-01-01 00:00:00, used to detect invalid SNTP responses.
  constexpr time_t epoch_2000_01_01 = 946684800;
  return time(nullptr) > epoch_2000_01_01;
}

void update_runtime_config()
{
  log_v("update_runtime_config");
  // Update runtime configuration
  log_d("Latitude: %s", param_latitude);
  latitude = atof(param_latitude);
  log_d("Longitude: %s", param_longitude);
  longitude = atof(param_longitude);
  log_d("Metric: %s", param_metric);
  metric_units = strlen(param_metric);

  auto tz_definition = timezonedb_get_definition(param_time_zone);
  setenv("TZ", tz_definition, 1);
  tzset();
}

void handleRoot()
{
  log_v("Handle root");
  // Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
    return;

  // Update values
  update_runtime_config();

  struct tm timeinfo;
  getLocalTime(&timeinfo);
  char time_buffer[20];
  if (time_valid())
    strftime(time_buffer, sizeof(time_buffer), "%F %R", &timeinfo);
  else
    strcpy(time_buffer, "Time syncing...");

  String html;
  html += "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  html += "<title>" APP_TITLE " v" APP_VERSION "</title></head>";
  html += "<body>";
  html += "<h2>Status page for " + String(iotWebConf.getThingName()) + "</h2><hr />";
  html += "<ul>";
  html += "<li>Location: " + String(param_location) + "</li>";
  html += "<li>Latitude: " + String(latitude) + " (" + format_lat(latitude).c_str() + ")" + "</li>";
  html += "<li>Longitude: " + String(longitude) + " (" + format_lon(longitude).c_str() + ")" + "</li>";
  html += "<li>Time zone: " + String(param_time_zone) + " (" + timezonedb_get_definition(param_time_zone) + ")" + "</li>";
  html += "<li>Current time: " + String(time_buffer) + "</li>";
  html += "<li>Units: " + String(metric_units ? "Metric" : "Imperial") + "</li>";
  html += "</ul>";
  html += "<br/>Go to <a href=\"config\">configure page</a> to change settings.";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

bool form_validator(iotwebconf::WebRequestWrapper *webRequestWrapper)
{
  log_v("Validating form");
  auto latitude = atof(webRequestWrapper->arg(iotWebParamLatitude.getId()).c_str());
  log_v("Latitude: %f", latitude);
  if (latitude < -90.0 || latitude > 90.0)
  {
    log_e("Latitude out of range [-90, 90]");
    return false;
  }

  auto longitude = atof(webRequestWrapper->arg(iotWebParamLongitude.getId()).c_str());
  log_v("Longitude: %f", longitude);
  if (longitude < -180.0 || longitude > 180.0)
  {
    log_e("Longitude out of range [-180, 180]");
    return false;
  }

  return true;
}

void setup()
{
  // Disable brownout
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  //  ADC_EN is the ADC detection enable port
  //  If the USB port is used for power supply, it is turned on by default.
  //  If it is powered by battery, it needs to be set to high level
  pinMode(GPIO_ADC_EN, OUTPUT);
  digitalWrite(GPIO_ADC_EN, HIGH);

#ifdef CORE_DEBUG_LEVEL
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  // esp_log_level_set("*", ESP_LOG_WARN);
#endif

  log_i("CPU Freq = %d Mhz", getCpuFrequencyMhz());
  log_i("Free heap: %d bytes", ESP.getFreeHeap());
  log_i("Starting " APP_TITLE "...");

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

  // Initializing the configuration for web configuration
  param_group_location.addItem(&iotWebParamLocation);
  param_group_location.addItem(&iotWebParamLatitude);
  param_group_location.addItem(&iotWebParamLongitude);
  param_group_location.addItem(&iotWebParamTimeZone);
  param_group_location.addItem(&iotWebParamMetric);

  iotWebConf.addParameterGroup(&param_group_location);
  iotWebConf.setFormValidator(form_validator);
  iotWebConf.setWifiConnectionCallback(update_runtime_config);
  iotWebConf.setApTimeoutMs(15 * 1000);

  iotWebConf.init();

  // Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/config", []
            { iotWebConf.handleConfig(); });
  server.onNotFound([]()
                    { iotWebConf.handleNotFound(); });

  // Set the time servers
  configTime(0, 0, NTP_SERVERS);
  // Set the timezone
  auto tz_definition = timezonedb_get_definition(param_time_zone);
  setenv("TZ", tz_definition, 1);
  tzset();

  button1.setClickHandler([](Button2 button)
                          {
        log_v("Button 1 clicked");
        switch (display_state) {
        case display_state_t::display_time:
            display_state = display_state_t::display_airtraffic;
            next_refresh_flights = 0;
            break;
        case display_state_t::display_airtraffic:
            display_state = display_state_t::display_time;
            last_minute = -1;
            break;
        } });
}

void clear()
{
  log_d("Clear screen");
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, background_color);
  tft.setCursor(0, 0);
}

void display_flight(const flight_info &flight_info)
{
  log_i("ICAO (%06x): %s from %s to %s, Squawk: %04d, Radar: %s, Registration: %s, GPS: %s, Altitude: %d ft, Speed: %d kts, Heading: %d degrees, Type: %s, Operator: %s", flight_info.icao, flight_info.flight.c_str(), flight_info.from.c_str(), flight_info.to.c_str(), flight_info.squawk, flight_info.radar.c_str(), flight_info.registration.c_str(), format_gps_location(flight_info.latitude, flight_info.longitude).c_str(), flight_info.altitude, flight_info.speed, flight_info.track, flight_info.type_designator.c_str(), flight_info.flight_operator.c_str());
  clear();
  int16_t y = 0;

  const aircraft_t *aircraft = nullptr;
  if (!flight_info.type_designator.isEmpty())
  {
    aircraft = lookupAircraft(flight_info.type_designator.c_str());
    if (aircraft == nullptr)
      log_w("Aircraft (%s) not found", flight_info.type_designator.c_str());
  }

  const airline_t *airline = nullptr;
  if (!flight_info.flight_operator.isEmpty())
  {
    airline = lookupAirline(flight_info.flight_operator.c_str());
    if (airline == nullptr)
      log_w("Airline (%s) not found", flight_info.flight_operator.c_str());
  }

  tft.setTextFont(font_26pt);

  if (flight_info.flight.length())
    tft.print(flight_info.flight + " ");

  tft.print(flight_info.from.c_str());
  tft.println((flight_info.to.isEmpty() ? "" : "-" + flight_info.to).c_str());

  y = tft.getCursorY();
  tft.setCursor(0, tft.getCursorY() + 2);
  if (metric_units)
    tft.println(String(flight_info.altitude * ft_to_m, 0) + "m " + String(flight_info.speed * kts_to_kmh, 0) + "kmh");
  else
    tft.println(String(flight_info.altitude) + "ft " + String(flight_info.speed) + "kts");

  // "`" is displayed as a degree symbol (°) in the font
  tft.drawRightString(String(flight_info.track) + "`", TFT_HEIGHT, y + 5, font_16pt);

  tft.setCursor(0, tft.getCursorY() + 2);

  if (airline)
  {
    log_i("Airline (%s): CallSign: %s. %s - %s. Logo: %s", airline->icao_airline, airline->callsign, airline->name, airline->country->name, airline->logo ? "present" : "not available");
    if (airline->logo)
    {
      auto image = z_image_decode(airline->logo);
      tft.pushImage(TFT_HEIGHT - airline->logo->width, tft.getCursorY(), airline->logo->width, airline->logo->height, image);
      delete[] image;
    }
    else
    {
      log_w("No logo present for airline: %s", airline->icao_airline);
      tft.drawRightString(airline->icao_airline, TFT_HEIGHT, tft.getCursorY(), font_26pt);
    }
  }

  tft.setTextFont(font_16pt);

  if (!flight_info.registration.isEmpty())
    tft.print(String(flight_info.registration) + " ");

  tft.println(format_gps_location(flight_info.latitude, flight_info.longitude));
  tft.setCursor(0, tft.getCursorY() + 4);

  if (aircraft)
  {
    log_i("Aircraft (%s): %s %s. Type: %s, Engine: %s, Number of engines: %c", aircraft->type_designator, aircraft->manufacturer, aircraft->type, aircraft->description, aircraft->engine_type, aircraft->engine_count);
    tft.println(String(aircraft->manufacturer) + " " + aircraft->type);
  }
  else
    tft.println(flight_info.type_designator);

  tft.setCursor(0, tft.getCursorY() + 6);

  if (!flight_info.from.isEmpty())
  {
    auto from = lookupAirport(flight_info.from.c_str());
    if (from)
    {
      log_i("From %s: %s - %s (%s) %s. %s", from->iata_airport, from->name, from->city, from->region, from->country->name, format_gps_location(from->latitude, from->longitude).c_str());
      if (from->country->flag)
      {
        if (from->country->flag)
        {
          auto cursor_y = tft.getCursorY();
          auto image = z_image_decode(from->country->flag);
          tft.pushImage(0, cursor_y + flag_margin_y_px, from->country->flag->width, from->country->flag->height, image);
          delete[] image;
          tft.setCursor(from->country->flag->width + flag_margin_x_px, cursor_y);
        }
      }

      tft.println(String(from->city) + " (" + from->region + ") " + from->country->name);
    }
    else
      log_w("From airport (%s) not found", flight_info.from.c_str());

    tft.setCursor(0, tft.getCursorY() + 2);
  }

  if (!flight_info.to.isEmpty())
  {
    auto to = lookupAirport(flight_info.to.c_str());
    if (to)
    {
      log_i("To %s: %s - %s (%s) %s. %s", to->iata_airport, to->name, to->city, to->region, to->country->name, format_gps_location(to->latitude, to->longitude).c_str());
      if (to->country)
      {
        if (to->country->flag)
        {
          auto cursor_y = tft.getCursorY();
          auto image = z_image_decode(to->country->flag);
          tft.pushImage(0, cursor_y + flag_margin_y_px, to->country->flag->width, to->country->flag->height, image);
          delete[] image;
          tft.setCursor(to->country->flag->width + flag_margin_x_px, cursor_y);
        }
      }

      tft.println(String(to->city) + " (" + to->region + ") " + to->country->name);
    }
    else
      log_w("To airport (%s) not found", flight_info.to.c_str());
  }
}

void display_network_state(iotwebconf::NetworkState state)
{
  log_i("Network state: %d", state);
  unsigned short *image_data;
  switch (state)
  {
  case iotwebconf::NotConfigured:
  case iotwebconf::ApMode:
    // Show WiFi AP screen
    image_data = z_image_decode(&image_wifi);
    tft.pushImage(0, 0, image_wifi.width, image_wifi.height, image_data);
    delete[] image_data;
    tft.drawCentreString(state == iotwebconf::NotConfigured ? "No config. Connect to SSID:" : "To configure, connect to SSID:", TFT_HEIGHT / 2, TFT_WIDTH - 42, font_16pt);
    tft.drawCentreString(iotWebConf.getThingName(), TFT_HEIGHT / 2, TFT_WIDTH - 26, font_26pt);
    break;
  case iotwebconf::Connecting:
    // Show splash screen
    image_data = z_image_decode(&image_splash);
    tft.pushImage(0, 0, image_splash.width, image_splash.height, image_data);
    delete[] image_data;
    tft.setTextFont(font_26pt);
    tft.print(APP_TITLE " v" APP_VERSION);
    break;
  case iotwebconf::OffLine:
    // Show Dinosaur / cactus image
    image_data = z_image_decode(&image_no_internet);
    tft.pushImage(0, 0, image_no_internet.width, image_no_internet.height, image_data);
    delete[] image_data;
    break;
  }
}

void display_flights()
{
  auto now = millis();
  if (now > next_refresh_flights)
  {
    next_refresh_flights = now + refresh_flights_milliseconds;
    log_i("Updating flights");
    flights = get_flights(atof(param_latitude), atof(param_longitude), range_latitude, range_longitude);
    log_i("Number of flights: %d", flights.size());

    if (flights.empty())
    {
      log_d("No flights in range");
      clear();

      struct tm timeinfo;
      getLocalTime(&timeinfo);
      char time_buffer[20];
      if (time_valid())
        strftime(time_buffer, sizeof(time_buffer), "%F %R", &timeinfo);
      else
        strcpy(time_buffer, "Time syncing...");

      tft.drawCentreString(time_buffer, TFT_HEIGHT / 2, 0, font_26pt);

      tft.setTextColor(TFT_ORANGE);
      tft.drawCentreString("No flights in range", TFT_HEIGHT / 2, TFT_WIDTH / 2 - 26, font_26pt);

      tft.setTextColor(text_color);
      tft.drawCentreString(format_gps_location(atof(param_latitude), atof(param_longitude)), TFT_HEIGHT / 2, TFT_WIDTH / 2, font_16pt);

      tft.drawCentreString(param_location, TFT_HEIGHT / 2, TFT_WIDTH - 32, font_16pt);
      tft.drawCentreString(param_time_zone, TFT_HEIGHT / 2, TFT_WIDTH - 16, font_16pt);

      next_update_flight = UINT_MAX;
    }
    else
    {
      update_flight_milliseconds = refresh_flights_milliseconds / display_cycles / flights.size();
      log_i("Duration to show each flight: %d milliseconds", update_flight_milliseconds);

      next_update_flight = 0ul;
      it = flights.begin();
      flight_index = 0;
    }
  }

  if (now > next_update_flight)
  {
    next_update_flight = now + update_flight_milliseconds;

    if (it != flights.end())
    {
      display_flight(*it);
      // Show index of displayed and total of flights
      tft.drawRightString(String(++flight_index) + "/" + String(flights.size()), TFT_HEIGHT, 0, font_16pt);
      if (++it == flights.end())
      {
        log_d("Restart with first flight");
        it = flights.begin();
        flight_index = 0;
      }
    }
  }
}

void display_clock()
{
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  if (timeinfo.tm_min != last_minute)
  {
    clear();
    last_minute = timeinfo.tm_min;
    log_i("Updating clock");
    if (time_valid())
    {
      char time_buffer[20];
      strftime(time_buffer, sizeof(time_buffer), "%F", &timeinfo);
      tft.drawCentreString(time_buffer, TFT_HEIGHT / 2, 0, font_26pt);
      strftime(time_buffer, sizeof(time_buffer), "%R", &timeinfo);
      tft.drawCentreString(time_buffer, TFT_HEIGHT / 2, TFT_WIDTH / 2 - 24, font_48pt_lcd);
      tft.drawCentreString(param_time_zone, TFT_HEIGHT / 2, TFT_WIDTH - 16, font_16pt);
    }
    else
      tft.drawCentreString("Time syncing...", TFT_HEIGHT / 2, TFT_WIDTH / 2 - 13, font_26pt);
  }
}

void loop()
{
  button1.loop();
  button2.loop();
  iotWebConf.doLoop();

  static auto last_network_state = iotwebconf::NetworkState::Boot;

  auto network_state = iotWebConf.getState();
  if (network_state != last_network_state)
  {
    last_network_state = network_state;
    display_network_state(network_state);
  }

  switch (network_state)
  {
  case iotwebconf::NetworkState::OffLine:
    next_refresh_flights = 0ul;
    break;

  case iotwebconf::NetworkState::OnLine:
    switch (display_state)
    {
    case display_state_t::display_airtraffic:
      display_flights();
      break;
    case display_state_t::display_time:
      display_clock();
      break;
    }
    break;
  }

  yield();
}
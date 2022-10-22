#include <settings.h>

#include <SPI.h>
#include <soc/rtc_cntl_reg.h>

#include <ttgo_display.h>

// Settings for the display are defined in platformio.ini
#include <TFT_eSPI.h>
#include <lvgl.h>

constexpr auto font_16pt = 2;
constexpr auto font_26pt = 4;
constexpr auto font_48pt = 6;
constexpr auto font_48pt_lcd = 7;

#include <Button2.h>
#include <flight_info.h>
#include <time.h>

#include <ESPmDNS.h>
#include <IotWebConf.h>
#include <IotWebConfTParameter.h>

#include <moustache.h>
#include <format_gps.h>
#include <format_number.h>
#include <format_duration.h>

#include <images.h>
#include <timezonedb_lookup.h>

#include <html_data.h>
#include <html_data_gzip.h>

// Web server
DNSServer dnsServer;
WebServer server(80);
IotWebConf iotWebConf(WIFI_SSID, &dnsServer, &server, WIFI_PASSWORD, CONFIG_VERSION);

auto param_group = iotwebconf::ParameterGroup("flightradar", "Flight radar");
auto iotWebParamLocation = iotwebconf::Builder<iotwebconf::TextTParameter<32>>("location").label("Location").defaultValue(DEFAULT_LOCATION).build();
auto iotWebParamLatitude = iotwebconf::Builder<iotwebconf::FloatTParameter>("lat").label("Latitude").min(-90.0).max(90.0).defaultValue(DEFAULT_LATITUDE).step(0.01).placeholder("e.g. 52.3").build();
auto iotWebParamLongitude = iotwebconf::Builder<iotwebconf::FloatTParameter>("lon").label("Longitude").min(-180.0).max(180.0).defaultValue(DEFAULT_LONGITUDE).step(0.01).placeholder("e.g. 4.76").build();
auto iotWebParamLatitudeRange = iotwebconf::Builder<iotwebconf::FloatTParameter>("lat_range").label("Latitude range (degrees)").defaultValue(DEFAULT_RANGE_LATITUDE).step(0.01).placeholder("e.g. 0.1").build();
auto iotWebParamLongitudeRange = iotwebconf::Builder<iotwebconf::FloatTParameter>("lon_range").label("Longitude range (degrees)").defaultValue(DEFAULT_RANGE_LONGITUDE).step(0.01).placeholder("e.g. 0.1").build();
auto iotWebParamAirborne = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("air").label("Include airborne").defaultValue(DEFAULT_AIR).build();
auto iotWebParamGrounded = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("ground").label("Include grounded").defaultValue(DEFAULT_GROUND).build();
auto iotWebParamGliders = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("gliders").label("Include gliders").defaultValue(DEFAULT_GLIDERS).build();
auto iotWebParamVehicles = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("vehicles").label("Include vehicles").defaultValue(DEFAULT_VEHICLES).build();
auto iotWebParamTimeZone = iotwebconf::Builder<iotwebconf::SelectTParameter<sizeof(posix_timezone_names[0])>>("timezone").label("Choose timezone").optionValues((const char *)&posix_timezone_names).optionNames((const char *)&posix_timezone_names).optionCount(sizeof(posix_timezone_names) / sizeof(posix_timezone_names[0])).nameLength(sizeof(posix_timezone_names[0])).defaultValue(DEFAULT_TIMEZONE).build();
auto iotWebParamMetric = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("metric").label("Use metric units").defaultValue(DEFAULT_METRIC).build();

// Screen is 240 * 135 pixels (rotated)
constexpr auto background_color = TFT_BLACK;
constexpr auto text_color = TFT_WHITE;
constexpr auto special_text_color = TFT_RED;

// Flag
constexpr auto flag_margin_x_px = 4;
constexpr auto flag_margin_y_px = 2;

constexpr auto airline_logo_width_px = 40;
constexpr auto airline_logo_height_px = 40;

// Use hardware SPI
auto tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

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

void send_content_gzip(const unsigned char *content, size_t length, const char *mime_type)
{
  server.sendHeader("Content-encoding", "gzip");
  server.setContentLength(length);
  server.send(200, mime_type, "");
  server.sendContent(reinterpret_cast<const char *>(content), length);
}

bool time_valid()
{
  // Value of time_t for 2000-01-01 00:00:00, used to detect invalid SNTP responses.
  constexpr time_t epoch_2000_01_01 = 946684800;
  return time(nullptr) > epoch_2000_01_01;
}

String get_localtime(const char *format)
{
  if (!time_valid())
    return "No time available";

  struct tm timeinfo;
  getLocalTime(&timeinfo);
  char time_buffer[32];
  strftime(time_buffer, sizeof(time_buffer), format, &timeinfo);
  return time_buffer;
}

void update_runtime_config()
{
  log_v("update_runtime_config");
  auto tz = lookup_posix_timezone_tz(iotWebParamTimeZone.value());
  if (tz != nullptr)
  {
    setenv("TZ", tz, 1);
    tzset();
    log_i("Set timezone to %s (%s)", iotWebParamTimeZone.value(), tz);
  }
  else
    log_e("Timezone %s not found!", iotWebParamTimeZone.value());
}

void handleRoot()
{
  log_v("Handle root");
  // Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
    return;

  auto tz = lookup_posix_timezone_tz(iotWebParamTimeZone.value());
  if (tz == nullptr)
  {
    log_e("Timezone %s not found!", iotWebParamTimeZone.value());
    tz = "Unknown";
  }

  auto localtime = get_localtime("%F, %T");

  // Format hostname
  auto hostname = "esp32-" + WiFi.macAddress() + ".local";
  hostname.replace(":", "");
  hostname.toLowerCase();

  // Wifi Modes
  const char *wifi_modes[] = {"NULL", "STA", "AP", "STA+AP"};

  // Location; format degree symbol
  auto html_location = format_gps_location(iotWebParamLatitude.value(), iotWebParamLongitude.value());
  html_location.replace("`", "&deg;");

  // Calculations for range
  auto latRange = String(iotWebParamLatitudeRange.value()) + "&deg; (" + (iotWebParamMetric.value() ? String(iotWebParamLatitudeRange.value() * DEGREES_TO_KM) + " km" : String(iotWebParamLatitudeRange.value() * DEGREES_TO_MI) + " mi") + ")";
  auto lonRange = String(iotWebParamLongitudeRange.value()) + "&deg; (" + (iotWebParamMetric.value() ? String(iotWebParamLongitudeRange.value() * DEGREES_TO_KM) + " km" : String(iotWebParamLongitudeRange.value() * DEGREES_TO_MI) + " mi") + ")";

  const moustache_variable_t substitutions[] = {
      // Version / CPU
      {"AppTitle", APP_TITLE},
      {"AppVersion", APP_VERSION},
      {"ThingName", iotWebConf.getThingName()},
      {"ChipModel", ESP.getChipModel()},
      {"ChipRevision", String(ESP.getChipRevision())},
      {"CpuFreqMHz", String(ESP.getCpuFreqMHz())},
      {"CpuCores", String(ESP.getChipCores())},
      {"FlashSize", format_memory(ESP.getFlashChipSize(), 0)},
      {"HeapSize", format_memory(ESP.getHeapSize())},
      // Diagnostics
      {"Uptime", String(format_duration(millis() / 1000))},
      {"FreeHeap", format_memory(ESP.getFreeHeap())},
      {"MaxAllocHeap", format_memory(ESP.getMaxAllocHeap())},
      {"LocalTime", localtime},
      // Network
      {"HostName", hostname},
      {"MacAddress", WiFi.macAddress()},
      {"AccessPoint", WiFi.SSID()},
      {"SignalStrength", String(WiFi.RSSI())},
      {"IpV4", WiFi.localIP().toString()},
      {"IpV6", WiFi.localIPv6().toString()},
      {"WifiMode", wifi_modes[WiFi.getMode()]},
      {"NetworkState.ApMode", String(iotWebConf.getState() == iotwebconf::NetworkState::ApMode)},
      {"NetworkState.OnLine", String(iotWebConf.getState() == iotwebconf::NetworkState::OnLine)},
      // Settings
      {"Location", iotWebParamLocation.value()},
      {"Lat", String(iotWebParamLatitude.value())},
      {"Lon", String(iotWebParamLongitude.value())},
      {"LatLon", html_location},
      {"LatLongRanges", latRange + " / " + lonRange},
      {"Airborne", iotWebParamAirborne.value() ? "Yes" : "No"},
      {"Grounded", iotWebParamGrounded.value() ? "Yes" : "No"},
      {"Gliders", iotWebParamGliders.value() ? "Yes" : "No"},
      {"Vehicles", iotWebParamVehicles.value() ? "Yes" : "No"},
      {"Timezone", iotWebParamTimeZone.value()},
      {"TZ", tz},
      {"Units", iotWebParamMetric.value() ? "Metric" : "Imperial"}};

  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  auto html = moustache_render(file_data_index_html, substitutions);
  server.send(200, "text/html", html);
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  auto w = (area->x2 - area->x1 + 1);
  auto h = (area->y2 - area->y1 + 1);
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

void xlv_log(const char *buf)
{
  log_printf("%s", buf);
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

  log_i("CPU Freq = %d Mhz", getCpuFrequencyMhz());
  log_i("Free heap: %d bytes", ESP.getFreeHeap());
  log_i("Starting " APP_TITLE "...");

  // Start LVGL
  log_i("LVGL version: %d.%d.%d ", lv_version_major(), lv_version_minor(), lv_version_patch());
  lv_init();
  tft.begin();
  // Rotate 90 degrees to Landscape
  tft.setRotation(1);
  // Width and height are flipped because is rotated 90 degrees
  const uint16_t screen_width = TFT_HEIGHT;
  const uint16_t screen_height = TFT_WIDTH;

  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf[screen_width * 10];
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screen_width * 10);

  // Initialize the display
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screen_width;
  disp_drv.ver_res = screen_height;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  lv_log_register_print_cb(&xlv_log);

  /*
    // Show WiFi AP screen
    lv_img_dsc_t img_dsc = {
        .header = {
            .cf = LV_IMG_CF_RGB565,
            .w = image_wifi.width,
            .h = image_wifi.height,
        },
        .data_size = image_wifi.width * image_wifi.height * LV_COLOR_SIZE / 4,
        .data = (const uint8_t *)z_image_decode(&image_wifi)};

    auto image = lv_img_create(lv_scr_act());
    lv_img_set_src(image, &img_dsc);
  */
  // Initializing the configuration for web configuration
  param_group.addItem(&iotWebParamLocation);
  param_group.addItem(&iotWebParamLatitude);
  param_group.addItem(&iotWebParamLongitude);
  param_group.addItem(&iotWebParamLatitudeRange);
  param_group.addItem(&iotWebParamLongitudeRange);
  param_group.addItem(&iotWebParamAirborne);
  param_group.addItem(&iotWebParamGrounded);
  param_group.addItem(&iotWebParamGliders);
  param_group.addItem(&iotWebParamVehicles);
  param_group.addItem(&iotWebParamTimeZone);
  param_group.addItem(&iotWebParamMetric);
  iotWebConf.addParameterGroup(&param_group);

  iotWebConf.getApTimeoutParameter()->visible = true;
  iotWebConf.setWifiConnectionCallback(update_runtime_config);
  // Set an IO pin (Top button) to reset config when pressed at boot
  iotWebConf.setConfigPin(GPIO_BUTTON_TOP);

  iotWebConf.init();

  // Set up required URL handlers on the web server.
  server.on("/", HTTP_GET, handleRoot);
  server.on("/config", []
            { iotWebConf.handleConfig(); });

  // bootstrap
  server.on("/bootstrap.min.css", HTTP_GET, []()
            {
              // Cache for 86400 seconds (one day)
              server.sendHeader("Cache-Control", "max-age=86400");
              send_content_gzip(file_data_bootstrap_min_css, sizeof(file_data_bootstrap_min_css), "text/css"); });

  server.onNotFound([]()
                    { iotWebConf.handleNotFound(); });

  // Set the time servers
  configTime(0, 0, NTP_SERVERS);
  // Set the timezone
  auto tz = lookup_posix_timezone_tz(iotWebParamTimeZone.value());
  if (tz != nullptr)
  {
    setenv("TZ", tz, 1);
    tzset();
    log_i("Set timezone to %s (%s)", iotWebParamTimeZone.value(), tz);
  }
  else
    log_e("Timezone %s not found!", iotWebParamTimeZone.value());

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

void display_flight(const std::list<flight_info> flights, const flight_info &flight_info)
{
  log_i("%s", flight_info.toString().c_str());
  // clear();
  lv_obj_clean(lv_scr_act());

  const aircraft_t *aircraft = flight_info.aircraft_type();
  if (aircraft == nullptr)
    log_w("Aircraft (%s) not found", flight_info.aircraft_code.c_str());

  const airline_t *airline = flight_info.airline();
  if (airline == nullptr)
    log_w("Airline (%s) not found", flight_info.icao_airline.c_str());

  // tft.setTextFont(font_26pt);

  // Special color if squawk is special code
  //  if (flight_info.squawk_hijack() || flight_info.squawk_radio_failure() || flight_info.squawk_emergency())
  //    tft.setTextColor(special_text_color);
  auto label_flight = lv_label_create(lv_scr_act());
  lv_label_set_text(label_flight, flight_info.flight.c_str());
  lv_obj_align(label_flight, LV_ALIGN_TOP_LEFT, 0, 0);
  // Special color if squawk is special code
  if (flight_info.squawk_hijack() || flight_info.squawk_radio_failure() || flight_info.squawk_emergency())
    lv_obj_set_style_text_color(label_flight, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);

  //  if (flight_info.flight.length())
  //    tft.print(flight_info.flight + " ");

  // tft.setTextColor(text_color);

  auto label_from_to = lv_label_create(lv_scr_act());
  lv_label_set_text(label_from_to, (flight_info.iata_origin_airport + "-" + flight_info.iata_destination_airport).c_str());
  lv_obj_align(label_from_to, LV_ALIGN_TOP_MID, 0, 0);

  //  tft.print(flight_info.iata_origin_airport);
  //  tft.println(flight_info.iata_destination_airport.isEmpty() ? "" : "-" + flight_info.iata_destination_airport);

  auto label_heading = lv_label_create(lv_scr_act());
  lv_label_set_text(label_heading, String(flight_info.heading).c_str());
  lv_obj_align(label_heading, LV_ALIGN_TOP_RIGHT, 0, 0);

  // "`" is displayed as a degree symbol (°) in the font
  // tft.drawRightString(String(flight_info.heading) + "`", TFT_HEIGHT, tft.getCursorY() + 5, font_16pt);

  // tft.setCursor(0, tft.getCursorY() + 2);
  //  Altitude
  auto label_altitude = lv_label_create(lv_scr_act());
  lv_label_set_text(label_altitude, (iotWebParamMetric.value() ? (String(flight_info.altitude_metric()) + "m ") : (String(flight_info.altitude) + "ft ")).c_str());
  lv_obj_align(label_altitude, LV_ALIGN_TOP_RIGHT, 0, 0);
  /*
    // if (iotWebParamMetric.value()
    //   tft.print(String(flight_info.altitude_metric()) + "m ");
    // else
    //   tft.print(String(flight_info.altitude) + "ft ");

    // Steady, Descending / Ascending
    // tft.print(flight_info.vertical_speed == 0 ? "= " : flight_info.vertical_speed < 0 ? "- "
                                                                                      : "+ ");

                                                                                        if (iotWebParamMetric.value())
                                                                                          tft.println(String(flight_info.ground_speed_metric()) + "kmh");
                                                                                        else
                                                                                          tft.println(String(flight_info.ground_speed) + "kts");

                                                                                        tft.setCursor(0, tft.getCursorY() + 2);

                                                                                        if (airline)
                                                                                        {
                                                                                          log_i("Airline (%s): CallSign: %s. %s - %s. Logo: %s", airline->icao_airline, airline->call_sign, airline->name, airline->country->name, airline->logo.data ? "present" : "not available");
                                                                                          if (airline->logo.data)
                                                                                          {
                                                                                            // auto image = z_image_decode(airline->logo);
                                                                                            // tft.pushImage(TFT_HEIGHT - airline->logo->width, tft.getCursorY(), airline->logo->width, airline->logo->height, image);
                                                                                            // delete[] image;
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
                                                                                          log_i("Aircraft (%s): %s %s. Description: %s, Engine: %s, Number of engines: %c", aircraft->aircraft_code, aircraft->manufacturer, aircraft->type, aircraft->description, aircraft->engine_type, aircraft->engine_count);
                                                                                          tft.println(String(aircraft->manufacturer) + " " + String(aircraft->type));
                                                                                        }
                                                                                        else
                                                                                          tft.println(flight_info.aircraft_code);

                                                                                        tft.setCursor(0, tft.getCursorY() + 6);

                                                                                        auto iata_origin = flight_info.origin_airport();
                                                                                        if (iata_origin)
                                                                                        {
                                                                                          log_i("From %s: %s - %s (%s) %s. %s", iata_origin->iata_airport, iata_origin->name, iata_origin->city, iata_origin->region, iata_origin->country->name, format_gps_location(iata_origin->latitude, iata_origin->longitude).c_str());
                                                                                          if (iata_origin->country)
                                                                                          {
                                                                                            if (iata_origin->country->flag.data)
                                                                                            {
                                                                                              auto cursor_y = tft.getCursorY();
                                                                                              // auto image = z_image_decode(iata_origin->country->flag);
                                                                                              // tft.pushImage(0, cursor_y + flag_margin_y_px, iata_origin->country->flag->width, iata_origin->country->flag->height, image);
                                                                                              // delete[] image;
                                                                                              // tft.setCursor(iata_origin->country->flag->width + flag_margin_x_px, cursor_y);
                                                                                            }
                                                                                          }

                                                                                          tft.println(String(iata_origin->city) + " (" + iata_origin->region + ") " + iata_origin->country->name);
                                                                                        }
                                                                                        else
                                                                                          log_w("From airport (%s) not found", flight_info.iata_origin_airport.c_str());

                                                                                        tft.setCursor(0, tft.getCursorY() + 2);

                                                                                        auto iata_destination = flight_info.destination_airport();
                                                                                        if (iata_destination)
                                                                                        {
                                                                                          log_i("To %s: %s - %s (%s) %s. %s", iata_destination->iata_airport, iata_destination->name, iata_destination->city, iata_destination->region, iata_destination->country->name, format_gps_location(iata_destination->latitude, iata_destination->longitude).c_str());
                                                                                          if (iata_destination->country)
                                                                                          {
                                                                                            if (iata_destination->country->flag.data)
                                                                                            {
                                                                                              auto cursor_y = tft.getCursorY();
                                                                                              // auto image = z_image_decode(iata_destination->country->flag);
                                                                                              // tft.pushImage(0, cursor_y + flag_margin_y_px, iata_destination->country->flag->width, iata_destination->country->flag->height, image);
                                                                                              // delete[] image;
                                                                                              // tft.setCursor(iata_destination->country->flag->width + flag_margin_x_px, cursor_y);
                                                                                            }
                                                                                          }

                                                                                          tft.println(String(iata_destination->city) + " (" + iata_destination->region + ") " + iata_destination->country->name);
                                                                                        }
                                                                                        else
                                                                                          log_w("To airport (%s) not found", flight_info.iata_destination_airport.c_str());
                                                                                        */
}

void display_network_state(iotwebconf::NetworkState state)
{
  log_i("Network state: %d", state);
  // unsigned short *image_data;
  switch (state)
  {
  case iotwebconf::NotConfigured:
  case iotwebconf::ApMode:
  {
    lv_obj_clean(lv_scr_act());
    auto image = lv_img_create(lv_scr_act());
    lv_img_set_src(image, &image_wifi);
    auto label_state = lv_label_create(lv_scr_act());
    lv_label_set_text(label_state, "Access point mode");
    lv_obj_align(label_state, LV_ALIGN_TOP_MID, 0, 0);
    auto label_message = lv_label_create(lv_scr_act());
    auto message = String(state == iotwebconf::NotConfigured ? "No config" : "To configure") + ", connect to SSID:";
    lv_label_set_text(label_message, message.c_str());
    lv_obj_align(label_message, LV_ALIGN_BOTTOM_MID, 0, -16);
    auto label_ssid = lv_label_create(lv_scr_act());
    lv_label_set_text(label_ssid, iotWebConf.getThingName());
    lv_obj_align(label_ssid, LV_ALIGN_BOTTOM_MID, 0, 0);
  }

    if (false)
    {
      lv_obj_clean(lv_scr_act());
      auto preload = lv_spinner_create(lv_scr_act(), 1000, 50);
      lv_obj_align(preload, LV_ALIGN_CENTER, 0, 0);
      auto label_state = lv_label_create(lv_scr_act());
      lv_label_set_text(label_state, "Access point mode");
      lv_obj_align(label_state, LV_ALIGN_TOP_MID, 0, 0);
      auto label_message = lv_label_create(lv_scr_act());
      auto message = String(state == iotwebconf::NotConfigured ? "No config" : "To configure") + ", connect to SSID:\n" + String(iotWebConf.getThingName());
      lv_label_set_text(label_message, message.c_str());
      lv_obj_align(label_message, LV_ALIGN_BOTTOM_MID, 0, 0);
    }
    /*
      // Show WiFi AP screen
      image_data = z_image_decode(&image_wifi);
      tft.pushImage(0, 0, image_wifi.width, image_wifi.height, image_data);
      delete[] image_data;
      tft.drawCentreString(state == iotwebconf::NotConfigured ? "No config. Connect to SSID:" : "To configure, connect to SSID:", TFT_HEIGHT / 2, TFT_WIDTH - 42, font_16pt);
      tft.drawCentreString(iotWebConf.getThingName(), TFT_HEIGHT / 2, TFT_WIDTH - 26, font_26pt);
      */
    break;
  case iotwebconf::Connecting:
  {
    lv_obj_clean(lv_scr_act());
    auto image = lv_img_create(lv_scr_act());
    lv_img_set_src(image, &image_splash);
    auto label_version = lv_label_create(lv_scr_act());
    lv_label_set_text(label_version, APP_TITLE " v" APP_VERSION);
    lv_obj_align(label_version, LV_ALIGN_TOP_MID, 0, 0);
  }
  // lv_msgbox_create(lv_scr_act(), "Connecting to", iotWebConf.getThingName(), nullptr, false);

  /*
    // Show splash screen
    image_data = z_image_decode(&image_splash);
    tft.pushImage(0, 0, image_splash.width, image_splash.height, image_data);
    delete[] image_data;
    tft.setCursor(0, 0);
    tft.setTextFont(font_26pt);
    tft.print(APP_TITLE " v" APP_VERSION);
    */
  break;
  case iotwebconf::OffLine:
  {
    lv_obj_clean(lv_scr_act());
    auto image = lv_img_create(lv_scr_act());
    lv_img_set_src(image, &image_no_internet);
  }

  /*
    // Show Dinosaur / cactus image
    image_data = z_image_decode(&image_no_internet);
    tft.pushImage(0, 0, image_no_internet.width, image_no_internet.height, image_data);
    delete[] image_data;
    */
  break;
  }
}

void display_flights()
{
  auto now = millis();
  if (now > next_refresh_flights)
  {
    lv_obj_clean(lv_scr_act());

    next_refresh_flights = now + refresh_flights_milliseconds;
    log_i("Updating flights");
    String error_message;
    if (!get_flights(iotWebParamLatitude.value(), iotWebParamLongitude.value(), iotWebParamLatitudeRange.value(), iotWebParamLongitudeRange.value(), iotWebParamAirborne.value(), iotWebParamGrounded.value(), iotWebParamGliders.value(), iotWebParamVehicles.value(), flights, error_message))
    {
      log_e("Error getting flights: %s", error_message.c_str());
      auto image = lv_img_create(lv_scr_act());
      lv_img_set_src(image, &image_error);
      auto label_message = lv_label_create(lv_scr_act());
      lv_label_set_text(label_message, error_message.c_str());
      lv_obj_align(label_message, LV_ALIGN_BOTTOM_MID, 0, 0);
      // Show error message
      // clear();
      //      auto image_data = z_image_decode(&image_error);
      //      tft.pushImage(0, 0, image_error.width, image_error.height, image_data);
      //      delete[] image_data;
      // tft.drawCentreString(error_message, TFT_HEIGHT / 2, TFT_WIDTH - 16, font_16pt);
      next_update_flight = UINT_MAX;
      return;
    }

    log_i("Number of flights: %d", flights.size());

    if (flights.empty())
    {
      log_d("No flights in range");
      auto label_message = lv_label_create(lv_scr_act());
      lv_label_set_text(label_message, "No flights in range");
      lv_obj_align(label_message, LV_ALIGN_TOP_MID, 0, 0);
      auto label_time = lv_label_create(lv_scr_act());
      lv_label_set_text(label_time, get_localtime("%F %R").c_str());
      lv_obj_align(label_time, LV_ALIGN_CENTER, 0, 0);
      auto label_latlon = lv_label_create(lv_scr_act());
      lv_label_set_text(label_latlon, format_gps_location(iotWebParamLatitude.value(), iotWebParamLongitude.value()).c_str());
      lv_obj_align(label_latlon, LV_ALIGN_CENTER, 0, 16);
      auto label_location = lv_label_create(lv_scr_act());
      lv_label_set_text(label_location, iotWebParamLocation.value());
      lv_obj_align(label_location, LV_ALIGN_BOTTOM_MID, 0, -16);
      auto label_timezone = lv_label_create(lv_scr_act());
      lv_label_set_text(label_timezone, iotWebParamTimeZone.value());
      lv_obj_align(label_timezone, LV_ALIGN_BOTTOM_MID, 0, 0);

      // clear();
      // auto localtime = get_localtime("%F %R");
      // tft.drawCentreString(localtime, TFT_HEIGHT / 2, 0, font_26pt);
      // tft.setTextColor(TFT_ORANGE);
      // tft.drawCentreString("No flights in range", TFT_HEIGHT / 2, TFT_WIDTH / 2 - 26, font_26pt);

      // tft.setTextColor(text_color);
      // tft.drawCentreString(format_gps_location(iotWebParamLatitude.value(), iotWebParamLongitude.value()), TFT_HEIGHT / 2, TFT_WIDTH / 2, font_16pt);

      // tft.drawCentreString(iotWebParamLocation.value(), TFT_HEIGHT / 2, TFT_WIDTH - 32, font_16pt);
      // tft.drawCentreString(iotWebParamTimeZone.value(), TFT_HEIGHT / 2, TFT_WIDTH - 16, font_16pt);

      next_update_flight = UINT_MAX;
      return;
    }

    update_flight_milliseconds = refresh_flights_milliseconds / display_cycles / flights.size();
    log_i("Duration to show each flight: %d milliseconds", update_flight_milliseconds);

    next_update_flight = 0ul;
    it = flights.begin();
    flight_index = 0;
  }

  if (now > next_update_flight)
  {
    next_update_flight = now + update_flight_milliseconds;

    if (it != flights.end())
    {
      display_flight(flights, *it);
      flight_index++;
      // Show index of displayed and total of flights
      // tft.drawRightString(String(flight_index) + "/" + String(flights.size()), TFT_HEIGHT, 0, font_16pt);

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
      tft.drawCentreString(get_localtime("%F"), TFT_HEIGHT / 2, 0, font_26pt);
      tft.drawCentreString(get_localtime("%R"), TFT_HEIGHT / 2, TFT_WIDTH / 2 - 24, font_48pt_lcd);
      tft.drawCentreString(iotWebParamTimeZone.value(), TFT_HEIGHT / 2, TFT_WIDTH - 16, font_16pt);
    }
  }
}

void loop()
{
  // LVGL
  lv_timer_handler();

  // Button
  button1.loop();
  button2.loop();

  // Web configuration
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
}
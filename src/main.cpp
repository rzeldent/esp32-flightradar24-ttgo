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

// Use hardware SPI
auto tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

// Buttons
Button2 button1(GPIO_BUTTON_TOP, INPUT);
Button2 button2(GPIO_BUTTON_BOTTOM, INPUT);

// Variables for flight info
unsigned long next_update;
// List of flights
std::list<flight_info> flights;
// Flight to display
std::list<flight_info>::const_iterator it = flights.begin();
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

  // Format hostname
  auto hostname = "esp32-" + WiFi.macAddress() + ".local";
  hostname.replace(":", "");
  hostname.toLowerCase();

  // Wifi Modes
  const char *wifi_modes[] = {"NULL", "STA", "AP", "STA+AP"};

  // Location; format degree symbol
  auto html_location = format_gps_location(iotWebParamLatitude.value(), iotWebParamLongitude.value());
  html_location.replace("\u00b0", "&deg;");

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
      {"LocalTime", get_localtime("%F - %T")},
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
  tft.initDMA(true);
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

  // For debugging
  lv_log_register_print_cb(&xlv_log);

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
            next_update = 0;
            break;
        case display_state_t::display_airtraffic:
            display_state = display_state_t::display_time;
            last_minute = -1;
            break;
        } });
}

void display_flight(const flight_info &flight_info, int index, int total)
{
  log_i("%s", flight_info.toString().c_str());
  lv_obj_clean(lv_scr_act());

  const auto aircraft = flight_info.aircraft_type();
  if (aircraft == nullptr)
    log_w("Aircraft (%s) not found", flight_info.aircraft_code.c_str());

  const auto airline = flight_info.airline();
  if (airline == nullptr)
    log_w("Airline (%s) not found", flight_info.icao_airline.c_str());

  // LINE 1

  // Flight
  auto label_flight = lv_label_create(lv_scr_act());
  lv_label_set_text(label_flight, flight_info.flight.c_str());
  lv_obj_set_style_text_font(label_flight, &lv_font_montserrat_22, LV_STATE_DEFAULT);
  lv_obj_align(label_flight, LV_ALIGN_TOP_LEFT, 0, 0);
  // Special color if squawk is special code
  if (flight_info.squawk_hijack() || flight_info.squawk_radio_failure() || flight_info.squawk_emergency())
    lv_obj_set_style_text_color(label_flight, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);

  // FROM TO
  auto from_to = flight_info.iata_origin_airport + (flight_info.iata_origin_airport.length() && flight_info.iata_destination_airport.length() ? "-" : "") + flight_info.iata_destination_airport;
  auto label_from_to = lv_label_create(lv_scr_act());
  lv_label_set_text(label_from_to, from_to.c_str());
  lv_obj_set_style_text_font(label_from_to, &lv_font_montserrat_22, LV_STATE_DEFAULT);
  lv_obj_align(label_from_to, LV_ALIGN_TOP_LEFT, 90, 0);

  auto index_total = String(index) + "/" + String(total);
  auto label_index_total = lv_label_create(lv_scr_act());
  lv_label_set_text(label_index_total, index_total.c_str());
  lv_obj_align(label_index_total, LV_ALIGN_TOP_RIGHT, 0, 0);

  // LINE 2

  //  Altitude
  auto altitude = iotWebParamMetric.value() ? String(flight_info.altitude_metric()) + "m " : String(flight_info.altitude) + "ft ";
  auto label_altitude = lv_label_create(lv_scr_act());
  lv_label_set_text(label_altitude, altitude.c_str());
  lv_obj_align(label_altitude, LV_ALIGN_TOP_LEFT, 0, 24);
  if (flight_info.altitude < 0)
    lv_obj_set_style_text_color(label_altitude, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);

  // Vertical speed
  auto vertical_speed = iotWebParamMetric.value() ? String(flight_info.vertical_speed_metric()) + "m/m" : String(flight_info.vertical_speed) + "ft/m";
  auto label_vertical_speed = lv_label_create(lv_scr_act());
  lv_label_set_text(label_vertical_speed, vertical_speed.c_str());
  lv_obj_align(label_vertical_speed, LV_ALIGN_TOP_MID, 0, 24);
  if (flight_info.vertical_speed > 0)
    lv_obj_set_style_text_color(label_vertical_speed, lv_palette_main(LV_PALETTE_GREEN), LV_STATE_DEFAULT);
  else if (flight_info.vertical_speed < 0)
    lv_obj_set_style_text_color(label_vertical_speed, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);

  // Ground speed
  auto speed = iotWebParamMetric.value() ? String(flight_info.ground_speed_metric()) + "km/h" : String(flight_info.ground_speed) + "kts";
  auto label_speed = lv_label_create(lv_scr_act());
  lv_label_set_text(label_speed, speed.c_str());
  lv_obj_align(label_speed, LV_ALIGN_TOP_RIGHT, 0, 24);

  // LINE 3

  // Registration
  auto label_registration = lv_label_create(lv_scr_act());
  lv_label_set_text(label_registration, flight_info.registration.c_str());
  lv_obj_align(label_registration, LV_ALIGN_TOP_LEFT, 0, 40);

  // Aircraft
  auto aircraft_type = aircraft ? String(aircraft->manufacturer) + " " + String(aircraft->type) : flight_info.aircraft_code;
  auto label_aircraft_type = lv_label_create(lv_scr_act());
  lv_label_set_text(label_aircraft_type, aircraft_type.c_str());
  lv_obj_set_width(label_aircraft_type, 240 - 70);
  lv_label_set_long_mode(label_aircraft_type, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_align(label_aircraft_type, LV_ALIGN_TOP_LEFT, 70, 40);

  // LINE 4 - 56

  // Lat Lon
  auto latlon = format_gps_location(flight_info.latitude, flight_info.longitude);
  auto label_latlon = lv_label_create(lv_scr_act());
  lv_label_set_text(label_latlon, latlon.c_str());
  lv_obj_align(label_latlon, LV_ALIGN_TOP_LEFT, 0, 56);

  // Heading
  auto heading = String(LV_SYMBOL_GPS) + " " + format_zero_padding(flight_info.heading, 3) + "\u00b0";
  auto label_heading = lv_label_create(lv_scr_act());
  lv_label_set_text(label_heading, heading.c_str());
  lv_obj_align(label_heading, LV_ALIGN_TOP_RIGHT, -45, 56);

  // LINE 5 - 72

  if (airline)
  {
    log_i("Airline (%s): CallSign: %s. %s - %s. Logo: %s", airline->icao_airline, airline->call_sign, airline->name, airline->country->name, airline->logo.data ? "present" : "not available");

    auto label_airline = lv_label_create(lv_scr_act());
    lv_label_set_text(label_airline, airline->name);
    lv_obj_set_width(label_airline, 240 - 45);
    lv_label_set_long_mode(label_airline, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_align(label_airline, LV_ALIGN_TOP_LEFT, 0, 56 + 40 - 14);

    if (airline->logo.data)
    {
      auto image = lv_gif_create(lv_scr_act());
      lv_gif_set_src(image, &airline->logo);
      lv_obj_align(image, LV_ALIGN_TOP_RIGHT, 0, 56);
    }
    else
      log_w("No logo present for airline: %s", airline->icao_airline);
  }

  // BOTTOM

  auto iata_origin = flight_info.origin_airport();
  if (iata_origin)
  {
    log_i("From %s: %s - %s (%s) %s. %s", iata_origin->iata_airport, iata_origin->name, iata_origin->city, iata_origin->region, iata_origin->country->name, format_gps_location(iata_origin->latitude, iata_origin->longitude).c_str());
    if (iata_origin->country)
    {
      if (iata_origin->country->flag.data)
      {
        auto image = lv_gif_create(lv_scr_act());
        lv_gif_set_src(image, &iata_origin->country->flag);
        lv_obj_align(image, LV_ALIGN_BOTTOM_LEFT, 0, -20);
      }
    }

    auto label_origin = lv_label_create(lv_scr_act());
    lv_label_set_text(label_origin, iata_origin->name);
    lv_obj_set_width(label_origin, 240 - 26);
    lv_label_set_long_mode(label_origin, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_align(label_origin, LV_ALIGN_BOTTOM_LEFT, 26, -20);
  }
  else
    log_w("From airport (%s) not found", flight_info.iata_origin_airport.c_str());

  auto iata_destination = flight_info.destination_airport();
  if (iata_destination)
  {
    log_i("To %s: %s - %s (%s) %s. %s", iata_destination->iata_airport, iata_destination->name, iata_destination->city, iata_destination->region, iata_destination->country->name, format_gps_location(iata_destination->latitude, iata_destination->longitude).c_str());
    if (iata_destination->country)
    {
      if (iata_destination->country->flag.data)
      {
        auto image = lv_gif_create(lv_scr_act());
        lv_gif_set_src(image, &iata_destination->country->flag);
        lv_obj_align(image, LV_ALIGN_BOTTOM_LEFT, 0, 0);
      }
    }

    auto label_destination = lv_label_create(lv_scr_act());
    lv_label_set_text(label_destination, iata_destination->name);
    lv_obj_set_width(label_destination, 240 - 26);
    lv_label_set_long_mode(label_destination, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_align(label_destination, LV_ALIGN_BOTTOM_LEFT, 26, 0);
  }
  else
    log_w("To airport (%s) not found", flight_info.iata_destination_airport.c_str());
}

void set_progress_bar(void *bar, int32_t v)
{
  lv_bar_set_value(static_cast<lv_obj_t *>(bar), v, LV_ANIM_ON);
}

void display_network_state(iotwebconf::NetworkState state)
{
  log_i("Network state: %d", state);
  switch (state)
  {
  case iotwebconf::NotConfigured:
  {
    lv_obj_clean(lv_scr_act());
    auto image = lv_img_create(lv_scr_act());
    lv_img_set_src(image, &image_wifi);
    lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);

    auto label_state = lv_label_create(lv_scr_act());
    lv_label_set_text(label_state, "Not configured!");
    lv_obj_set_style_text_font(label_state, &lv_font_montserrat_22, LV_STATE_DEFAULT);
    lv_obj_align(label_state, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_text_color(label_state, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);

    auto label_message = lv_label_create(lv_scr_act());
    lv_label_set_text(label_message, iotWebConf.getThingName());
    lv_obj_align(label_message, LV_ALIGN_BOTTOM_MID, 0, 0);
  }
  break;

  case iotwebconf::ApMode:
  {
    lv_obj_clean(lv_scr_act());
    auto image = lv_img_create(lv_scr_act());
    lv_img_set_src(image, &image_wifi);
    // background color: 212121
    lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);

    auto label_message = lv_label_create(lv_scr_act());
    lv_label_set_text(label_message, iotWebConf.getThingName());
    lv_obj_align(label_message, LV_ALIGN_BOTTOM_MID, 0, -5);

    // Bar animation
    auto timeout = atoi(iotWebConf.getApTimeoutParameter()->valueBuffer);
    log_i("Timeout: %d seconds", timeout);
    auto bar = lv_bar_create(lv_scr_act());
    lv_obj_set_size(bar, 240, 3);
    lv_obj_align(bar, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_bar_set_range(bar, 0, 100);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, &set_progress_bar);
    lv_anim_set_time(&a, timeout * 1000);
    lv_anim_set_var(&a, bar);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);
  }
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
  break;

  case iotwebconf::OffLine:
  {
    lv_obj_clean(lv_scr_act());
    auto image = lv_img_create(lv_scr_act());
    lv_img_set_src(image, &image_no_internet);
  }
  break;
  }
}

void display_flights()
{
  auto now = millis();
  if (now > next_update)
  {
    lv_obj_clean(lv_scr_act());

    if (it == flights.cend())
    {
      log_i("Updating flights");
      String error_message;
      if (!get_flights(iotWebParamLatitude.value(), iotWebParamLongitude.value(), iotWebParamLatitudeRange.value(), iotWebParamLongitudeRange.value(), iotWebParamAirborne.value(), iotWebParamGrounded.value(), iotWebParamGliders.value(), iotWebParamVehicles.value(), flights, error_message))
      {
        log_e("Error getting flights: %s", error_message.c_str());
        auto label_message = lv_label_create(lv_scr_act());
        lv_label_set_text(label_message, error_message.c_str());
        lv_obj_set_style_text_color(label_message, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
        lv_obj_align(label_message, LV_ALIGN_BOTTOM_MID, 0, 0);

        next_update = now + flight_milliseconds_error;
        return;
      }

      log_i("Number of flights: %d", flights.size());
      if (flights.empty())
      {
        log_d("No flights in range");
        auto label_message = lv_label_create(lv_scr_act());
        lv_label_set_text(label_message, "No flights in range");
        lv_obj_set_style_text_color(label_message, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(label_message, &lv_font_montserrat_22, LV_STATE_DEFAULT);
        lv_obj_align(label_message, LV_ALIGN_TOP_MID, 0, 0);
        auto label_time = lv_label_create(lv_scr_act());
        lv_label_set_text(label_time, get_localtime("%F - %R").c_str());
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

        next_update = now + flight_milliseconds_noflights;
        return;
      }

      it = flights.begin();
      flight_index = 1;
    }

    display_flight(*it++, flight_index++, flights.size());

    next_update = now + flight_milliseconds;
  }
}

void display_clock()
{
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  if (timeinfo.tm_min != last_minute)
  {
    last_minute = timeinfo.tm_min;
    log_i("Updating clock");

    lv_obj_clean(lv_scr_act());

    if (time_valid())
    {
      auto label_date = lv_label_create(lv_scr_act());
      lv_label_set_text(label_date, get_localtime("%F").c_str());
      lv_obj_set_style_text_font(label_date, &lv_font_montserrat_22, LV_STATE_DEFAULT);
      lv_obj_align(label_date, LV_ALIGN_TOP_MID, 0, 0);
      auto label_time = lv_label_create(lv_scr_act());
      lv_label_set_text(label_time, get_localtime("%R").c_str());
      lv_obj_set_style_text_font(label_time, &lv_font_montserrat_22, LV_STATE_DEFAULT);
      lv_obj_align(label_time, LV_ALIGN_CENTER, 0, 0);
      auto label_timezone = lv_label_create(lv_scr_act());
      lv_label_set_text(label_timezone, iotWebParamTimeZone.value());
      lv_obj_align(label_timezone, LV_ALIGN_BOTTOM_MID, 0, 0);
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
    next_update = 0ul;
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
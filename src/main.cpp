#include <settings.h>

#include <SPI.h>
#include <soc/rtc_cntl_reg.h>

#include <esp_adc_cal.h>

#include <FS.h>

// Settings for the display are defined in platformio.ini
#include <TFT_eSPI.h>
#include <lvgl.h>

#include <flight_info.h>
#include <time.h>
#include <string>
#include <string>

#include <ESPmDNS.h>
#include <IotWebConf.h>
#include <IotWebConfTParameter.h>

#include <moustache.h>
#include <format_gps.h>
#include <format_date_time.h>
#include <format_number.h>
#include <format_duration.h>
#include <format_latin.h>

#include <images.h>
#include <timezonedb_lookup.h>

// Embedded data
extern const uint8_t binary_html_bootstrap_min_css_gz_start[] asm("_binary_html_bootstrap_min_css_gz_start");
extern const uint8_t binary_html_bootstrap_min_css_gz_end[] asm("_binary_html_bootstrap_min_css_gz_end");
extern const char text_html_index_html[] asm("_binary_html_index_html_start");

// LCD display
auto tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

esp_adc_cal_characteristics_t adc_chars;

// Web server
DNSServer dnsServer;
WebServer server(80);
auto deviceName = String(WIFI_SSID) + "-" + String(ESP.getEfuseMac(), 16);
IotWebConf iotWebConf(deviceName.c_str(), &dnsServer, &server, WIFI_PASSWORD, CONFIG_VERSION);

auto param_group = iotwebconf::ParameterGroup("flightradar", "Flight radar");
auto iotWebParamLocation = iotwebconf::Builder<iotwebconf::TextTParameter<32>>("location")
                               .label("Location")
                               .defaultValue(DEFAULT_LOCATION)
                               .build();
auto iotWebParamLatitude = iotwebconf::Builder<iotwebconf::FloatTParameter>("lat")
                               .label("Latitude")
                               .min(-90.0)
                               .max(90.0)
                               .defaultValue(DEFAULT_LATITUDE)
                               .step(0.01)
                               .placeholder("e.g. 52.3")
                               .build();
auto iotWebParamLongitude = iotwebconf::Builder<iotwebconf::FloatTParameter>("lon")
                                .label("Longitude")
                                .min(-180.0)
                                .max(180.0)
                                .defaultValue(DEFAULT_LONGITUDE)
                                .step(0.01)
                                .placeholder("e.g. 4.76")
                                .build();
auto iotWebParamLatitudeRange = iotwebconf::Builder<iotwebconf::FloatTParameter>("lat_range")
                                    .label("Latitude range (degrees)")
                                    .defaultValue(DEFAULT_RANGE_LATITUDE)
                                    .step(0.01)
                                    .placeholder("e.g. 0.1")
                                    .build();
auto iotWebParamLongitudeRange = iotwebconf::Builder<iotwebconf::FloatTParameter>("lon_range")
                                     .label("Longitude range (degrees)")
                                     .defaultValue(DEFAULT_RANGE_LONGITUDE)
                                     .step(0.01)
                                     .placeholder("e.g. 0.1")
                                     .build();
auto iotWebParamAirborne = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("air")
                               .label("Include airborne")
                               .defaultValue(DEFAULT_AIR)
                               .build();
auto iotWebParamGrounded = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("ground")
                               .label("Include grounded")
                               .defaultValue(DEFAULT_GROUND)
                               .build();
auto iotWebParamGliders = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("gliders")
                              .label("Include gliders")
                              .defaultValue(DEFAULT_GLIDERS)
                              .build();
auto iotWebParamVehicles = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("vehicles")
                               .label("Include vehicles")
                               .defaultValue(DEFAULT_VEHICLES)
                               .build();
// The timezone names live in a posix_timezone_tz_t[] array, where each zone_name starts at a fixed stride of sizeof(posix_timezone_tz_t)
auto iotWebParamTimeZone = iotwebconf::Builder<iotwebconf::SelectTParameter<sizeof(posix_timezone_tz_t)>>("timezone")
                               .label("Choose timezone")
                               .optionValues(posix_timezone_tzs->zone_name)
                               .optionNames(posix_timezone_tzs->zone_name)
                               .optionCount(sizeof(posix_timezone_tzs) / sizeof(posix_timezone_tzs[0]))
                               .nameLength(sizeof(posix_timezone_tz_t))
                               .defaultValue(DEFAULT_TIMEZONE)
                               .build();
auto iotWebParamMetric = iotwebconf::Builder<iotwebconf::CheckboxTParameter>("metric")
                             .label("Use metric units")
                             .defaultValue(DEFAULT_METRIC)
                             .build();

// Variables for flight info
unsigned long next_update;
// List of flights
std::list<flight_info> flights;
// Flight to display
std::list<flight_info>::const_iterator it = flights.cbegin();
// Number of times the current flight has been displayed
unsigned int display_cycle = 0;
// True when the last attempt to retrieve the flights failed
bool flights_update_error = false;

// Display mode
enum display_mode
{
  DISPLAY_MODE_FLIGHTS,
  DISPLAY_MODE_CLOCK,
  DISPLAY_MODE_FLIGHTS_CLOCK
};

display_mode display_mode = DISPLAY_MODE_FLIGHTS;

// One event per physical press of TOP and BOTTOM buttons
volatile bool top_button_event = false;
volatile bool bottom_button_event = false;

// Screen shown on the display
enum screen
{
  SCREEN_NONE,       // Nothing of this application is shown (startup / network screens)
  SCREEN_CLOCK,      // Date, time and location
  SCREEN_FLIGHT,     // Details of a single flight
  SCREEN_NO_FLIGHTS, // Information screen when no flights are in range
  SCREEN_ERROR       // Error retrieving the flights
};

screen current_screen = SCREEN_NONE;

// Clock screen objects
lv_obj_t *clock_date_label = nullptr;
lv_obj_t *clock_time_label = nullptr;
lv_obj_t *clock_location_label = nullptr;

// Flight screen objects
lv_obj_t *flight_label = nullptr;
lv_obj_t *flight_from_to_label = nullptr;
lv_obj_t *flight_index_total_label = nullptr;
lv_obj_t *flight_altitude_label = nullptr;
lv_obj_t *flight_vertical_speed_label = nullptr;
lv_obj_t *flight_speed_label = nullptr;
lv_obj_t *flight_registration_label = nullptr;
lv_obj_t *flight_aircraft_type_label = nullptr;
lv_obj_t *flight_latlon_label = nullptr;
lv_obj_t *flight_heading_label = nullptr;
lv_obj_t *flight_airline_label = nullptr;
lv_obj_t *flight_airline_logo_image = nullptr;
lv_obj_t *flight_origin_label = nullptr;
lv_obj_t *flight_origin_flag_image = nullptr;
lv_obj_t *flight_destination_label = nullptr;
lv_obj_t *flight_destination_flag_image = nullptr;

// "No flights in range" screen objects
lv_obj_t *no_flights_message_label = nullptr;
lv_obj_t *no_flights_time_label = nullptr;
lv_obj_t *no_flights_latlon_label = nullptr;
lv_obj_t *no_flights_range_label = nullptr;
lv_obj_t *no_flights_location_label = nullptr;
lv_obj_t *no_flights_timezone_label = nullptr;

// Error screen objects
lv_obj_t *error_message_label = nullptr;

// PWM channel used to dim the backlight LED (TFT_BL)
constexpr auto backlight_pwm_channel = 0;

// PWM Duty cycles steps for the backlight
float backlight_pwm_duty_steps[] = {1.00f, 0.75f, 0.50f, 0.25f, 0.15f, 0.10f, 0.05f};
byte backlight_pwm_duty_step = 0; // Start with maximum brightness

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

  moustache_variable_t substitutions[] = {
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
      {"LocalTime", get_localtime(iotWebParamMetric.value() ? localtime_format_date_time_metric : localtime_format_date_time_imperial)},
      // Network
      {"HostName", hostname},
      {"MacAddress", WiFi.macAddress()},
      {"AccessPoint", WiFi.SSID()},
      {"SignalStrength", String(WiFi.RSSI())},
      {"IpV4", WiFi.localIP().toString()},
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
  auto html = moustache_render(text_html_index_html, substitutions);
  server.send(200, "text/html", html);
}

// Display flushing
void tft_espi_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
  auto w = (area->x2 - area->x1 + 1);
  auto h = (area->y2 - area->y1 + 1);
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();
  lv_disp_flush_ready(drv);
}

void set_backlight_pwm_duty(float level)
{
  auto pwm = (uint32_t)(level * backlight_max_level);
  ledcWrite(backlight_pwm_channel, pwm);
  log_i("Backlight PWM on pin %d (channel %d, %d Hz, %d-bit): %f%% level %d/%d", TFT_BL, backlight_pwm_channel, backlight_pwm_frequency, level, backlight_pwm_resolution, pwm, backlight_max_level);
}

void button_read(_lv_indev_drv_t *drv, lv_indev_data_t *data)
{
  static uint32_t last_key;
  uint32_t key = 0;
  static bool last_top_pressed = false;
  static bool last_bottom_pressed = false;

#if GPIO_BUTTON_TOP >= 0
  const bool top_button_pressed = (digitalRead(GPIO_BUTTON_TOP) == LOW);
  if (key == 0 && top_button_pressed)
    key = LV_KEY_NEXT;

  // Generate one application event on the press edge.
  if (top_button_pressed && !last_top_pressed)
  {
    top_button_event = true;
    log_i("TOP BUTTON pressed");
  }

  last_top_pressed = top_button_pressed;
#endif

#if GPIO_BUTTON_BOTTOM >= 0
  const bool bottom_button_pressed = (digitalRead(GPIO_BUTTON_BOTTOM) == LOW);
  if (key == 0 && bottom_button_pressed)
    key = LV_KEY_ENTER;

  // Generate one application event on the press edge.
  if (bottom_button_pressed && !last_bottom_pressed)
  {
    bottom_button_event = true;
    log_i("BOTTOM BUTTON pressed");
  }

  last_bottom_pressed = bottom_button_pressed;
#endif

  if (key)
  {
    data->state = LV_INDEV_STATE_PR;
    log_d("Button: 0x%02x pressed", key);
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }

  data->key = key;
}

void lvgl_log(const char *buf)
{
  log_printf("%s", buf);
}

void setup()
{
  // Disable brownout
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

#ifdef GPIO_ADC_EN
  //  ADC_EN is the ADC detection enable port
  //  If the USB port is used for power supply, it is turned on by default.
  //  If it is powered by battery, it needs to be set to high level
  pinMode(GPIO_ADC_EN, OUTPUT);
  digitalWrite(GPIO_ADC_EN, LOW);

  // ADC calibration: GPIO34 = ADC1_CH6. After the 2:1 voltage divider, USB (2.5V) and battery (1.85-2.1V)
  // exceed ADC_ATTEN_DB_2_5 limit (~1.5V). Use ADC_ATTEN_DB_12 (~3.9V max) and set hardware attenuation
  // explicitly so it matches the calibration curve.
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_12);
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, &adc_chars);
#endif

  log_i("CPU Freq = %d Mhz", getCpuFrequencyMhz());
  log_i("Free heap: %d bytes", ESP.getFreeHeap());
  log_i("Starting " APP_TITLE "...");

  // Input buttons
#if GPIO_BUTTON_TOP >= 0
  pinMode(GPIO_BUTTON_TOP, INPUT_PULLUP);
#endif
#if GPIO_BUTTON_BOTTOM >= 0
  pinMode(GPIO_BUTTON_BOTTOM, INPUT_PULLUP);
#endif

  // Start LVGL
  log_i("LVGL version: %d.%d.%d ", lv_version_major(), lv_version_minor(), lv_version_patch());
  lv_init();
  tft.begin();
  // Rotate 90 degrees to Landscape
  tft.setRotation(1);

  // Drive the backlight with PWM (instead of a fixed GPIO level) so the brightness can be dimmed with the bottom button.
  ledcSetup(backlight_pwm_channel, backlight_pwm_frequency, backlight_pwm_resolution);
  ledcAttachPin(TFT_BL, backlight_pwm_channel);
  set_backlight_pwm_duty(1.0f); // Start with full brightness

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
  disp_drv.flush_cb = tft_espi_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
  // Initialize the keyboard
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv.read_cb = button_read;
  lv_indev_drv_register(&indev_drv);

  // For debugging
  lv_log_register_print_cb(&lvgl_log);

  // Hide the scrollbar and disable scrolling on the screen
  lv_obj_set_scrollbar_mode(lv_scr_act(), LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
  // The dark theme uses #15171A as the screen background; use pure black instead
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);

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
#if GPIO_BUTTON_TOP >= 0
  iotWebConf.setConfigPin(GPIO_BUTTON_TOP);
#endif

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
              send_content_gzip(binary_html_bootstrap_min_css_gz_start, binary_html_bootstrap_min_css_gz_end - binary_html_bootstrap_min_css_gz_start, "text/css"); });

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
  {
    log_e("Timezone %s not found!", iotWebParamTimeZone.value());
  }
}

// Only update if different, to avoid unnecessary redraws and flickering
void lv_label_update_text(lv_obj_t * obj, const char * text)
{
  if (strcmp(lv_label_get_text(obj), text) == 0)
    return;

  lv_label_set_text(obj, text);
}

void create_clock_screen()
{
  // Day + Date
  clock_date_label = lv_label_create(lv_scr_act());
  lv_obj_set_style_text_font(clock_date_label, &lv_font_montserrat_22, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(clock_date_label, lv_palette_main(LV_PALETTE_GREY), LV_STATE_DEFAULT);
  lv_obj_align(clock_date_label, LV_ALIGN_CENTER, 0, -42);
  // Time
  clock_time_label = lv_label_create(lv_scr_act());
  lv_obj_set_style_text_font(clock_time_label, &lv_font_montserrat_38, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(clock_time_label, lv_palette_main(LV_PALETTE_GREY), LV_STATE_DEFAULT);
  lv_obj_align(clock_time_label, LV_ALIGN_CENTER, 0, 0);
  // City / Location
  clock_location_label = lv_label_create(lv_scr_act());
  lv_obj_set_style_text_font(clock_location_label, &lv_font_montserrat_14, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(clock_location_label, lv_palette_main(LV_PALETTE_GREY), LV_STATE_DEFAULT);
  lv_obj_align(clock_location_label, LV_ALIGN_CENTER, 0, 42);
}

// Set the image of a GIF or hide it when there is no source
void set_flight_image(lv_obj_t *image, const lv_img_dsc_t *source)
{
  if (source == nullptr || source->data == nullptr)
  {
    lv_obj_add_flag(image, LV_OBJ_FLAG_HIDDEN);
    return;
  }

  lv_gif_set_src(image, source);
  lv_obj_clear_flag(image, LV_OBJ_FLAG_HIDDEN);
}

void create_flight_screen()
{
  // LINE 1
  // Flight
  flight_label = lv_label_create(lv_scr_act());
  lv_obj_set_style_text_font(flight_label, &lv_font_montserrat_22, LV_STATE_DEFAULT);
  lv_obj_align(flight_label, LV_ALIGN_TOP_LEFT, 0, 0);
  // FROM TO
  flight_from_to_label = lv_label_create(lv_scr_act());
  lv_obj_set_style_text_font(flight_from_to_label, &lv_font_montserrat_22, LV_STATE_DEFAULT);
  lv_obj_align(flight_from_to_label, LV_ALIGN_TOP_LEFT, 90, 0);
  // Index / total
  flight_index_total_label = lv_label_create(lv_scr_act());
  lv_obj_align(flight_index_total_label, LV_ALIGN_TOP_RIGHT, 0, 0);
  // LINE 2
  // Altitude
  flight_altitude_label = lv_label_create(lv_scr_act());
  lv_obj_align(flight_altitude_label, LV_ALIGN_TOP_LEFT, 0, 24);
  // Vertical speed
  flight_vertical_speed_label = lv_label_create(lv_scr_act());
  lv_obj_align(flight_vertical_speed_label, LV_ALIGN_TOP_MID, 0, 24);
  // Ground speed
  flight_speed_label = lv_label_create(lv_scr_act());
  lv_obj_align(flight_speed_label, LV_ALIGN_TOP_RIGHT, 0, 24);
  // LINE 3
  // Registration
  flight_registration_label = lv_label_create(lv_scr_act());
  lv_obj_align(flight_registration_label, LV_ALIGN_TOP_LEFT, 0, 40);
  // Aircraft
  flight_aircraft_type_label = lv_label_create(lv_scr_act());
  lv_obj_set_width(flight_aircraft_type_label, 240 - 70);
  lv_label_set_long_mode(flight_aircraft_type_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_align(flight_aircraft_type_label, LV_ALIGN_TOP_LEFT, 70, 40);
  // LINE 4 - 56
  // Lat Lon
  flight_latlon_label = lv_label_create(lv_scr_act());
  lv_obj_align(flight_latlon_label, LV_ALIGN_TOP_LEFT, 0, 56);
  // Heading
  flight_heading_label = lv_label_create(lv_scr_act());
  lv_obj_align(flight_heading_label, LV_ALIGN_TOP_RIGHT, -45, 56);
  // LINE 5 - 72
  // Airline with logo
  flight_airline_label = lv_label_create(lv_scr_act());
  lv_obj_set_width(flight_airline_label, 240 - 45);
  lv_label_set_long_mode(flight_airline_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_align(flight_airline_label, LV_ALIGN_TOP_LEFT, 0, 56 + 40 - 14);
  flight_airline_logo_image = lv_gif_create(lv_scr_act());
  lv_obj_align(flight_airline_logo_image, LV_ALIGN_TOP_RIGHT, 0, 56);
  lv_obj_add_flag(flight_airline_logo_image, LV_OBJ_FLAG_HIDDEN);
  // BOTTOM
  // From, with the flag of the country
  flight_origin_flag_image = lv_gif_create(lv_scr_act());
  lv_obj_align(flight_origin_flag_image, LV_ALIGN_BOTTOM_LEFT, 0, -20);
  lv_obj_add_flag(flight_origin_flag_image, LV_OBJ_FLAG_HIDDEN);
  flight_origin_label = lv_label_create(lv_scr_act());
  lv_obj_set_width(flight_origin_label, 240 - 24);
  lv_label_set_long_mode(flight_origin_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_align(flight_origin_label, LV_ALIGN_BOTTOM_LEFT, 28, -20);
  // To, with the flag of the country
  flight_destination_flag_image = lv_gif_create(lv_scr_act());
  lv_obj_align(flight_destination_flag_image, LV_ALIGN_BOTTOM_LEFT, 0, 0);
  lv_obj_add_flag(flight_destination_flag_image, LV_OBJ_FLAG_HIDDEN);
  flight_destination_label = lv_label_create(lv_scr_act());
  lv_obj_set_width(flight_destination_label, 240 - 24);
  lv_label_set_long_mode(flight_destination_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_align(flight_destination_label, LV_ALIGN_BOTTOM_LEFT, 28, 0);
}

void create_no_flights_screen()
{
  no_flights_message_label = lv_label_create(lv_scr_act());
  lv_label_set_text(no_flights_message_label, "No flights in range");
  lv_obj_set_style_text_color(no_flights_message_label, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(no_flights_message_label, &lv_font_montserrat_22, LV_STATE_DEFAULT);
  lv_obj_align(no_flights_message_label, LV_ALIGN_TOP_MID, 0, 0);
  no_flights_time_label = lv_label_create(lv_scr_act());
  lv_obj_align(no_flights_time_label, LV_ALIGN_CENTER, 0, -16);
  no_flights_latlon_label = lv_label_create(lv_scr_act());
  lv_obj_align(no_flights_latlon_label, LV_ALIGN_CENTER, 0, 0);
  no_flights_range_label = lv_label_create(lv_scr_act());
  lv_obj_align(no_flights_range_label, LV_ALIGN_CENTER, 0, 16);
  no_flights_location_label = lv_label_create(lv_scr_act());
  lv_obj_align(no_flights_location_label, LV_ALIGN_BOTTOM_MID, 0, -16);
  no_flights_timezone_label = lv_label_create(lv_scr_act());
  lv_obj_align(no_flights_timezone_label, LV_ALIGN_BOTTOM_MID, 0, 0);
}

void create_error_screen()
{
  error_message_label = lv_label_create(lv_scr_act());
  lv_obj_set_style_text_color(error_message_label, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
  lv_obj_align(error_message_label, LV_ALIGN_BOTTOM_MID, 0, 0);
}

// Show the given screen. The screen is only cleared when another screen is shown so the
// objects of the current screen can be updated in place.
void show_screen(screen screen)
{
  if (current_screen == screen)
    return;

  lv_obj_clean(lv_scr_act());
  current_screen = screen;

  switch (screen)
  {
  case SCREEN_CLOCK:
    create_clock_screen();
    break;

  case SCREEN_FLIGHT:
    create_flight_screen();
    break;

  case SCREEN_NO_FLIGHTS:
    create_no_flights_screen();
    break;

  case SCREEN_ERROR:
    create_error_screen();
    break;

  default:
    break;
  }
}

void display_clock()
{
  show_screen(SCREEN_CLOCK);

  static time_t clock_last_time = -1;

  const time_t now = time(nullptr);
  if (now == clock_last_time)
    return;

  clock_last_time = now;

  if (time_valid())
  {
    lv_label_update_text(clock_date_label, get_localtime(iotWebParamMetric.value() ? localtime_format_date_metric : localtime_format_date_imperial).c_str());
    lv_label_update_text(clock_time_label, get_localtime(iotWebParamMetric.value() ? localtime_format_time_metric : localtime_format_time_imperial).c_str());
    lv_label_update_text(clock_location_label, iotWebParamLocation.value());
  }
  else
  {
    lv_label_update_text(clock_date_label, "");
    lv_label_update_text(clock_time_label, "");
    lv_label_update_text(clock_location_label, "No NTP Time");
  }
}

void enter_flights_mode()
{
  display_mode = DISPLAY_MODE_FLIGHTS;
  // Force an update of the flights
  next_update = 0;
  log_i("Display mode: FLIGHTS");
}

void enter_clock_mode()
{
  display_mode = DISPLAY_MODE_CLOCK;
  log_i("Display mode: CLOCK");
}

void enter_flights_clock_mode()
{
  display_mode = DISPLAY_MODE_FLIGHTS_CLOCK;
  // Force an update of the flights
  next_update = 0;
  log_i("Display mode: FLIGHTS + CLOCK");
}

void display_flight(std::list<flight_info>::const_iterator it)
{
  const flight_info &flight_info = *it;

  log_i("%s", flight_info.toString().c_str());
  show_screen(SCREEN_FLIGHT);

  const auto aircraft = flight_info.aircraft_type();
  if (aircraft == nullptr)
    log_w("Aircraft (%s) not found", flight_info.aircraft_code.c_str());

  const auto airline = flight_info.airline();
  if (airline == nullptr)
    log_w("Airline (%s) not found", flight_info.icao_airline.c_str());

  // LINE 1
  // Flight
  lv_label_update_text(flight_label, flight_info.flight.c_str());
  // Special color if squawk is special code
  if (flight_info.squawk_hijack() || flight_info.squawk_radio_failure() || flight_info.squawk_emergency())
    lv_obj_set_style_text_color(flight_label, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
  else
    lv_obj_remove_local_style_prop(flight_label, LV_STYLE_TEXT_COLOR, LV_STATE_DEFAULT);
  // FROM TO
  auto from_to = flight_info.iata_origin_airport + (flight_info.iata_origin_airport.length() && flight_info.iata_destination_airport.length() ? "-" : "") + flight_info.iata_destination_airport;
  lv_label_update_text(flight_from_to_label, from_to.c_str());
  auto index = std::distance(flights.cbegin(), it) + 1;
  auto total = flights.size();
  auto index_total = String(index) + "/" + String(total);
  lv_label_update_text(flight_index_total_label, index_total.c_str());
  // LINE 2
  //  Altitude
  auto altitude = iotWebParamMetric.value() ? String(flight_info.altitude_metric()) + "m" : String(flight_info.altitude) + "ft";
  lv_label_update_text(flight_altitude_label, altitude.c_str());
  if (flight_info.altitude < 0)
    lv_obj_set_style_text_color(flight_altitude_label, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
  else
    lv_obj_remove_local_style_prop(flight_altitude_label, LV_STYLE_TEXT_COLOR, LV_STATE_DEFAULT);
  // Vertical speed
  auto vertical_speed = iotWebParamMetric.value() ? String(flight_info.vertical_speed_metric()) + "m/min" : String(flight_info.vertical_speed) + "ft/min";
  lv_label_update_text(flight_vertical_speed_label, vertical_speed.c_str());
  if (flight_info.vertical_speed > 0)
    lv_obj_set_style_text_color(flight_vertical_speed_label, lv_palette_main(LV_PALETTE_GREEN), LV_STATE_DEFAULT);
  else if (flight_info.vertical_speed < 0)
    lv_obj_set_style_text_color(flight_vertical_speed_label, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
  else
    lv_obj_remove_local_style_prop(flight_vertical_speed_label, LV_STYLE_TEXT_COLOR, LV_STATE_DEFAULT);

  // Ground speed
  auto speed = iotWebParamMetric.value() ? String(flight_info.ground_speed_metric()) + "km/h" : String(flight_info.ground_speed) + "kts";
  lv_label_update_text(flight_speed_label, speed.c_str());
  // LINE 3
  // Registration
  lv_label_update_text(flight_registration_label, flight_info.registration.c_str());
  // Aircraft
  auto aircraft_type = aircraft ? String(aircraft->manufacturer) + " " + String(aircraft->type) : flight_info.aircraft_code;
  lv_label_update_text(flight_aircraft_type_label, aircraft_type.c_str());
  // LINE 4 - 56
  // Lat Lon
  auto latlon = format_gps_location(flight_info.latitude, flight_info.longitude);
  lv_label_update_text(flight_latlon_label, latlon.c_str());
  // Heading \u00b0 = degrees
  auto heading = format_zero_padding(flight_info.heading, 3) + "\u00b0";
  lv_label_update_text(flight_heading_label, heading.c_str());
  // LINE 5 - 72
  if (airline)
  {
    auto country = get_country(airline->country);
    log_i("Airline (%s): CallSign: %s. %s - %s. Logo: %s", airline->icao_airline, airline->call_sign, airline->name, country->name, airline->logo.data ? "present" : "not available");
    lv_label_update_text(flight_airline_label, format_to_latin(airline->name).c_str());
    if (airline->logo.data == nullptr)
      log_w("No logo present for airline: %s", airline->icao_airline);
  }
  else
  {
    lv_label_update_text(flight_airline_label, "");
  }

  set_flight_image(flight_airline_logo_image, airline ? &airline->logo : nullptr);
  // BOTTOM
  auto iata_origin = flight_info.origin_airport();
  if (iata_origin)
  {
    auto country = get_country(iata_origin->country);
    log_i("From %s: %s - %s (%s) %s. %s", iata_origin->iata_airport, iata_origin->name, iata_origin->city, iata_origin->region, country->name, format_gps_location(iata_origin->latitude, iata_origin->longitude).c_str());
    auto origin_text = std::string(iata_origin->name) + " - " + iata_origin->city;
    lv_label_update_text(flight_origin_label, format_to_latin(origin_text.c_str()).c_str());
    set_flight_image(flight_origin_flag_image, (const lv_img_dsc_t *)&country->flag);
  }
  else
  {
    log_w("From airport (%s) not found", flight_info.iata_origin_airport.c_str());
    lv_label_update_text(flight_origin_label, "");
    set_flight_image(flight_origin_flag_image, nullptr);
  }

  auto iata_destination = flight_info.destination_airport();
  if (iata_destination)
  {
    auto country = get_country(iata_destination->country);
    log_i("To %s: %s - %s (%s) %s. %s", iata_destination->iata_airport, iata_destination->name, iata_destination->city, iata_destination->region, country->name, format_gps_location(iata_destination->latitude, iata_destination->longitude).c_str());
    auto destination_text = std::string(iata_destination->name) + " - " + iata_destination->city;
    lv_label_update_text(flight_destination_label, format_to_latin(destination_text.c_str()).c_str());
    set_flight_image(flight_destination_flag_image, iata_destination->country != COUNTRY_ZZ ? (const lv_img_dsc_t *)&country->flag : nullptr);
  }
  else
  {
    log_w("To airport (%s) not found", flight_info.iata_destination_airport.c_str());
    lv_label_update_text(flight_destination_label, "");
    set_flight_image(flight_destination_flag_image, nullptr);
  }
}

void set_progress_bar(void *bar, int32_t v)
{
  lv_bar_set_value(static_cast<lv_obj_t *>(bar), v, LV_ANIM_ON);
}

void display_network_state(iotwebconf::NetworkState state)
{
  log_i("Network state: %d", state);
  // The network screens own the display; the flight and clock screens have to be rebuilt afterwards
  current_screen = SCREEN_NONE;

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
  // Use a signed difference so the comparison is safe around the 49.7 day millis() wrap-around
  if (static_cast<long>(now - next_update) > 0)
  {
#if defined(GPIO_ADC_EN) && defined(GPIO_ADC_IN)
    // Read USB voltage: (GPIO_ADC_EN is LOW) means USB powered, (GPIO_ADC_EN is HIGH) means battery powered
    auto usb_voltage = esp_adc_cal_raw_to_voltage(analogRead(GPIO_ADC_IN), &adc_chars) / 1000.0 * 2.0; // mV -> V, account for the 2:1 voltage divider
    if (usb_voltage > 4.5)
      log_i("USB voltage: %.2f V", usb_voltage);
    else
    {
      // Read Li-ion battery voltage
      digitalWrite(GPIO_ADC_EN, HIGH);
      delay(1);
      auto battery_voltage = esp_adc_cal_raw_to_voltage(analogRead(GPIO_ADC_IN), &adc_chars) / 1000.0 * 2.0; // mV -> V, account for the 2:1 voltage divider
      digitalWrite(GPIO_ADC_EN, LOW);
      log_i("Battery voltage: %.2fV", battery_voltage);
    }
#endif

    if (flights.empty() || display_cycle >= display_cycles)
    {
      log_i("No flights in range or number of cycles exceeded. Updating flights");
      String error_message;
      if (!get_flights(iotWebParamLatitude.value(), iotWebParamLongitude.value(), iotWebParamLatitudeRange.value(), iotWebParamLongitudeRange.value(), iotWebParamAirborne.value(), iotWebParamGrounded.value(), iotWebParamGliders.value(), iotWebParamVehicles.value(), flights, error_message))
      {
        log_e("Error getting flights: %s", error_message.c_str());
        flights_update_error = true;
        show_screen(SCREEN_ERROR);
        lv_label_update_text(error_message_label, error_message.c_str());
        next_update = now + flight_milliseconds_error;
        return;
      }

      flights_update_error = false;
      log_i("Number of flights available: %d", flights.size());
      if (flights.empty())
      {
        show_screen(SCREEN_NO_FLIGHTS);
        lv_label_update_text(no_flights_time_label, get_localtime(iotWebParamMetric.value() ? localtime_format_date_time_metric : localtime_format_date_time_imperial).c_str());
        lv_label_update_text(no_flights_latlon_label, format_gps_location(iotWebParamLatitude.value(), iotWebParamLongitude.value()).c_str());
        auto lat_lon_range = iotWebParamMetric.value()
                                 ? "lat: " + String(iotWebParamLatitudeRange.value() * DEGREES_TO_KM) + " / lon: " + String(iotWebParamLongitudeRange.value() * DEGREES_TO_KM) + " km"
                                 : "lat: " + String(iotWebParamLatitudeRange.value() * DEGREES_TO_MI) + " / lon: " + String(iotWebParamLongitudeRange.value() * DEGREES_TO_MI) + " mi";
        lv_label_update_text(no_flights_range_label, lat_lon_range.c_str());
        lv_label_update_text(no_flights_location_label, iotWebParamLocation.value());
        lv_label_update_text(no_flights_timezone_label, iotWebParamTimeZone.value());
        next_update = now + flight_milliseconds_noflights;
        return;
      }

      log_i("Starting flight display cycle");
      display_cycle = 0;
      it = flights.cbegin();
      display_cycle = 0;
    }
    else
    {
      if (it == flights.cend())
      {
        it = flights.cbegin();
        display_cycle++;
        log_i("#Display cycle: %d. Reached end of flight list. Restarting from beginning.", display_cycle);
      }
    }

    display_flight(it++);
    next_update = now + flight_milliseconds;
  }
}

void display_flights_clock()
{
  // Keep the flight list updated; when there is nothing to show, display the clock instead.
  display_flights();
  if (flights.empty() && !flights_update_error)
    display_clock();
}

void loop()
{
  // LVGL
  lv_timer_handler();

  // Web configuration
  iotWebConf.doLoop();

  static auto last_network_state = iotwebconf::NetworkState::Boot;

  auto network_state = iotWebConf.getState();
  if (network_state != last_network_state)
  {
    last_network_state = network_state;
    display_network_state(network_state);
  }

  // TOP BUTTON cycles through the display modes: flights, clock and flights/clock.
  if (top_button_event)
  {
    top_button_event = false;
    if (network_state == iotwebconf::NetworkState::OnLine)
    {
      switch (display_mode)
      {
      case DISPLAY_MODE_FLIGHTS:
        enter_clock_mode();
        break;

      case DISPLAY_MODE_CLOCK:
        enter_flights_clock_mode();
        break;

      default:
        enter_flights_mode();
        break;
      }
    }
  }

  // BOTTOM BUTTON changes the PWM brightness of the backlight.
  if (bottom_button_event)
  {
    bottom_button_event = false;
    backlight_pwm_duty_step = (++backlight_pwm_duty_step) % (sizeof(backlight_pwm_duty_steps) / sizeof(backlight_pwm_duty_steps[0]));
    set_backlight_pwm_duty(backlight_pwm_duty_steps[backlight_pwm_duty_step]);
  }

  switch (network_state)
  {
  case iotwebconf::NetworkState::OffLine:
    next_update = 0ul;
    break;

  case iotwebconf::NetworkState::OnLine:
    switch (display_mode)
    {
    case DISPLAY_MODE_CLOCK:
      display_clock();
      break;

    case DISPLAY_MODE_FLIGHTS_CLOCK:
      display_flights_clock();
      break;

    default:
      display_flights();
      break;
    }
    break;
  }

  yield();
}

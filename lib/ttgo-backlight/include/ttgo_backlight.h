#pragma once

#include <TFT_eSPI.h>

#define TTGO_DEFAULT_BACKLIGHT_INTENSITY    80

extern void ttgo_backlight_init();
extern void ttgo_backlight_intensity(byte intensity);
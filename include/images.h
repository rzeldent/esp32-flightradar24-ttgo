//*******************************************************************************
// Type: LVGL
// ******************************************************************************

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


constexpr unsigned char image_no_internet_map[] = { 
// PNG Data

};
const lv_img_dsc_t image_no_internet = {
  .header = {
    .cf = LV_IMG_SRC_VARIABLE,
    .always_zero = 0,
    .w = 240,
    .h = 135},
  .data_size = sizeof(image_no_internet_map),
  .data = image_no_internet_map};

constexpr unsigned char image_wifi_map[] = { 
// PNG Data

};
const lv_img_dsc_t image_wifi = {
  .header = {
    .cf = LV_IMG_SRC_VARIABLE,
    .always_zero = 0,
    .w = 240,
    .h = 135},
  .data_size = sizeof(image_wifi_map),
  .data = image_wifi_map};

constexpr unsigned char image_splash_map[] = { 
// PNG Data

};
const lv_img_dsc_t image_splash = {
  .header = {
    .cf = LV_IMG_SRC_VARIABLE,
    .always_zero = 0,
    .w = 240,
    .h = 135},
  .data_size = sizeof(image_splash_map),
  .data = image_splash_map};

constexpr unsigned char image_error_map[] = { 
// PNG Data

};
const lv_img_dsc_t image_error = {
  .header = {
    .cf = LV_IMG_SRC_VARIABLE,
    .always_zero = 0,
    .w = 240,
    .h = 118},
  .data_size = sizeof(image_error_map),
  .data = image_error_map};



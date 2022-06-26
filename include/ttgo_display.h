#pragma once

// TFT Pins has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
// #define TFT_MOSI            19
// #define TFT_SCLK            18
// #define TFT_CS              5
// #define TFT_DC              16
// #define TFT_RST             23
// #define TFT_BL              4   // Display backlight control pin

// SD Card definitions
#define SD_CARD_CS       33
#define SD_CARD_SCLK     25
#define SD_CARD_MISO     27
#define SD_CARD_MOSI     26

// ADC_EN is the ADC detection enable port
// If the USB port is used for power supply, it is turned on by default.
// If it is powered by battery, it needs to be set to high level
#define GPIO_ADC_EN 14
#define PIN_ADC 34

// GPIO of the buttons on the TTGO Display
#define GPIO_BUTTON_TOP 35
#define GPIO_BUTTON_BOTTOM 0

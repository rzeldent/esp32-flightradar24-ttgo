#include <ttgo_backlight.h>

// TTGO Display PWM properties
const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;

void ttgo_backlight_init()
{
    log_i("Initializing PWM for TFT backlight");
    pinMode(TFT_BL, OUTPUT);                // Set backlight pin to output mode
    digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
    ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
    ledcAttachPin(TFT_BL, pwmLedChannelTFT);
}

void ttgo_backlight_intensity(byte intensity)
{
    log_i("Setting backlight intensity to: %d", intensity);
    ledcWrite(pwmLedChannelTFT, intensity);
}
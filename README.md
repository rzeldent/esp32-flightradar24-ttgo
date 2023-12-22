# FlightRadar24-TTGO

[![Platform IO CI](https://github.com/rzeldent/esp32-flightradar24-ttgo/actions/workflows/main.yml/badge.svg)](https://github.com/rzeldent/esp32-flightradar24-ttgo/actions/workflows/main.yml)

Real-time flights display. No login or account required.
Easy configuration through the web interface.

![FlightRadar](assets/20220909_221059.jpg)

Display flights in your area and display them on the screen of the ESP32 TTGO-Display or LilyGo-T-Display-S3 module.
Under the hood it uses the API of [FlightRadar24.com](https://www.flightradar24.com/) but only for flight updates.
Internally there is a database with airport, aircraft and airline data with graphics to minimize the requests.

This application retrieves the current flights near a configured location and displays them sequentially on the display.

![Example1](assets/20220909_221101.jpg)
![Example2](assets/20220909_221104.jpg)

Example of layout on LilyGo-T-Display-S3
![Example3](assets/20231022_000000.jpeg)

## History

|             |                                                                      |
| :---------- | :------------------------------------------------------------------- |
| Oct 21 2023 | Added configuration from LilyGo-T-Display-S3 with help from ulihuber |
| Oct 25 2022 | Use LVGL for graphics                                                |
| Oct 15 2022 | Filtering for airborne/grounded/gliders/vehicles                     |
| Oct 14 2022 | Added vertical speed                                                 |
| Oct 2 2022  | Bootstrap for HTML overview                                          |
| Jun 16 2022 | Wifi manager for configuration                                       |
| Jun 15 2022 | Use time zones                                                       |
| Apr 27 2022 | Import aircraft types                                                |
| Dec 5 2021  | Compressing of RGB565                                                |
| Nov 21 2021 | Import airlines from Wiki page                                       |
| Nov 8 2021  | New airline logos                                                    |
| Oct 31 2021 | Added heading, altitude and speed                                    |
| Oct 6 2021  | Move images from SPIFF to code                                       |
| May 25 2021 | GUI update                                                           |
| Dec 26 2019 | Initial version: The "birth" of the project                          |

## Features

The FlightRadar firmware offers the following features:

- Lookup of airplane type and specifics (manufacturer, type, description, engine type and count)
- Lookup of carrier and (if available) display the logo
- Display GPS location, registration, altitude, heading, speed and vertical speed of the airplane
- Lookup of the full name for the from- and to airports name and region, lat/lon
- Lookup and display flag for the countries
- No account required, ony WiFi with internet connection!
- Minimal interaction with FlightRadar24; database and graphics are present in firmware
- Configuration using a Web interface
- HTML status screen
- Stay in AP mode at reset (Resetting + pressing top button)
- Clock mode

## Usage

Download the repo, open it in [**PlatformIO**](https://platformio.org/) and flash it to the ESP32-TTGO-Display.
When installed make a WiFi connection to the device, initially called FlightRadar and configure the access point parameters.
After configuration the device starts updating the flights in the configured area.

When pressing the top button, the device switches to clock mode: just showing the date and time.
To return to the flights mode, press the top button again.

## Installing and running PlatformIO

Take the following steps to install platformIo. There is a lot of information on their site!

- Install Visual Studio Code
- From the Extensions menu select PlatformIo
- Clone this repository, and open the folder in your workspace
- Compile and upload to the ESP32-TTGO-Display / LilyGo-T-Display-S3

## Status overview

When connected to the FlightRadar, the main screen is shown; the overview.
Here details about the device, network and settings are shown.
![Status page](assets/status.png)

## Modifying the configuration

The configuration can be changed using a web browser. Connecting to the flight radar can be done in two ways:

- During startup, connect to the access point `FlightRadar` and log in. In case the browser does not open the page immediately, the url is [http://192.168.4.1](http://192.168.4.1).
- Find the internal IP address of the FlightRadar (from your home router) and enter the url.
- When the password is lost, a fix is to completely erase the ESP32 using the pio run -t erase command.
  This will reset the device including configuration.
  If using the esptool, you can do this using esptool.py --chip esp32 --port /dev/ttyUSB0 erase_flash.
  However, after erasing, reflashing of the firmware is required.

![Settings page](assets/configuration.png)

Configuration options:

- The WIFI SSID and WIFI password for changing the configuration,
- The SSID and password for the network to connect to with internet access,
- The latitude and longitude (decimal format) to observe,
- The range in degrees of the area to observe,
- Filtering on:
  - Include airborne
  - Include grounded
  - Include gliders
  - Include vehicles on the ground
- The timezone,
- Usage of metric or imperial units

Some tips:

- Sometimes after configuration a reboot is required.
  If the error screen is shown that it is unable to make a connection, first try to reboot the device,
- When booting, the device waits 30 seconds for a connection.
  Make a connection to the SSID indicated on the screen using the AP password,
- When connected, go to the ip of the device and, when prompted for the credentials, enter 'admin' and the AP password.
  This field is **required** before saving the credentials,
- When the password is lost, holding the top button while booting will clear the configuration.
- When finished disconnect from the wireless network. This should reset the flight radar.
  Resetting is also a good alternative...

## Case / Enclosure

Please take a look at the STL file to create a case for the FlightRadar to host the TTGO-Display and a battery.
Thanks to Erwin Reid for creating the models.

Files can be found at [Thingverse](https://www.thingiverse.com/thing:5412296/files).

![Erwin Reid case](assets/featured_preview_capture.jpg)

Another option is from LilyGo (AliExpress).
With a little modification, the "LILYGO® T-Display Shell ABS Accessories For T-Display T-PicoC3 T-Display RP2040" can be adapted by removing the stands in the case.

These can be ordered at [https://www.aliexpress.com/item/1005004507656890.html](https://www.aliexpress.com/item/1005004507656890.html)

![LiliGo Case](assets/S6573ff3851164766ab1a3648b04ba30b1.jpg)

## Suggestions

Suggestions especially to faulty or missing logo's, airlines etc are welcome. Please make a Pull request and, after verification, this will be added to the main version.

## Credits

Thanks to [FlightRadar24.com](https://www.flightradar24.com/) to be able to hook into their API.

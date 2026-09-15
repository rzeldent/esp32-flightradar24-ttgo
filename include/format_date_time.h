#pragma once

#include <Arduino.h>

constexpr const char* localtime_format_date_metric = "%A %d-%m-%Y";
constexpr const char* localtime_format_date_imperial = "%A %m/%d/%Y"; 

constexpr const char* localtime_format_time_metric = "%H:%M:%S";
constexpr const char* localtime_format_time_imperial = "%I:%M:%S %p";

constexpr const char* localtime_format_date_time_metric = "%A %d-%m-%Y %H:%M:%S";
constexpr const char* localtime_format_date_time_imperial = "%A %m/%d/%Y %I:%M:%S %p";

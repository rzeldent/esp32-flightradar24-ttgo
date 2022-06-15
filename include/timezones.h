#include <Timezone.h>

typedef struct time_zone_info
{
    const char *location;
    const Timezone timezone_info;
} time_zone_info_t;

// Australia Eastern Time Zone (Sydney, Melbourne)
constexpr TimeChangeRule tcr_aEDT = {"AEDT", First, Sun, Oct, 2, 660}; // UTC + 11 hours
constexpr TimeChangeRule tcr_aEST = {"AEST", First, Sun, Apr, 3, 600}; // UTC + 10 hours
// Moscow Standard Time (MSK, does not observe DST)
constexpr TimeChangeRule tcr_MSK = {"MSK", Last, Sun, Mar, 1, 180};
// Central European Time (Frankfurt, Paris)
constexpr TimeChangeRule tcr_CEST = {"CEST", Last, Sun, Mar, 2, 120}; // Central European Summer Time
constexpr TimeChangeRule tcr_CET = {"CET ", Last, Sun, Oct, 3, 60};   // Central European Standard Time
// United Kingdom (London, Belfast)
constexpr TimeChangeRule tcr_BST = {"BST", Last, Sun, Mar, 1, 60}; // British Summer Time
constexpr TimeChangeRule tcr_GMT = {"GMT", Last, Sun, Oct, 2, 0};  // Standard Time
// UTC
constexpr TimeChangeRule tcr_UTC = {"UTC", Last, Sun, Mar, 1, 0}; // UTC
// US Eastern Time Zone (New York, Detroit)
constexpr TimeChangeRule tcr_usEDT = {"EDT", Second, Sun, Mar, 2, -240}; // Eastern Daylight Time = UTC - 4 hours
constexpr TimeChangeRule tcr_usEST = {"EST", First, Sun, Nov, 2, -300};  // Eastern Standard Time = UTC - 5 hours
// US Central Time Zone (Chicago, Houston)
constexpr TimeChangeRule tcr_usCDT = {"CDT", Second, Sun, Mar, 2, -300};
constexpr TimeChangeRule tcr_usCST = {"CST", First, Sun, Nov, 2, -360};
// US Mountain Time Zone (Denver, Salt Lake City)
constexpr TimeChangeRule tcr_usMDT = {"MDT", Second, Sun, Mar, 2, -360};
constexpr TimeChangeRule tcr_usMST = {"MST", First, Sun, Nov, 2, -420};
#define TS_usMT tcr_usMDT, tcr_usMST
// Arizona is US Mountain Time Zone but does not use DST
// US Pacific Time Zone (Las Vegas, Los Angeles)
constexpr TimeChangeRule tcr_usPDT = {"PDT", Second, Sun, Mar, 2, -420};
constexpr TimeChangeRule tcr_usPST = {"PST", First, Sun, Nov, 2, -480};

time_zone_info time_zone_info_list[] = {
    {"Australia Eastern Time Zone (Sydney, Melbourne)", Timezone(tcr_aEDT, tcr_aEST)},
    {"Moscow Standard Time", Timezone(tcr_MSK, tcr_MSK)},
    {"Central European Time", Timezone(tcr_CEST, tcr_CET)},
    {"United Kingdom (London, Belfast)", Timezone(tcr_BST, tcr_GMT)},
    {"UTC", Timezone(tcr_UTC, tcr_UTC)},
    {"US Eastern Time Zone (New York, Detroit)", Timezone(tcr_usEDT, tcr_usEST)},
    {"US Central Time Zone (Chicago, Houston)", Timezone(tcr_usCDT, tcr_usCST)},
    {"US Mountain Time Zone (Denver, Salt Lake City)", Timezone(tcr_usMDT, tcr_usMST)},
    {"Mountain Time (Arizona)", Timezone(tcr_usMST, tcr_usMST)},
    {"US Pacific Time Zone (Las Vegas, Los Angeles)", Timezone(tcr_usPDT, tcr_usPST)}};

#define TZ_CE   tcr_CEST, tcr_CET
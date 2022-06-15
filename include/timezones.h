#include <Timezone.h>

// Australia Eastern Time Zone (Sydney, Melbourne)
constexpr TimeChangeRule tcr_aEDT = {"AEDT", First, Sun, Oct, 2, 60 * 11}; // UTC + 11 hours
constexpr TimeChangeRule tcr_aEST = {"AEST", First, Sun, Apr, 3, 60 * 10}; // UTC + 10 hours
// Moscow Standard Time (Moscow), does not observe DST)
constexpr TimeChangeRule tcr_MSK = {"MSK", Last, Sun, Mar, 1, 60 * 3};
// Central European Time (Frankfurt, Paris)
constexpr TimeChangeRule tcr_CEST = {"CEST", Last, Sun, Mar, 2, 60 * 2}; // Central European Summer Time
constexpr TimeChangeRule tcr_CET = {"CET ", Last, Sun, Oct, 3, 60 * 1};  // Central European Standard Time
// United Kingdom (London, Belfast)
constexpr TimeChangeRule tcr_BST = {"BST", Last, Sun, Mar, 1, 60 * 1}; // British Summer Time
constexpr TimeChangeRule tcr_GMT = {"GMT", Last, Sun, Oct, 2, 60 * 0}; // Standard Time
// UTC
constexpr TimeChangeRule tcr_UTC = {"UTC", Last, Sun, Mar, 1, 60 * 0}; // UTC
// US Eastern Time (New York, Detroit)
constexpr TimeChangeRule tcr_usEDT = {"EDT", Second, Sun, Mar, 2, 60 * -4}; // Eastern Daylight Time = UTC - 4 hours
constexpr TimeChangeRule tcr_usEST = {"EST", First, Sun, Nov, 2, 60 * -5};  // Eastern Standard Time = UTC - 5 hours
// US Central Time (Chicago, Houston)
constexpr TimeChangeRule tcr_usCDT = {"CDT", Second, Sun, Mar, 2, 60 * -5};
constexpr TimeChangeRule tcr_usCST = {"CST", First, Sun, Nov, 2, 60 * -6};
// US Mountain Time (Denver, Salt Lake City)
constexpr TimeChangeRule tcr_usMDT = {"MDT", Second, Sun, Mar, 2, 60 * -6};
constexpr TimeChangeRule tcr_usMST = {"MST", First, Sun, Nov, 2, 60 * -7};
// US Mountain Time (Arizona) equals US Mountain Time Zone but does not use DST
// US Pacific Time (Las Vegas, Los Angeles)
constexpr TimeChangeRule tcr_usPDT = {"PDT", Second, Sun, Mar, 2, 60 * -7};
constexpr TimeChangeRule tcr_usPST = {"PST", First, Sun, Nov, 2, 60 * -8};


#define TZ_CE tcr_CEST, tcr_CET
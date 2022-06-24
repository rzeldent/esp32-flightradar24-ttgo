#include <flight_info.h>

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <esp32-hal-log.h>

std::list<flight_info> get_flights(float latitude, float longitude, float range_latitude, float range_longitude)
{
    const String bounds = String(latitude + range_latitude) + "," + String(latitude - range_latitude) + "," + String(longitude - range_longitude) + "," + String(longitude + range_longitude);
    const String flight_data_url = "http://data-live.flightradar24.com/zones/fcgi/feed.js?bounds=" + bounds + "&faa=1&satellite=1&mlat=1&flarm=1&adsb=1&gnd=0&air=1&vehicles=0&estimated=1&maxage=14400&gliders=1&stats=0";

    HTTPClient client;
    log_i("Request states=%s", flight_data_url.c_str());
    client.begin(flight_data_url);
    const auto httpResultCode = client.GET();
    if (httpResultCode != HTTP_CODE_OK)
    {
        client.end();
        log_e("Get error code=%d", httpResultCode);
        return std::list<flight_info>();
    }

    auto response = client.getString();
    log_d("Body=%s", response.c_str());
    // Parse JSON states object 32k
    DynamicJsonDocument doc_flight_data(32 * 1024);
    const auto error = deserializeJson(doc_flight_data, response);
    if (error != DeserializationError::Ok)
    {
        client.end();
        log_e("Deserialize. Error=%s", error.c_str());
        return std::list<flight_info>();
    }

    client.end();
    
    std::list<flight_info> flights;
    auto flight_data_root = doc_flight_data.as<JsonObject>();
    for (const auto kvp : flight_data_root)
    {
        if (!kvp.value().is<JsonArray>())
            continue;

        log_i("KVP=%s", kvp.key().c_str());
        auto items = kvp.value().as<JsonArray>();
        struct flight_info flight
        {
            .icao = strtol(items[0].as<const char*>(), nullptr, 0x10),
            .latitude = items[1].as<const float>(),
            .longitude = items[2].as<const float>(),
            .track = items[3].as<const int>(),
            .altitude = items[4].as<const int>(),
            .speed = items[5].as<const int>(),
            .squawk = (ushort)atoi(items[6].as<const char*>()),
            .radar = items[7].as<const char*>(),
            .type_designator = items[8].as<const char*>(),
            .registration = items[9].as<const char*>(),
            .timestamp = items[10].as<time_t>(),
            .from = items[11].as<const char*>(),
            .to = items[12].as<const char*>(),
            .flight = items[13].as<const char*>(),
            .flight_operator = items[18].as<const char*>()
        };
        flights.push_back(flight);
    }
    return flights;
}
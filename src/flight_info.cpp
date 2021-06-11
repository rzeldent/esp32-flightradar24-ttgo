#include <flight_info.h>

#include <HTTPClient.h>

std::shared_ptr<std::list<flight_info>> get_flights(float latitude, float longitude, float range_latitude, float range_longitude)
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
        return nullptr;
    }

    String response = client.getString();
    log_d("Body=%s", response.c_str());
    // Parse JSON states object
    DynamicJsonDocument doc_flight_data(8192);
    const auto error = deserializeJson(doc_flight_data, response);
    if (error != DeserializationError::Ok)
    {
        client.end();
        log_e("Deserialize. Error=%s", error.c_str());
        return nullptr;
    }

    client.end();
    std::shared_ptr<std::list<flight_info>> flights(new std::list<flight_info>);
    JsonObject flight_data_root = doc_flight_data.as<JsonObject>();
    for (JsonPair kvp : flight_data_root)
    {
        if (!kvp.value().is<JsonArray>())
            continue;

        log_i("KVP=%s", kvp.key().c_str());
        auto items = kvp.value().as<JsonArray>();
        struct flight_info flight
        {
            .icao = items[0].as<const char *>(),
            .latitude = items[1].as<const char *>(),
            .longitude = items[2].as<const char *>(),
            .track = items[3].as<const char *>(),
            .altitude = items[4].as<const char *>(),
            .speed = items[5].as<const char *>(),
            .squawk = items[6].as<const char *>(),
            .radar = items[7].as<const char *>(),
            .type = items[8].as<const char *>(),
            .registration = items[9].as<const char *>(),
            .timestamp = items[10].as<const char *>(),
            .from = items[11].as<const char *>(),
            .to = items[12].as<const char *>(),
            .flight = items[13].as<const char *>(),
            .flight_operator = items[15].as<const char *>()
        };
        flights->push_back(flight);
    }
    return flights;
}
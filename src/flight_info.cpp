#include <flight_info.h>

#include <HTTPClient.h>

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

    String response = client.getString();
    log_d("Body=%s", response.c_str());
    // Parse JSON states object
    DynamicJsonDocument doc_flight_data(8192);
    const auto error = deserializeJson(doc_flight_data, response);
    if (error != DeserializationError::Ok)
    {
        client.end();
        log_e("Deserialize. Error=%s", error.c_str());
        return std::list<flight_info>();
    }

    client.end();
    
    std::list<flight_info> flights;
    JsonObject flight_data_root = doc_flight_data.as<JsonObject>();
    for (JsonPair kvp : flight_data_root)
    {
        if (!kvp.value().is<JsonArray>())
            continue;

        log_i("KVP=%s", kvp.key().c_str());
        auto items = kvp.value().as<JsonArray>();
        struct flight_info flight
        {
            .icao = items[0].as<String>(),
            .latitude = items[1].as<float>(),
            .longitude = items[2].as<float>(),
            .track = items[3].as<int>(),
            .altitude = items[4].as<int>(),
            .speed = items[5].as<int>(),
            .squawk = items[6].as<String>(),
            .radar = items[7].as<String>(),
            .type = items[8].as<String>(),
            .registration = items[9].as<String>(),
            .timestamp = items[10].as<ulong>(),
            .from = items[11].as<String>(),
            .to = items[12].as<String>(),
            .flight = items[13].as<String>(),
            .flight_operator = items[15].as<String>()
        };
        flights.push_back(flight);
    }
    return flights;
}
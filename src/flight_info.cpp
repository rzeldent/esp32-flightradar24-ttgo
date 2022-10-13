#include <flight_info.h>

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <esp32-hal-log.h>
#include <http_status.h>

bool get_flights(float latitude, float longitude, float range_latitude, float range_longitude, std::list<flight_info> &flights, String &error_message)
{
    const String bounds = String(latitude + range_latitude / 2.0) + "," + String(latitude - range_latitude / 2.0) + "," + String(longitude - range_longitude / 2.0) + "," + String(longitude + range_longitude / 2.0);
    const String flight_data_url = "http://data-live.flightradar24.com/zones/fcgi/feed.js?bounds=" + bounds + "&faa=1&satellite=1&mlat=1&flarm=1&adsb=1&gnd=1&air=1&vehicles=0&estimated=1&maxage=14400&gliders=1&stats=0";

    flights.clear();
    error_message = "";

    HTTPClient client;
    log_i("Request states=%s", flight_data_url.c_str());
    if (!client.begin(flight_data_url))
    {
        error_message = "Failed to start client. DNS/TCP error?";
        log_e("%s", error_message.c_str());
        return false;
    }

    const auto httpResultCode = client.GET();
    if (httpResultCode != HTTP_CODE_OK)
    {
        client.end();
        error_message = String(httpResultCode) + " " + (httpResultCode < 0 ? client.errorToString(httpResultCode) : http_status_reason(httpResultCode));
        log_e("HTTP error: %d (%s)", httpResultCode, error_message);
        return false;
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
        error_message = error.c_str();
        return false;
    }

    client.end();

    auto flight_data_root = doc_flight_data.as<JsonObject>();
    for (const auto &kvp : flight_data_root)
    {
        if (!kvp.value().is<JsonArray>())
            continue;

        log_i("KVP=%s", kvp.key().c_str());
        auto items = kvp.value().as<JsonArray>();
        struct flight_info flight
        {
            .icao_address = items[0].as<const char *>(),
            .latitude = items[1].as<const float>(),
            .longitude = items[2].as<const float>(),
            .heading = items[3].as<const int>(),
            .altitude = items[4].as<const int>(),
            .ground_speed = items[5].as<const int>(),
            .squawk = items[6].as<const char *>(),
            .radar = items[7].as<const char *>(),
            .aircraft_code = items[8].as<const char *>(),
            .registration = items[9].as<const char *>(),
            .timestamp = items[10].as<time_t>(),
            .iata_origin_airport = items[11].as<const char *>(),
            .iata_destination_airport = items[12].as<const char *>(),
            .flight = items[13].as<const char *>(),
            .on_ground = items[14].as<const bool>(),
            .vertical_speed = items[15].as<const int>(),
            .call_sign = items[16].as<const char *>(),
            .icao_airline = items[18].as<const char *>()
        };
        flights.push_back(flight);
    }

    return true;
}

String flight_info::toString() const
{
    return "ICAO " + icao_address + ": Flight " + flight + " from " + iata_origin_airport + " to " + iata_destination_airport + ", Squawk: " + String(squawk) + ", Radar: " + radar + ", Registration: " + registration + ", Lat: " + String(latitude) + ", Lon: " + String(longitude) + ", Altitude: " + String(altitude) + " ft, Ground speed: " + ground_speed + " kts, Heading: " + String(heading) + " degrees, Vertical speed: " + String(vertical_speed) + ", Aircraft code: " + aircraft_code + ", Airline: " + icao_airline;
}
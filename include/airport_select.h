#pragma once

#include <string.h>

#include <IotWebConf.h>
#include <IotWebConfTParameter.h>

#include <airport.h>
#include <html_escape.h>

/**
 * Location parameter, rendered as a drop down with all airports. The value is the IATA code
 * of the selected airport; an empty value means the latitude and longitude are set manually.
 *
 * The options are sent to the client in chunks, because the list with all airports cannot be
 * built as one string in memory.
 */
class AirportSelectParameter : public iotwebconf::TextTParameter<32>
{
public:
    AirportSelectParameter(const char *id, const char *label, const char *defaultValue) : // ConfigItemBridge is a virtual base, so it must be initialized by the most derived class
                                                                                          iotwebconf::ConfigItemBridge(id),
                                                                                          iotwebconf::TextTParameter<32>(id, label, defaultValue)
    {
    }

    // Latitude and longitude that are set to the position of the selected airport
    void setPosition(iotwebconf::FloatTParameter *latitude, iotwebconf::FloatTParameter *longitude)
    {
        _latitude = latitude;
        _longitude = longitude;

        // Show the position of the selected airport in the latitude and longitude fields right
        // away, without a round trip to the device. The script is added to the config page.
        _customHtml = String("onchange=\"airport_selected(this, '") + _latitude->getId() + "', '" + _longitude->getId() + "')\"";
        this->customHtml = _customHtml.c_str();
    }

    // Remember the selection that is currently applied to the latitude and longitude
    void rememberSelection() { _selection = this->value(); }

    // When another airport is selected, the position of that airport is applied to the latitude
    // and longitude. This cannot be done in update(), because the latitude and longitude are
    // updated from the form after this parameter; it is called just before the configuration is
    // stored instead.
    void applySelection()
    {
        if (_latitude == nullptr || _longitude == nullptr || _selection == this->value())
            return;

        _selection = this->value();
        const auto airport = lookup_airport(_selection.c_str());
        if (airport == nullptr)
            return;

        // The position in the table is scaled by 1,000,000
        _latitude->value() = (float)airport->latitude / 1000000.0f;
        _longitude->value() = (float)airport->longitude / 1000000.0f;
        log_i("Position of %s (%s) set to %f, %f", airport->name, _selection.c_str(), _latitude->value(), _longitude->value());
    }

protected:
    void renderHtml(bool dataArrived, iotwebconf::WebRequestWrapper *webRequestWrapper) override
    {
        const bool hasValueFromPost = webRequestWrapper->hasArg(this->getId());
        const String valueFromPost = hasValueFromPost ? webRequestWrapper->arg(this->getId()) : String();

        String item = FPSTR(IOTWEBCONF_HTML_FORM_SELECT_PARAM);
        item.replace("{b}", this->label);
        item.replace("{i}", this->getId());
        item.replace("{c}", this->customHtml == nullptr ? "" : this->customHtml);
        item.replace("{s}", this->errorMessage == nullptr ? "" : "de");
        item.replace("{e}", this->errorMessage == nullptr ? "" : this->errorMessage);

        // The options are inserted at the {o} marker, so the parts around it can be sent
        // separately with the options streamed in between.
        const int marker = item.indexOf("{o}");
        webRequestWrapper->sendContent(item.substring(0, marker));
        stream_airports(webRequestWrapper, hasValueFromPost, valueFromPost);
        webRequestWrapper->sendContent(item.substring(marker + 3));
    }

private:
    // Approximate size of the chunks in which the options are sent to the client
    constexpr static uint16_t chunk_size = 2048;

    // The airports are streamed in the order of the airport table (sorted on IATA code)
    void stream_airports(iotwebconf::WebRequestWrapper *webRequestWrapper, bool hasValueFromPost, const String &valueFromPost)
    {
        String chunk;
        chunk.reserve(chunk_size + 128);

        // Option to leave the latitude and longitude unchanged
        const bool manual = hasValueFromPost ? valueFromPost.length() == 0 : this->value()[0] == '\0';
        chunk += "<option value=''";
        if (manual)
            chunk += " selected";
        chunk += ">Set the latitude and longitude manually</option>\n";

        for (size_t i = 0; i < airport_count; i++)
        {
            // The IATA code is not terminated in the table
            const char iata_airport[] = {airports[i].iata_airport[0], airports[i].iata_airport[1], airports[i].iata_airport[2], '\0'};
            const bool selected = hasValueFromPost ? valueFromPost.equals(iata_airport) : strcmp(this->value(), iata_airport) == 0;
            chunk += "<option value='" + String(iata_airport) + "'";
            if (selected)
                chunk += " selected";

            chunk += "> " + String(iata_airport) + " - " + escape_html(airports[i].name) + " - " + escape_html(airports[i].city) + " (" + escape_html(get_country(airports[i].country)->name) + ") </option>\n";

            if (chunk.length() >= chunk_size)
            {
                webRequestWrapper->sendContent(chunk);
                chunk = "";
            }
        }

        if (chunk.length() > 0)
            webRequestWrapper->sendContent(chunk);
    }

    // Latitude and longitude of the selected airport
    iotwebconf::FloatTParameter *_latitude = nullptr;
    iotwebconf::FloatTParameter *_longitude = nullptr;
    // The selection that was applied to the latitude and longitude
    String _selection;
    // The custom html with the onchange handler; customHtml points into this string
    String _customHtml;
};

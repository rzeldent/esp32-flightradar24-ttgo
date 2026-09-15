#pragma once

#include <Arduino.h>

inline String escape_html(const String &text)
{
    String escaped;
    escaped.reserve(text.length() + 8);
    for (const char *c = text.c_str(); *c != '\0'; c++)
    {
        switch (*c)
        {
        case '&':
            escaped += "&amp;";
            break;
        case '<':
            escaped += "&lt;";
            break;
        case '>':
            escaped += "&gt;";
            break;
        case '"':
            escaped += "&quot;";
            break;
        case '\'':
            escaped += "&#39;";
            break;
        default:
            escaped += *c;
            break;
        }
    }

    return escaped;
}

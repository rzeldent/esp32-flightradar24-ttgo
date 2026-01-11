#pragma once

#include <string.h>
#include <Arduino.h>

/**
 * Convert non-latin accented characters to their ASCII equivalents
 * Handles common diacritics: á, é, í, ó, ú, ä, ë, ö, ü, ñ, ç, etc.
 */
inline String format_to_latin(const char* input)
{
    if (!input)
        return String();

    String output;
    for (auto i = 0; input[i] != '\0'; i++)
    {
        auto c = (unsigned char)input[i];
        // Handle UTF-8 multi-byte sequences for accented characters
        if (c >= 0xC0)
        {
            // Ensure there is a continuation byte before accessing input[i + 1]
            if (input[i + 1] == '\0')
            {
                // Truncated or malformed multi-byte sequence at end of string
                output += '?';
                continue;
            }
            auto next = (unsigned char)input[i + 1];
           
            // Common Latin-1 supplement characters (0xC0-0xFF range in UTF-8)
            switch (c)
            {
                case 0xC3:  // UTF-8 Latin Extended-A block (0xC380-0xC3BF)
                    switch (next)
                    {
                        // Uppercase accents
                        case 0x80: output += 'A'; break;  // À
                        case 0x81: output += 'A'; break;  // Á
                        case 0x82: output += 'A'; break;  // Â
                        case 0x83: output += 'A'; break;  // Ã
                        case 0x84: output += 'A'; break;  // Ä
                        case 0x85: output += 'A'; break;  // Å
                        case 0x86: output += 'A'; break;  // Æ
                        case 0x87: output += 'C'; break;  // Ç
                        case 0x88: output += 'E'; break;  // È
                        case 0x89: output += 'E'; break;  // É
                        case 0x8A: output += 'E'; break;  // Ê
                        case 0x8B: output += 'E'; break;  // Ë
                        case 0x8C: output += 'I'; break;  // Ì
                        case 0x8D: output += 'I'; break;  // Í
                        case 0x8E: output += 'I'; break;  // Î
                        case 0x8F: output += 'I'; break;  // Ï
                        case 0x90: output += 'D'; break;  // Ð
                        case 0x91: output += 'N'; break;  // Ñ
                        case 0x92: output += 'O'; break;  // Ò
                        case 0x93: output += 'O'; break;  // Ó
                        case 0x94: output += 'O'; break;  // Ô
                        case 0x95: output += 'O'; break;  // Õ
                        case 0x96: output += 'O'; break;  // Ö
                        case 0x97: output += 'x'; break;  // ×
                        case 0x98: output += 'O'; break;  // Ø
                        case 0x99: output += 'U'; break;  // Ù
                        case 0x9A: output += 'U'; break;  // Ú
                        case 0x9B: output += 'U'; break;  // Û
                        case 0x9C: output += 'U'; break;  // Ü
                        case 0x9D: output += 'Y'; break;  // Ý
                        case 0x9E: output += 'T'; break;  // Þ
                        case 0xA0: output += 'a'; break;  // à
                        case 0xA1: output += 'a'; break;  // á
                        case 0xA2: output += 'a'; break;  // â
                        case 0xA3: output += 'a'; break;  // ã
                        case 0xA4: output += 'a'; break;  // ä
                        case 0xA5: output += 'a'; break;  // å
                        case 0xA6: output += 'a'; break;  // æ
                        case 0xA7: output += 'c'; break;  // ç
                        case 0xA8: output += 'e'; break;  // è
                        case 0xA9: output += 'e'; break;  // é
                        case 0xAA: output += 'e'; break;  // ê
                        case 0xAB: output += 'e'; break;  // ë
                        case 0xAC: output += 'i'; break;  // ì
                        case 0xAD: output += 'i'; break;  // í
                        case 0xAE: output += 'i'; break;  // î
                        case 0xAF: output += 'i'; break;  // ï
                        case 0xB0: output += 'o'; break;  // ð
                        case 0xB1: output += 'n'; break;  // ñ
                        case 0xB2: output += 'o'; break;  // ò
                        case 0xB3: output += 'o'; break;  // ó
                        case 0xB4: output += 'o'; break;  // ô
                        case 0xB5: output += 'o'; break;  // õ
                        case 0xB6: output += 'o'; break;  // ö
                        case 0xB7: output += '/'; break;  // ÷
                        case 0xB8: output += 'o'; break;  // ø
                        case 0xB9: output += 'u'; break;  // ù
                        case 0xBA: output += 'u'; break;  // ú
                        case 0xBB: output += 'u'; break;  // û
                        case 0xBC: output += 'u'; break;  // ü
                        case 0xBD: output += 'y'; break;  // ý
                        case 0xBE: output += 't'; break;  // þ
                        case 0xBF: output += 'y'; break;  // ÿ
                        default: output += '?'; break;
                    }
                    i++;
                    break;

                case 0xC4:  // UTF-8 Latin Extended-A block
                    switch (next)
                    {
                        case 0x80: output += 'A'; break;  // Ā
                        case 0x81: output += 'a'; break;  // ā
                        case 0x84: output += 'A'; break;  // Ą
                        case 0x85: output += 'a'; break;  // ą
                        case 0x8C: output += 'C'; break;  // Č
                        case 0x8D: output += 'c'; break;  // č
                        case 0xB8: output += 'k'; break;  // ĸ
                        case 0xB9: output += 'L'; break;  // Ĺ
                        case 0xBA: output += 'l'; break;  // ĺ
                        default: output += '?'; break;
                    }
                    i++;
                    break;
                case 0xC5:  // UTF-8 Latin Extended-B block
                    switch (next) {
                        case 0x9A: output += 'S'; break;  // Ś
                        case 0x9B: output += 's'; break;  // ś
                        case 0x9C: output += 'S'; break;  // Ŝ
                        case 0x9D: output += 's'; break;  // ŝ
                        case 0xBB: output += 'Z'; break;  // Ż
                        case 0xBC: output += 'z'; break;  // ż
                        case 0xBD: output += 'Z'; break;  // Ž
                        case 0xBE: output += 'z'; break;  // ž
                        default: output += '?'; break;
                    }
                    i++;
                    break;
                default:
                    // Unknown multi-byte sequence, replace with ?
                    output += '?';
                    i++;
                    break;
            }
        }
        else
        {
            // ASCII character: copy as-is. Non-ASCII (invalid UTF-8 here), replace with '?'
            output += c < 0x80 ? (char)c : '?';
        }
    }
    
    return output;
}   
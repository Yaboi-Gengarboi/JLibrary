// JLibraryDevelopment
// UTF.hpp
// Created on 2021-07-16 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Header file for UTF template classes and functions.
// 
////////////////////////////////////////////////////////////
// References:
//
// https://www.unicode.org/
// https://www.unicode.org/Public/PROGRAMS/CVTUTF/ConvertUTF.c
// https://www.unicode.org/Public/PROGRAMS/CVTUTF/ConvertUTF.h
// https://people.w3.org/rishida/scripts/uniview/conversion
//
////////////////////////////////////////////////////////////

#pragma once

#include <JLibrary/System/Integer.hpp>
#include <algorithm>
#include <locale>
#include <string>
#include <cstdlib>

namespace jlib
{
	template <u32 N> class UTF;

    // Make typedefs to get rid of the template syntax.
    typedef UTF<8>  UTF8;
    typedef UTF<16> UTF16;
    typedef UTF<32> UTF32;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Specialization of the UTF template for UTF-8.
	template <> class UTF<8>
	{
		public:

        // Decodes a single UTF-8 character.
        // Decoding a character means finding its unique 32-bits
        // code (called the codepoint) in the Unicode standard.
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static In decode(In begin, In end, u32& output, u32 replacement = 0)
        {
            // Some useful precomputed data.
            static const i32 trailing[256] =
            {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
            };
            static const u32 offsets[6] =
            {
                0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080
            };

            // decode the character
            i32 trailingBytes = trailing[static_cast<u8>(*begin)];
            if (begin + trailingBytes < end)
            {
                output = 0;
                switch (trailingBytes)
                {
                    case 5: output += static_cast<u8>(*begin++); output <<= 6;
                    case 4: output += static_cast<u8>(*begin++); output <<= 6;
                    case 3: output += static_cast<u8>(*begin++); output <<= 6;
                    case 2: output += static_cast<u8>(*begin++); output <<= 6;
                    case 1: output += static_cast<u8>(*begin++); output <<= 6;
                    case 0: output += static_cast<u8>(*begin++);
                }
                output -= offsets[trailingBytes];
            }
            else
            {
                // Incomplete character.
                begin = end;
                output = replacement;
            }

            return begin;
        }

        // Encodes a single UTF-8 character.
        // Encoding a character means converting a unique 32-bits
        // code (called the codepoint) in the target encoding, UTF-8.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename Out>
        static Out encode(u32 input, Out output, u8 replacement = 0)
        {
            // Some useful precomputed data.
            static const u8 firstBytes[7] =
            {
                0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
            };

            // encode the character.
            if ((input > 0x0010FFFF) || ((input >= 0xD800) && (input <= 0xDBFF)))
            {
                // Invalid character.
                if (replacement)
                    *output++ = replacement;
            }
            else
            {
                // Valid character.

                // Get the number of bytes to write
                std::size_t bytestoWrite = 1;
                if (input < 0x80)       bytestoWrite = 1;
                else if (input < 0x800)      bytestoWrite = 2;
                else if (input < 0x10000)    bytestoWrite = 3;
                else if (input <= 0x0010FFFF) bytestoWrite = 4;

                // Extract the bytes to write.
                u8 bytes[4];
                switch (bytestoWrite)
                {
                    case 4: bytes[3] = static_cast<u8>((input | 0x80) & 0xBF); input >>= 6;
                    case 3: bytes[2] = static_cast<u8>((input | 0x80) & 0xBF); input >>= 6;
                    case 2: bytes[1] = static_cast<u8>((input | 0x80) & 0xBF); input >>= 6;
                    case 1: bytes[0] = static_cast<u8> (input | firstBytes[bytestoWrite]);
                }

                // Add them to the output.
                output = std::copy(bytes, bytes + bytestoWrite, output);
            }

            return output;
        }

        // Advances to the next UTF-8 character.
        // This function is necessary for multi-elements encodings, as
        // a single character may use more than 1 storage element.
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static In next(In begin, In end)
        {
            u32 codepoint;
            return decode(begin, end, codepoint);
        }

        // Counts the number of characters of a UTF-8 sequence.
        // This function is necessary for multi-elements encodings, as
        // a single character may use more than 1 storage element, thus the
        // total size can be different from (begin - end).
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static std::size_t count(In begin, In end)
        {
            std::size_t length = 0;
            while (begin < end)
            {
                begin = next(begin, end);
                ++length;
            }

            return length;
        }

        // Converts an ANSI characters range to UTF-8.
        // The current global locale will be used by default, unless you
        // pass a custom one in the locale parameter.
        // Returns an iterator to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale())
        {
            while (begin < end)
            {
                u32 codepoint = UTF<32>::decodeAnsi(*begin++, locale);
                output = encode(codepoint, output);
            }

            return output;
        }

        // Converts a wide characters range to UTF-8.
        // Returns an iterator to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromWide(In begin, In end, Out output)
        {
            while (begin < end)
            {
                u32 codepoint = UTF<32>::decodeWide(*begin++);
                output = encode(codepoint, output);
            }

            return output;
        }

        // Converts a latin-1 (ISO-5589-1) characters range to UTF-8.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromLatin1(In begin, In end, Out output)
        {
            // Latin-1 is directly compatible with Unicode encodings,
            // and can thus be treated as (a sub-range of) UTF-32.
            while (begin < end)
                output = encode(*begin++, output);

            return output;
        }

        // Converts an UTF-8 characters range to ANSI characters.
        // The current global locale will be used by default, unless you
        // pass a custom one in the locale parameter.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toAnsi(In begin, In end, Out output, char replacement = 0, 
                          const std::locale& locale = std::locale())
        {
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                output = UTF<32>::encodeAnsi(codepoint, output, replacement, locale);
            }

            return output;
        }

        // Converts an UTF-8 characters range to wide characters.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toWide(In begin, In end, Out output, wchar_t replacement = 0)
        {
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                output = UTF<32>::encodeWide(codepoint, output, replacement);
            }

            return output;
        }

        // Converts an UTF-8 characters range to latin-1 (ISO-5589-1) characters.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toLatin1(In begin, In end, Out output, char replacement = 0)
        {
            // Latin-1 is directly compatible with Unicode encodings,
            // and can thus be treated as (a sub-range of) UTF-32.
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                *output++ = codepoint < 256 ? static_cast<char>(codepoint) : replacement;
            }
        }

        // Converts a UTF-8 characters range to UTF-8.
        // This functions does nothing more than a direct copy;
        // it is defined only to provide the same interface as other
        // specializations of the jlib::UTF<> template, and allow
        // generic code to be written on top of it.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF8(In begin, In end, Out output)
        {
            return std::copy(begin, end, output);
        }

        // Converts a UTF-8 characters range to UTF-16.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF16(In begin, In end, Out output)
        {
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                output = UTF<16>::encode(codepoint, output);
            }

            return output;
        }

        // Converts a UTF-8 characters range to UTF-32.s
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF32(In begin, In end, Out output)
        {
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                *output++ = codepoint;
            }

            return output;
        }
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Specialization of the UTF template for UTF-16.
    template <> class UTF<16>
    {
        public:

        // Decodes a single UTF-16 character.
        // Decoding a character means finding its unique 32-bits
        // code (called the codepoint) in the Unicode standard.
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static In decode(In begin, In end, u32& output, u32 replacement = 0)
        {
            u16 first = *begin++;

            // If it's a surrogate pair, first convert to a single UTF-32 character.
            if ((first >= 0xD800) && (first <= 0xDBFF))
            {
                if (begin < end)
                {
                    u32 second = *begin++;
                    if ((second >= 0xDC00) && (second <= 0xDFFF))
                    {
                        // The second element is valid: convert the two elements to a UTF-32 character.
                        output = static_cast<u32>(((first - 0xD800) << 10) + (second - 0xDC00) + 0x0010000);
                    }
                    else
                    {
                        // Invalid character.
                        output = replacement;
                    }
                }
                else
                {
                    // Invalid character.
                    begin = end;
                    output = replacement;
                }
            }
            else
            {
                // We can make a direct copy.
                output = first;
            }

            return begin;
        }

        // Encodes a single UTF-16 character.
        // Encoding a character means converting a unique 32-bits
        // code (called the codepoint) in the target encoding, UTF-16.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename Out>
        static Out encode(u32 input, Out output, u16 replacement = 0)
        {
            if (input <= 0xFFFF)
            {
                // The character can be copied directly, we just need to check if it's in the valid range.
                if ((input >= 0xD800) && (input <= 0xDFFF))
                {
                    // Invalid character (this range is reserved).
                    if (replacement)
                        *output++ = replacement;
                }
                else
                {
                    // Valid character directly convertible to a single UTF-16 character.
                    *output++ = static_cast<u16>(input);
                }
            }
            else if (input > 0x0010FFFF)
            {
                // Invalid character (greater than the maximum Unicode value).
                if (replacement)
                    *output++ = replacement;
            }
            else
            {
                // The input character will be converted to two UTF-16 elements.
                input -= 0x0010000;
                *output++ = static_cast<u16>((input >> 10) + 0xD800);
                *output++ = static_cast<u16>((input & 0x3FFUL) + 0xDC00);
            }

            return output;
        }

        // Advances to the next UTF-16 character.
        // This function is necessary for multi-elements encodings, as
        // a single character may use more than 1 storage element.
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static In next(In begin, In end)
        {
            u32 codepoint;
            return decode(begin, end, codepoint);
        }

        // Counts the number of characters of a UTF-16 sequence.
        // This function is necessary for multi-elements encodings, as
        // a single character may use more than 1 storage element, thus the
        // total size can be different from (begin - end).
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static std::size_t count(In begin, In end)
        {
            std::size_t length = 0;
            while (begin < end)
            {
                begin = next(begin, end);
                ++length;
            }

            return length;
        }

        // Convert an ANSI characters range to UTF-16.
        // The current global locale will be used by default, unless you
        // pass a custom one in the locale parameter.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale())
        {
            while (begin < end)
            {
                u32 codepoint = UTF<32>::decodeAnsi(*begin++, locale);
                output = encode(codepoint, output);
            }

            return output;
        }

        // Converts a wide characters range to UTF-16.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromWide(In begin, In end, Out output)
        {
            while (begin < end)
            {
                u32 codepoint = UTF<32>::decodeWide(*begin++);
                output = encode(codepoint, output);
            }

            return output;
        }

        // Converts a latin-1 (ISO-5589-1) characters range to UTF-16.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromLatin1(In begin, In end, Out output)
        {
            // Latin-1 is directly compatible with Unicode encodings,
            // and can thus be treated as (a sub-range of) UTF-32.
            return std::copy(begin, end, output);
        }

        // Converts an UTF-16 characters range to ANSI characters.
        // The current global locale will be used by default, unless you
        // pass a custom one in the \a locale parameter.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toAnsi(In begin, In end, Out output, char replacement = 0,
            const std::locale& locale = std::locale())
        {
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                output = UTF<32>::encodeAnsi(codepoint, output, replacement, locale);
            }

            return output;
        }

        // Converts an UTF-16 characters range to wide characters.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toWide(In begin, In end, Out output, wchar_t replacement = 0)
        {
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                output = UTF<32>::encodeWide(codepoint, output, replacement);
            }

            return output;
        }

        // Converts an UTF-16 characters range to latin-1 (ISO-5589-1) characters.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toLatin1(In begin, In end, Out output, char replacement = 0)
        {
            // Latin-1 is directly compatible with Unicode encodings,
            // and can thus be treated as (a sub-range of) UTF-32
            while (begin < end)
            {
                *output++ = *begin < 256 ? static_cast<char>(*begin) : replacement;
                begin++;
            }

            return output;
        }

        // Converts a UTF-16 characters range to UTF-8.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF8(In begin, In end, Out output)
        {
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                output = UTF<8>::encode(codepoint, output);
            }

            return output;
        }

        // Converts a UTF-16 characters range to UTF-16.
        // This functions does nothing more than a direct copy;
        // it is defined only to provide the same interface as other
        // specializations of the sf::UTF<> template, and allow
        // generic code to be written on top of it.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF16(In begin, In end, Out output)
        {
            return std::copy(begin, end, output);
        }

        // Converts a UTF-16 characters range to UTF-32.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF32(In begin, In end, Out output)
        {
            while (begin < end)
            {
                u32 codepoint;
                begin = decode(begin, end, codepoint);
                *output++ = codepoint;
            }

            return output;
        }
    };

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Specialization of the UTF template for UTF-32.
    template <> class UTF<32>
    {
        public:

        // Decodes a single UTF-32 character.
        // Decoding a character means finding its unique 32-bits
        // code (called the codepoint) in the Unicode standard.
        // For UTF-32, the character value is the same as the codepoint.
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static In decode(In begin, In end, u32& output, u32 replacement = 0) 
        {
            output = *begin++;
            return begin;
        }

        // Encodes a single UTF-32 character.
        // Encoding a character means converting a unique 32-bits
        // code (called the codepoint) in the target encoding, UTF-32.
        // For UTF-32, the codepoint is the same as the character value.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename Out>
        static Out encode(u32 input, Out output, u32 replacement = 0)
        {
            *output++ = input;
            return output;
        }

        // Advances to the next UTF-32 character.
        // This function is trivial for UTF-32, which can store
        // every character in a single storage element.
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static In next(In begin, In end)
        {
            return ++begin;
        }

        // Counts the number of characters of a UTF-32 sequence.
        // This function is trivial for UTF-32, which can store
        // every character in a single storage element.
        // Returns an iterator pointing to one past the last read element of the input sequence.
        template <typename In>
        static std::size_t count(In begin, In end)
        {
            return begin - end;
        }

        // Converts an ANSI characters range to UTF-32.
        // The current global locale will be used by default, unless you
        // pass a custom one in the locale parameter.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale()) 
        {
            while (begin < end)
                *output++ = decodeAnsi(*begin++, locale);

            return output;
        }

        // Converts a wide characters range to UTF-32.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromWide(In begin, In end, Out output)
        {
            while (begin < end)
                *output++ = decodeWide(*begin++);

            return output;
        }

        // Converts a latin-1 (ISO-5589-1) characters range to UTF-32.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out fromLatin1(In begin, In end, Out output)
        {
            // Latin-1 is directly compatible with Unicode encodings,
            // and can thus be treated as (a sub-range of) UTF-32.
            return std::copy(begin, end, output);
        }


        // Converts an UTF-32 characters range to ANSI characters.
        // The current global locale will be used by default, unless you
        // pass a custom one in the locale parameter.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toAnsi(In begin, In end, Out output, char replacement = 0, 
                          const std::locale& locale = std::locale())
        {
            while (begin < end)
                output = encodeAnsi(*begin++, output, replacement, locale);

            return output;
        }

        // Converts an UTF-32 characters range to wide characters.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toWide(In begin, In end, Out output, wchar_t replacement = 0)
        {
            while (begin < end)
                output = encodeWide(*begin++, output, replacement);

            return output;
        }

        // Converts an UTF-16 characters range to latin-1 (ISO-5589-1) characters.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toLatin1(In begin, In end, Out output, char replacement = 0)
        {
            // Latin-1 is directly compatible with Unicode encodings,
            // and can thus be treated as (a sub-range of) UTF-32.
            while (begin < end)
            {
                *output++ = *begin < 256 ? static_cast<char>(*begin) : replacement;
                begin++;
            }

            return output;
        }

        // Converts a UTF-32 characters range to UTF-8.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF8(In begin, In end, Out output)
        {
            while (begin < end)
                output = UTF<8>::encode(*begin++, output);

            return output;
        }

        // Converts a UTF-32 characters range to UTF-16.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF16(In begin, In end, Out output)
        {
            while (begin < end)
                output = Utf<16>::encode(*begin++, output);

            return output;
        }

        // Converts a UTF-32 characters range to UTF-32.
        // This functions does nothing more than a direct copy;
        // it is defined only to provide the same interface as other
        // specializations of the jlib::UTF<> template, and allow
        // generic code to be written on top of it.
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename In, typename Out>
        static Out toUTF32(In begin, In end, Out output)
        {
            return std::copy(begin, end, output);
        }

        // Decodes a single ANSI character to UTF-32.
        // This function does not exist in other specializations
        // of jlib::UTF<>, it is defined for convenience (it is used by
        // several other conversion functions).
        // Returns the converted character.
        template <typename In>
        static u32 decodeAnsi(In input, const std::locale& locale = std::locale())
        {
            // Get the facet of the locale which deals with character conversion.
            const std::ctype<wchar_t>& facet = std::use_facet<std::ctype<wchar_t>>(locale);

            // Use the facet to convert each character of the input string.
            return static_cast<u32>(facet.widen(input));
        }

        // Decodes a single wide character to UTF-32.
        // This function does not exist in other specializations
        // of jlib::UTF<>, it is defined for convenience (it is used by
        // several other conversion functions).
        // Returns the converted character.
        template <typename In>
        static u32 decodeWide(In input)
        {
            // The encoding of wide characters is not well defined and is left to the system;
            // however we can safely assume that it is UCS-2 on Windows and
            // UCS-4 on Unix systems.
            // In both cases, a simple copy is enough (UCS-2 is a subset of UCS-4,
            // and UCS-4 *is* UTF-32).
            return input;
        }

        // Encodes a single UTF-32 character to ANSI.
        // This function does not exist in other specializations
        // of jlib::UTF<>, it is defined for convenience (it is used by
        // several other conversion functions).
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename Out>
        static Out encodeAnsi(u32 codepoint, Out output, char replacement = 0,
                              const std::locale& locale = std::locale())
        {
            // Get the facet of the locale which deals with character conversion.
            const std::ctype<wchar_t>& facet = std::use_facet<std::ctype<wchar_t>>(locale);

            // Use the facet to convert each character of the input string.
            *output++ = facet.narrow(static_cast<wchar_t>(codepoint), replacement);

            return output;
        }

        // Encodes a single UTF-32 character to wide.
        // This function does not exist in other specializations
        // of jlib::UTF<>, it is defined for convenience (it is used by
        // several other conversion functions).
        // Returns an iterator pointing to the end of the output sequence which has been written.
        template <typename Out>
        static Out encodeWide(u32 codepoint, Out output, wchar_t replacement = 0)
        {
            // The encoding of wide characters is not well defined and is left to the system;
            // however we can safely assume that it is UCS-2 on Windows and
            // UCS-4 on Unix systems.
            // For UCS-2 we need to check if the source characters fits in (UCS-2 is a subset of UCS-4).
            // For UCS-4 we can do a direct copy (UCS-4 *is* UTF-32).
            switch (sizeof(wchar_t))
            {
                case 4:
                {
                    *output++ = static_cast<wchar_t>(codepoint);
                    break;
                }

                default:
                {
                    if ((codepoint <= 0xFFFF) && ((codepoint < 0xD800) || (codepoint > 0xDFFF)))
                    {
                        *output++ = static_cast<wchar_t>(codepoint);
                    }
                    else if (replacement)
                    {
                        *output++ = replacement;
                    }
                    break;
                }
            }

            return output;
        }
    };
}
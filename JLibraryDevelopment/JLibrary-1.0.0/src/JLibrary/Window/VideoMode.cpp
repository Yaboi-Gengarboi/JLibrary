////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// VideoMode.cpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-08 by Justyn Durnford
// Source file for the VideoMode class.

#include <JLibrary/Window/VideoMode.hpp>
using namespace jlib;

#include <algorithm>
using std::find;
using std::sort;

// <compare>
using std::strong_ordering;

#include <functional>
using std::greater;

// <vector>
using std::vector;

#include <windows.h>

VideoMode::VideoMode()
{
	width = 0;
	height = 0;
	bitsPerPixel = 0;
}

VideoMode::VideoMode(u32 modeWidth, u32 modeHeight, u32 modeBitsPerPixel)
{
	width = modeWidth;
	height = modeHeight;
	bitsPerPixel = modeBitsPerPixel;
}

VideoMode VideoMode::getDesktopMode()
{
    DEVMODE win32Mode;
    win32Mode.dmSize = sizeof(win32Mode);
    win32Mode.dmDriverExtra = 0;
    EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &win32Mode);
    return VideoMode(win32Mode.dmPelsWidth, win32Mode.dmPelsHeight, win32Mode.dmBitsPerPel);
}

const vector<VideoMode>& VideoMode::getFullscreenModes()
{
    static vector<VideoMode> modes;

    if (modes.empty())
    {
        // Enumerate all available video modes for the primary display adapter.
        DEVMODE win32Mode;
        win32Mode.dmSize = sizeof(win32Mode);
        win32Mode.dmDriverExtra = 0;
        for (int count = 0; EnumDisplaySettings(nullptr, count, &win32Mode); ++count)
        {
            // Convert to a jlib::VideoMode.
            VideoMode mode(win32Mode.dmPelsWidth, win32Mode.dmPelsHeight, win32Mode.dmBitsPerPel);

            // Add it only if it is not already in the array.
            if (find(modes.begin(), modes.end(), mode) == modes.end())
                modes.push_back(mode);
        }

        sort(modes.begin(), modes.end(), greater<VideoMode>());
    }

    return modes;
}

bool VideoMode::isValid() const
{
	const vector<VideoMode>& modes = getFullscreenModes();
	return find(modes.begin(), modes.end(), *this) != modes.end();
}

bool operator == (const VideoMode& A, const VideoMode& B)
{
    return (A.width == B.width)                && 
           (A.height == B.height)              && 
           (A.bitsPerPixel == B.bitsPerPixel);
}

bool operator != (const VideoMode& A, const VideoMode& B)
{
    return (A.width != B.width)                || 
           (A.height != B.height)              || 
           (A.bitsPerPixel != B.bitsPerPixel);
}

bool operator < (const VideoMode& A, const VideoMode& B)
{
    if (A.bitsPerPixel == B.bitsPerPixel)
    {
        if (A.width == B.width)
            return A.height < B.height;
        else
            return A.width < B.width;
    }
    else
        return A.bitsPerPixel < B.bitsPerPixel;
}

bool operator <= (const VideoMode& A, const VideoMode& B)
{
    return !(A > B);
}

bool operator > (const VideoMode& A, const VideoMode& B)
{
    if (A.bitsPerPixel == B.bitsPerPixel)
    {
        if (A.width == B.width)
            return A.height > B.height;
        else
            return A.width > B.width;
    }
    else
        return A.bitsPerPixel > B.bitsPerPixel;
}

bool operator >= (const VideoMode& A, const VideoMode& B)
{
    return !(A < B);
}

std::strong_ordering operator <=> (const VideoMode& A, const VideoMode& B)
{
    if (A < B)
        return strong_ordering::less;
    if (A > B)
        return strong_ordering::greater;
    return strong_ordering::equivalent;
}
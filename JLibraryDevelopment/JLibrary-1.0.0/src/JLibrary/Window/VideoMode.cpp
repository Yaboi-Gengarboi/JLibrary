// JLibraryDevelopment
// VideoMode.cpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-08 by Justyn Durnford
// Source file for the VideoMode class.

#include <JLibrary/Window/VideoMode.hpp>
using namespace jlib;

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
            bool found = false;
            for (const VideoMode& elem : modes)
            {
                if (elem == mode)
                {
                    found = true;
                    break;
                }
            }

            if (found == false)
                modes.push_back(mode);
        }
    }

    return modes;
}

bool VideoMode::isValid() const
{
	const vector<VideoMode>& modes = getFullscreenModes();
    
    bool found = false;
    for (const VideoMode& elem : modes)
    {
        if (elem == *this)
        {
            found = true;
            break;
        }
    }

    return found;
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
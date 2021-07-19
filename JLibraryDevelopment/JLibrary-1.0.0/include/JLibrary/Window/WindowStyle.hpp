// JLibraryDevelopment
// WindowStyle.hpp
// Created on 2021-07-15 by Justyn Durnford
// Last modified on 2021-07-15 by Justyn Durnford
// Header file for the WindowStyle enum.

#pragma once

namespace jlib
{
    // Enumeration of the window styles.
    enum WindowStyle
    {
        None = 0, // No border / title bar (this flag and all others are mutually exclusive).
        Titlebar = 1, // Title bar + fixed border.
        Resize = 2, // Title bar + resizable border + maximize button.
        Close = 4, // Title bar + close button.
        Fullscreen = 8, // Fullscreen mode (this flag and all others are mutually exclusive).
        Default = Titlebar | Resize | Close // Default window style.
    };
}
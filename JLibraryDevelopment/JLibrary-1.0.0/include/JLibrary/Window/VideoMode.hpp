// JLibraryDevelopment
// VideoMode.hpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-08 by Justyn Durnford
// Header file for the VideoMode class.

#pragma once

#include <JLibrary/System/Integer.hpp>
#include <vector>

namespace jlib
{
	// Class that defines a video mode (width, height, bpp).
	class VideoMode
	{
		public:

		u32 width;
		u32 height;
		u32 bitsPerPixel;

		// Default constructor.
		// Initializes all members to 0.
		VideoMode();

		// Constructs the video mode with its attributes.
		VideoMode(u32 modeWidth, u32 modeHeight, u32 modeBitsPerPixel = 32);

		// Gets the current desktop video mode.
		static VideoMode getDesktopMode();

		// Retrieves all the video modes supported in fullscreen mode.
		// When creating a fullscreen window, the video mode is restricted
		// to be compatible with what the graphics driver and monitor
		// support. This function returns the complete list of all video
		// modes that can be used in fullscreen mode.
		// The returned array is sorted from best to worst, so that
		// the first element will always give the best mode (higher
		// width, height and bits-per-pixel).
		static const std::vector<VideoMode>& getFullscreenModes();

		// Returns true if the video mode is valid.
		// The validity of video modes is only relevant when using
		// fullscreen windows; otherwise any video mode can be used
		// with no restriction.
		bool isValid() const;
	};
}

// Overload of binary operator ==
bool operator == (const jlib::VideoMode& A, const jlib::VideoMode& B);

// Overload of binary operator !=
bool operator != (const jlib::VideoMode& A, const jlib::VideoMode& B);
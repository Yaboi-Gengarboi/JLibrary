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
// Image.hpp
// Created on 2021-06-21 by Justyn Durnford
// Last modified on 2021-06-29 by Justyn Durnford
// Header file for the Image class.

#pragma once

#include <JLibrary/Graphics/Color.hpp>
#include <JLibrary/Math/Rectangle.hpp>
#include <JLibrary/System/Array.hpp>
#include <JLibrary/System/InputStream.hpp>
#include <JLibrary/System/Integer.hpp>
#include <string>

namespace jlib
{
	// Class for loading, manipulating and saving images.
	// The supported image formats are bmp, png, tga, jpg, gif,
	// psd, hdr and pic. Some format options are not supported,
	// like progressive jpeg.
	class Image
	{
		public:

		enum Format
		{
			BMP = 0,
			PNG = 1,
			TGA = 2,
			JPG = 3,
			GIF = 4,
			PSD = 5,
			HDR = 6,
			PIC = 7
		};

		private:

		unsigned int width_;
		unsigned int height_;
		Array<unsigned char> pixels_;

		public:

		// Default constructor.
		Image();

		// Copy constructor.
		Image(const Image& other) = default;

		// Move constructor.
		Image(Image&& other) = default;

		// Copy assignment operator.
		Image& operator = (const Image& other) = default;

		// Move assignment operator.
		Image& operator = (Image&& other) = default;

		// Destructor.
		~Image() = default;

		// Creates the image and fills it with a transparent color.
		void create(unsigned int width, unsigned int height);

		// Creates the image and fills it with the given color.
		void create(unsigned int width, unsigned int height, const Color& color);

		// Creates the image and fills it the constructed color.
		void create(unsigned int width, unsigned int height, unsigned char r, 
					unsigned char g, unsigned char b, unsigned char a);

		// Creates the image and fills it the constructed color.
		void create(unsigned int width, unsigned int height, unsigned int color);

		// Creates the image from an array of pixels.
		// The pixel array is assumed to contain 32-bit RGBA pixels,
		// and have the given width and height. If not, this
		// results in undefined behavior.
		// If the pixel pointer is nullptr, an empty image is created.
		void create(unsigned int width, unsigned int height, const unsigned char* pixels);

		// Creates the image from the Array of pixels.
		// The pixel vector is assumed to contain 32-bit RGBA pixels,
		// and have the given width and height. If not, this
		// results in undefined behavior.
		// If the pixel Array is empty, an empty image is created.
		void create(unsigned int width, unsigned int height, const Array<unsigned char>& pixels);

		// Loads the image from a file on the disk.
		// If this function fails, the image is left unchanged.
		// Returns true if this is successful.
		bool loadFromFile(const std::string& filename);

		// Loads the image from a file in memory.
		// If this function fails, the image is left unchanged.
		// Returns true if this is successful.
		bool loadFromMemory(const void* data, std::size_t size);

		// Loads the image from a custom stream.
		// If this function fails, the image is left unchanged.
		// Returns true if this is successful.
		bool loadFromStream(InputStream& stream);

		// Saves the image to a file on the disk.
		// The format of the image is automatically deduced from
		// the extension.
		// The destination file is overwritten if it already exists. 
		// This function fails if the image is empty.
		bool saveToFile(const std::string& filename) const;

		// Saves the image to a buffer in memory.
		// The format of the image MUST be specified.
		// This function fails if the image is empty.
		bool saveToMemory(Array<unsigned char>& output, Format format) const;

		// Saves the image to a buffer in memory.
		// The format of the image MUST be specified.
		// This function fails if the image is empty, or if
		// the format was invalid.
		bool saveToMemory(Array<unsigned char>& output, const std::string& format) const;

		// Returns the width of the image.
		unsigned int width() const;

		// Returns the height of the image.
		unsigned int height() const;

		// Creates a transparency mask from a specified color-key.
		// This function sets the alpha value of every pixel matching
		// the given color to an alpha of 0 so that they become transparent.
		void createMaskFromColor(const Color& color);

		// Creates a transparency mask from a specified color-key.
		// This function sets the alpha value of every pixel matching
		// the given color to alpha so that they become transparent.
		void createMaskFromColor(const Color& color, unsigned char alpha);

		// Copies pixels from another image onto this one.
		// 
		// This function does a slow pixel copy and should not be
		// used intensively. It can be used to prepare a complex
		// static image from several others, but if you need this
		// kind of feature in real-time, you'd be better off 
		// using a jlib::RenderTexture.
		void copyFrom(const Image& source, unsigned int dest_x, unsigned int dest_y,
					  const IntRect& sourceRect = IntRect(), bool applyAlpha = true);

		// Returns the color of the pixel at coordinate (x, y).
		Color getPixel(unsigned int x, unsigned int y) const;

		// Changes the color of the pixel at coordinate (x, y) to the given Color.
		void setPixel(unsigned int x, unsigned int y, const Color& color);

		// Returns a read-only pointer to the array of pixels.
		const unsigned char* getPixelPtr() const;

		// Flips the image horizontally.
		void flipHorizontally();

		// Flips the image vertically.
		void flipVertically();
	};
}
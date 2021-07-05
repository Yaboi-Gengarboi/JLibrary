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
// Image.cpp
// Created on 2021-06-24 by Justyn Durnford
// Last modified on 2021-07-02 by Justyn Durnford
// Source file for the Image class.

#define STB_IMAGE_IMPLEMENTATION
#include <ExternalLibs/stb_image/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <ExternalLibs/stb_image/stb_image_write.h>

#include <JLibrary/Graphics/Image.hpp>
#include <JLibrary/System/NonCopyable.hpp>
using namespace jlib;

#include <algorithm>
using std::copy;
using std::swap_ranges;

#include <cctype>
using std::isalpha;
using std::tolower;

#include <cstring>
using std::memcpy;

#include <iostream>
using std::cout;
using std::endl;

#include <iterator>
using std::back_inserter;

// <string>
using std::string;

#include <utility>
using std::move;

#include <vector>
using std::vector;

// Create a lowercase copy of the given std::string.
string toLower(string str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (isalpha(str[i]))
            str[i] = tolower(str[i]);
    }

    return str;
}

// stb_image callback that operates on a jlib::InputStream.
int read(void* user, char* data, int size)
{
    InputStream* stream = static_cast<InputStream*>(user);
    return static_cast<int>(stream->read(data, size));
}

// stb_image callback that operates on a jlib::InputStream.
void skip(void* user, int size)
{
    InputStream* stream = static_cast<InputStream*>(user);
    stream->seek(stream->tell() + size);
}

// stb_image callback that operates on a jlib::InputStream.
int eof(void* user)
{
    InputStream* stream = static_cast<InputStream*>(user);
    return stream->tell() >= stream->size();
}

// stb_image callback for constructing a buffer.
void bufferFromCallback(void* context, void* data, int size)
{
    u8* source = static_cast<u8*>(data);
    vector<u8>* dest = static_cast<vector<u8>*>(context);
    copy(source, source + size, back_inserter(*dest));
}

class ImageLoader : public NonCopyable
{
    // Default constructor.
    ImageLoader() {}

    // Destructor
    ~ImageLoader() {}

    public:

    // Gets the unique instance of the class.
    static ImageLoader& getInstance()
    {
        static ImageLoader Instance;
        return Instance;
    }

    // Loads an image from a file on the disk.
    bool loadImageFromFile(const string& filename, Array<u8>& pixels, u32 image_width, u32 image_height)
    {
        pixels.clear();

        // Load the image and get a pointer to the pixels in memory.
        int width = 0;
        int height = 0;
        int channels = 0;
        u8* ptr = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if (ptr != nullptr)
        {
            image_width = width;
            image_height = height;

            if (width != 0 && height != 0)
            {
                // Copy the loaded pixels to the pixel buffer.
                pixels = Array<u8>(width * height * 4);
                memcpy(&pixels[0], ptr, pixels.size());
            }

            // Free the loaded pixels (they are now in our own pixel buffer).
            stbi_image_free(ptr);

            return true;
        }
        else
        {
            // Error, failed to load the image.
            cout << "ERROR: Failed to load image \"" << filename << "\". Reason: " << stbi_failure_reason() << endl;

            return false;
        }
    }

    // Loads an image from a file in memory.
    bool loadImageFromMemory(const void* data, size_t dataSize, Array<u8>& pixels, 
                             u32 image_width, u32 image_height)
    {
        if (data != nullptr && dataSize != 0)
        {
            pixels.clear();

            // Load the image and get a pointer to the pixels in memory.
            int width = 0;
            int height = 0;
            int channels = 0;
            const u8* buffer = static_cast<const u8*>(data);
            u8* ptr = stbi_load_from_memory(buffer, static_cast<int>(dataSize), &width, 
                                            &height, &channels, STBI_rgb_alpha);

            if (ptr != nullptr)
            {
                image_width = width;
                image_height = height;

                if (width != 0 && height != 0)
                {
                    // Copy the loaded pixels to the pixel buffer.
                    pixels = Array<u8>(width * height * 4);
                    memcpy(&pixels[0], ptr, pixels.size());
                }

                // Free the loaded pixels (they are now in our own pixel buffer).
                stbi_image_free(ptr);

                return true;
            }
        }
    }

    // Loads an image from a custom stream.
    bool loadImageFromStream(InputStream& stream, Array<u8>& pixels, 
                             u32 image_width, u32 image_height)
    {
        pixels.clear();

        // Make sure that the stream's reading position is at the beginning.
        stream.seek(0);

        // Setup the stb_image callbacks.
        stbi_io_callbacks callbacks;
        callbacks.read = &read;
        callbacks.skip = &skip;
        callbacks.eof = &eof;

        // Load the image and get a pointer to the pixels in memory.
        int width = 0;
        int height = 0;
        int channels = 0;
        u8* ptr = stbi_load_from_callbacks(&callbacks, &stream, &width, 
                                           &height, &channels, STBI_rgb_alpha);

        if (ptr != nullptr)
        {
            image_width = width;
            image_height = height;

            if (width && height)
            {
                // Copy the loaded pixels to the pixel buffer.
                pixels = Array<u8>(width * height * 4);
                memcpy(&pixels[0], ptr, pixels.size());
            }

            // Free the loaded pixels (they are now in our own pixel buffer).
            stbi_image_free(ptr);

            return true;
        }
        else
        {
            // Error, failed to load the image.
            cout << "Failed to load image from stream. Reason: " << stbi_failure_reason() << endl;

            return false;
        }
    }

    // Saves the Array of pixels as an image file.
    bool saveImageToFile(const string& filename, const Array<u8>& pixels, 
                         u32 image_width, u32 image_height)
    {
        // Make sure the image is not empty.
        if (!pixels.isEmpty() && (image_width > 0) && (image_height > 0))
        {
            // Deduce the image type from its extension.

            // Extract the extension.
            size_t dot = filename.find_last_of('.');
            string extension;

            if (dot != string::npos)
                extension = toLower(filename.substr(dot + 1));
            else
                extension = "";

            // Choose function based on format.
            if (extension == "bmp")
            {
                // BMP format.
                if (stbi_write_bmp(filename.c_str(), image_width, image_height, 4, &pixels[0]))
                    return true;
            }
            else if (extension == "tga")
            {
                // TGA format.
                if (stbi_write_tga(filename.c_str(), image_width, image_height, 4, &pixels[0]))
                    return true;
            }
            else if (extension == "png")
            {
                // PNG format.
                if (stbi_write_png(filename.c_str(), image_width, image_height, 4, &pixels[0], 0))
                    return true;
            }
            else if (extension == "jpg" || extension == "jpeg")
            {
                // JPG format.
                if (stbi_write_jpg(filename.c_str(), image_width, image_height, 4, &pixels[0], 90))
                    return true;
            }
        }

        cout << "Failed to save image \"" << filename << "\"" << endl;
        return false;
    }

    // Saves the Array of pixels as an encoded image buffer.
    bool saveImageToMemory(Image::Format format, Array<u8>& output,
                           const Array<u8>& pixels, u32 image_width,
                           u32 image_height)
    {
        // Make sure the image is not empty.
        if (!pixels.isEmpty() && (image_width > 0) && (image_height > 0))
        {
            // Choose function based on format.
            if (format = Image::Format::BMP)
            {
                // BMP format.
                if (stbi_write_bmp_to_func(&bufferFromCallback, &output, image_width, image_height, 4, &pixels[0]))
                    return true;
            }
            else if (format = Image::Format::TGA)
            {
                // TGA format.
                if (stbi_write_tga_to_func(&bufferFromCallback, &output, image_width, image_height, 4, &pixels[0]))
                    return true;
            }
            else if (format = Image::Format::PNG)
            {
                // PNG format.
                if (stbi_write_png_to_func(&bufferFromCallback, &output, image_width, image_height, 4, &pixels[0], 0))
                    return true;
            }
            else if (format = Image::Format::JPG)
            {
                // JPG format
                if (stbi_write_jpg_to_func(&bufferFromCallback, &output, image_width, image_height, 4, &pixels[0], 90))
                    return true;
            }
        }

        cout << "Failed to save image with format \"" << format << "\"" << endl;
        return false;
    }

    // Saves the Array of pixels as an encoded image buffer.
    bool saveImageToMemory(const string& format, Array<u8>& output, const Array<u8>& pixels, 
                           u32 image_width, u32 image_height)
    {
        // Make sure the image is not empty.
        if (!pixels.isEmpty() && (image_width > 0) && (image_height > 0))
        {
            // Choose function based on format.
            string specified = toLower(format);

            if (specified == "bmp")
            {
                // BMP format
                if (stbi_write_bmp_to_func(&bufferFromCallback, &output, image_width, image_width, 4, &pixels[0]))
                    return true;
            }
            else if (specified == "tga")
            {
                // TGA format
                if (stbi_write_tga_to_func(&bufferFromCallback, &output, image_width, image_width, 4, &pixels[0]))
                    return true;
            }
            else if (specified == "png")
            {
                // PNG format
                if (stbi_write_png_to_func(&bufferFromCallback, &output, image_width, image_width, 4, &pixels[0], 0))
                    return true;
            }
            else if (specified == "jpg")
            {
                // JPG format
                if (stbi_write_jpg_to_func(&bufferFromCallback, &output, image_width, image_width, 4, &pixels[0], 90))
                    return true;
            }
        }

        cout << "Failed to save image with format \"" << format << "\"" << endl;
        return false;
    }
};

Image::Image()
{
	width_ = 0;
	height_ = 0;
}

void Image::create(u32 width, u32 height)
{
    if (width != 0 && height != 0)
    {
        width_ = width;
        height_ = height;
        pixels_ = Array<u8>(width * height * 4, 0x00);
    }
    else
    {
        // Empty the pixel buffer.
        pixels_.clear();

        // Assign the new size.
        width_ = 0;
        height_ = 0;
    }
}

void Image::create(u32 width, u32 height, const Color& color)
{
    if (width != 0 && height != 0)
    {
        // Create a new pixel buffer first for exception safety's sake.
        Array<u8> new_pixels(width * height * 4);

        for (size_t i(0); i < new_pixels.size(); i += 4)
        {
            new_pixels[i + 0] = color[0];
            new_pixels[i + 1] = color[1];
            new_pixels[i + 2] = color[2];
            new_pixels[i + 3] = color[3];
        }

        // Commit the new pixel buffer.
        pixels_ = move(new_pixels);

        // Assign the new size.
        width_ = width;
        height_ = height;
    }
    else
    {
        // Empty the pixel buffer.
        pixels_.clear();

        // Assign the new size.
        width_ = 0;
        height_ = 0;
    }
}

void Image::create(u32 width, u32 height, u8 r, u8 g, u8 b, u8 a)
{
    if (width != 0 && height != 0)
    {
        // Create a new pixel buffer first for exception safety's sake.
        Array<u8> new_pixels(width * height * 4);

        for (size_t i(0); i < new_pixels.size(); i += 4)
        {
            new_pixels[i + 0] = r;
            new_pixels[i + 1] = g;
            new_pixels[i + 2] = b;
            new_pixels[i + 3] = a;
        }

        // Commit the new pixel buffer.
        pixels_ = move(new_pixels);

        // Assign the new sizes.
        width_ = width;
        height_ = height;
    }
    else
    {
        // Empty the pixel buffer.
        pixels_.clear();

        // Assign the new size.
        width_ = 0;
        height_ = 0;
    }
}

void Image::create(u32 width, u32 height, u32 color)
{
    if (width != 0 && height != 0)
    {
        // Create a new pixel buffer first for exception safety's sake.
        Array<u8> new_pixels(width * height * 4);

        for (size_t i(0); i < new_pixels.size(); i += 4)
        {
            new_pixels[i + 0] = (color & 0xff000000) >> 24;
            new_pixels[i + 1] = (color & 0x00ff0000) >> 16;
            new_pixels[i + 2] = (color & 0x0000ff00) >> 8;
            new_pixels[i + 3] = (color & 0x000000ff) >> 0;
        }

        // Commit the new pixel buffer.
        pixels_ = move(new_pixels);

        // Assign the new size.
        width_ = width;
        height_ = height;
    }
    else
    {
        // Empty the pixel buffer.
        pixels_.clear();

        // Assign the new size.
        width_ = 0;
        height_ = 0;
    }
}

void Image::create(u32 width, u32 height, const u8* pixels)
{
    if (pixels != nullptr && width != 0 && height != 0)
    {
        // Create a new pixel buffer first for exception safety's sake.
        Array<u8> new_pixels(pixels, pixels + width * height * 4);

        // Commit the new pixel buffer.
        pixels_ = move(new_pixels);

        // Assign the new size.
        width_ = width;
        height_ = height;
    }
    else
    {
        // Empty the pixel buffer.
        pixels_.clear();

        // Assign the new size.
        width_ = 0;
        height_ = 0;
    }
}

void Image::create(u32 width, u32 height, const Array<u8>& pixels)
{
    if (!pixels.isEmpty() && width != 0 && height != 0)
    {
        pixels_ = pixels;

        // Assign the new size.
        width_ = width;
        height_ = height;
    }
    else
    {
        // Empty the pixel buffer.
        pixels_.clear();

        // Assign the new size.
        width_ = 0;
        height_ = 0;
    }
}

bool Image::loadFromFile(const string& filename)
{
    return ImageLoader::getInstance().loadImageFromFile(filename,pixels_, width_, height_);
}

bool Image::loadFromMemory(const void* data, size_t size)
{
    return ImageLoader::getInstance().loadImageFromMemory(data, size, pixels_, width_, height_);
}

bool Image::loadFromStream(InputStream& stream)
{
    return ImageLoader::getInstance().loadImageFromStream(stream, pixels_, width_, height_);
}

bool Image::saveToFile(const string& filename) const
{
    return ImageLoader::getInstance().saveImageToFile(filename, pixels_, width_, height_);
}

bool Image::saveToMemory(Array<u8>& output, Image::Format format) const
{
    return ImageLoader::getInstance().saveImageToMemory(format, output, pixels_, width_, height_);
}

bool Image::saveToMemory(Array<u8>& output, const string& format) const
{
    return ImageLoader::getInstance().saveImageToMemory(format, output, pixels_, width_, height_);
}

u32 Image::width() const
{
    return width_;
}

u32 Image::height() const
{
    return height_;
}

void Image::createMaskFromColor(const Color& color, u8 alpha)
{
    if (!pixels_.isEmpty())
    {
        // Replace the alpha of the pixels that match the transparent color.
        u8* ptr = &pixels_[0];
        u8* end = ptr + pixels_.size();
        while (ptr < end)
        {
            if ((ptr[0] == color[0]) && (ptr[1] == color[1]) &&
                (ptr[2] == color[2]) && (ptr[3] == color[2]))
                ptr[3] = alpha;
            ptr += 4;
        }
    }
}

void Image::copyFrom(const Image& source, u32 dest_x, u32 dest_y,
                     const IntRect& sourceRect, bool applyAlpha)
{
    // Make sure that both images are valid.
    if ((source.width_ == 0) || (source.height_ == 0) || (width_ == 0) || (height_ == 0))
        return;

    // Adjust the source rectangle.
    IntRect srcRect = sourceRect;
    if (srcRect.width == 0 || (srcRect.height == 0))
    {
        srcRect.vertex = Point2i(0, 0);
        srcRect.width = source.width_;
        srcRect.height = source.height_;
    }
    else
    {
        if (srcRect.vertex.x < 0) 
            srcRect.vertex.x = 0;
        if (srcRect.vertex.y < 0) 
            srcRect.vertex.y = 0;
        if (srcRect.width > static_cast<int>(source.width_))
            srcRect.width = source.width_;
        if (srcRect.height > static_cast<int>(source.height_)) 
            srcRect.height = source.height_;
    }

    // Then find the valid bounds of the destination rectangle.
    int width = srcRect.width;
    int height = srcRect.height;
    if (dest_x + width > width_) width = width_ - dest_x;
    if (dest_y + height > height_) height = height_ - dest_y;

    // Make sure the destination area is valid.
    if ((width <= 0) || (height <= 0))
        return;

    // Precompute as much as possible.
    int          pitch = width * 4;
    int          rows = height;
    int          srcStride = source.width_ * 4;
    int          dstStride = width_ * 4;
    const u8* srcPixels = &source.pixels_[0] + (srcRect.vertex.x + srcRect.vertex.y * source.width_) * 4;
    u8* dstPixels = &pixels_[0] + (dest_x + dest_y * width_) * 4;

    // Copy the pixels.
    if (applyAlpha)
    {
        // Interpolation using alpha values, pixel by pixel (slower).
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                // Get a direct pointer to the components of the current pixel.
                const u8* src = srcPixels + j * 4;
                u8* dst = dstPixels + j * 4;

                // Interpolate RGBA components using the alpha value of the source pixel.
                u8 alpha = src[3];
                dst[0] = (src[0] * alpha + dst[0] * (255 - alpha)) / 255;
                dst[1] = (src[1] * alpha + dst[1] * (255 - alpha)) / 255;
                dst[2] = (src[2] * alpha + dst[2] * (255 - alpha)) / 255;
                dst[3] = alpha + dst[3] * (255 - alpha) / 255;
            }

            srcPixels += srcStride;
            dstPixels += dstStride;
        }
    }
    else
    {
        // Optimized copy ignoring alpha values, row by row (faster).
        for (int i = 0; i < rows; ++i)
        {
            memcpy(dstPixels, srcPixels, pitch);
            srcPixels += srcStride;
            dstPixels += dstStride;
        }
    }
}

Color Image::getPixel(u32 x, u32 y) const
{
    const u8* pixel = &pixels_[(x + y * width_) * 4];
    return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
}

void Image::setPixel(u32 x, u32 y, const Color& color)
{
    u8* pixel = &pixels_[(x + y * width_) * 4];
    *pixel++ = color[0];
    *pixel++ = color[1];
    *pixel++ = color[2];
    *pixel++ = color[3];
}

const u8* Image::getPixelPtr() const
{
    if (!pixels_.isEmpty())
        return pixels_.data();
    return nullptr;
}

void Image::flipHorizontally()
{
    if (!pixels_.isEmpty())
    {
        size_t row_size = width_ * 4;

        for (size_t y = 0; y < height_; ++y)
        {
            Array<u8>::iterator l = pixels_.begin() + y * row_size;
            Array<u8>::iterator r = pixels_.begin() + (y + 1) * row_size - 4;

            for (size_t x = 0; x < width_ / 2; ++x)
            {
                swap_ranges(l, l + 4, r);

                l += 4;
                r -= 4;
            }
        }
    }
}

void Image::flipVertically()
{
    if (!pixels_.isEmpty())
    {
        size_t row_size = width_ * 4;

        Array<u8>::iterator t = pixels_.begin();
        Array<u8>::iterator b = pixels_.end() - row_size;

        for (size_t y = 0; y < height_ / 2; ++y)
        {
            swap_ranges(t, t + row_size, b);

            t += row_size;
            b -= row_size;
        }
    }
}
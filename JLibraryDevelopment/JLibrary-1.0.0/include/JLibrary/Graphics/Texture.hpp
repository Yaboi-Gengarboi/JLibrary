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
// Texture.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-05 by Justyn Durnford
// Header file for the Texture class.

#pragma once

#include <JLibrary/Graphics/Image.hpp>
#include <JLibrary/Graphics/GlResource.hpp>
#include <JLibrary/System/Integer.hpp>
#include <bitset>

namespace jlib
{
    class InputStream;
    class RenderTarget;
    class RenderTexture;
    class Text;
    class Window;

	// Image living on the graphics card that can be used for drawing.
	class Texture : GlResource
	{
        u32          width_;          
        u32          height_;
        u32          actualWidth_;
        u32          actualHeight_;
        u32          texture_;
        u64          cacheID_;

        // Flags:
        // - [0]: isSmooth
        // - [1]: isSRGB
        // - [2]: isRepeated
        // - [3]: arePixelsFlipped
        // - [4]: hasFrameBufferAttachment
        // - [5]: hasMipmap
        mutable std::bitset<6> flags_;

        friend class Text;
        friend class RenderTexture;
        friend class RenderTarget;

        // Gets a valid image size according to hardware support.
        // This function checks whether the graphics driver supports
        // non power of two sizes or not, and adjusts the size
        // accordingly.
        // The returned size is greater than or equal to the original size.
        static unsigned int getValidSize(unsigned int size);

        // Invalidates the mipmap if one exists.
        // This also resets the texture's minifying function.
        // This function is mainly for internal use by RenderTexture.
        void invalidateMipmap();

        public:

        enum CoordinateType
        {
            Normalized,
            Pixels
        };

        // Default constructor.
        Texture();

        // Copy constructor.
        Texture(const Texture& copy);

        // Copy assignment operator.
        Texture& operator = (const Texture& other);

        // Destructor.
        ~Texture();

        // Creates the texture.
        // If this function fails, the texture is left unchanged.
        // Returns true if successful.
        bool create(u32 width, u32 height);

        // Loads the texture from a file on disk.
        // The area argument can be used to load only a sub-rectangle
        // of the whole image. If you want the entire image then leave
        // the default value (which is an empty IntRect).
        // If the area rectangle crosses the bounds of the image, it
        // is adjusted to fit the image size.
        // The maximum size for a texture depends on the graphics
        // driver and can be retrieved with the getMaximumSize function.
        // If this function fails, the texture is left unchanged.
        // Returns true if successful.
        bool loadFromFile(const std::string& filename, const IntRect& area = IntRect());

        // Loads the texture from a file in memory.
        // The area argument can be used to load only a sub-rectangle
        // of the whole image. If you want the entire image then leave
        // the default value (which is an empty IntRect).
        // If the area rectangle crosses the bounds of the image, it
        // is adjusted to fit the image size.
        // The maximum size for a texture depends on the graphics
        // driver and can be retrieved with the getMaximumSize function.
        // If this function fails, the texture is left unchanged.
        // Returns true if successful.
        bool loadFromMemory(const void* data, std::size_t size, const IntRect& area = IntRect());

        // Loads the texture from a custom stream.
        // The area argument can be used to load only a sub-rectangle
        // of the whole image. If you want the entire image then leave
        // the default value (which is an empty IntRect).
        // If the area rectangle crosses the bounds of the image, it
        // is adjusted to fit the image size.
        // The maximum size for a texture depends on the graphics
        // driver and can be retrieved with the getMaximumSize function.
        // If this function fails, the texture is left unchanged.
        // Returns true if successful.
        bool loadFromStream(InputStream& stream, const IntRect& area = IntRect());

        // Loads the texture from an image.
        // The area argument can be used to load only a sub-rectangle
        // of the whole image. If you want the entire image then leave
        // the default value (which is an empty IntRect).
        // If the area rectangle crosses the bounds of the image, it
        // is adjusted to fit the image size.
        // The maximum size for a texture depends on the graphics
        // driver and can be retrieved with the getMaximumSize function.
        // If this function fails, the texture is left unchanged.
        // Returns true if successful.
        bool loadFromImage(const Image& image, const IntRect& area = IntRect());

        // Returns the width of the texture.
        u32 width() const;

        // Returns the height of the texture.
        u32 height() const;

        // Copies the texture pixels to an image.
        // This function performs a slow operation that downloads
        // the texture's pixels from the graphics card and copies
        // them to a new image, potentially applying transformations
        // to pixels if necessary (texture may be padded or flipped).
        Image copyToImage() const;

        // Update the whole texture from an array of pixels.
        // The pixel array is assumed to have the same size as
        // the area rectangle, and to contain 32-bits RGBA pixels.
        // No additional check is performed on the size of the pixel
        // array, passing invalid arguments will lead to an undefined
        // behavior.
        // This function does nothing if pixels is nullptr or if the
        // texture was not previously created.
        void update(const u8* pixels);

        // Updates a part of the texture from an array of pixels.
        // The size of the pixel array must match the width and
        // height arguments, and it must contain 32-bit RGBA pixels.
        // No additional check is performed on the size of the pixel
        // array or the bounds of the area to update, passing invalid
        // arguments will lead to an undefined behavior.
        // This function does nothing if pixels is nullptr or if the
        // texture was not previously created.
        void update(const u8* pixels, u32 width, u32 height, u32 x, u32 y);

        // Updates a part of this texture from another texture.
        // Although the source texture can be smaller than this texture,
        // this function is usually used for updating the whole texture.
        // The other overload, which has (x, y) additional arguments,
        // is more convenient for updating a sub-area of this texture.
        // No additional check is performed on the size of the passed
        // texture, passing a texture bigger than this texture
        // will lead to an undefined behavior.
        // This function does nothing if either texture was not
        // previously created.
        void update(const Texture& texture);

        // Updates a part of this texture from another texture.
        // No additional check is performed on the size of the texture,
        // passing an invalid combination of texture size and offset
        // will lead to an undefined behavior.
        // This function does nothing if either texture was not
        // previously created.
        void update(const Texture& texture, u32 x, u32 y);

        // Updates the texture from an image.
        // Although the source image can be smaller than the texture,
        // this function is usually used for updating the whole texture.
        // The other overload, which has (x, y) additional arguments,
        // is more convenient for updating a sub-area of the texture.
        // No additional check is performed on the size of the image,
        // passing an image bigger than the texture will lead to an
        // undefined behavior.
        // This function does nothing if the texture was not
        // previously created.
        void update(const Image& image);

        // Updates a part of the texture from an image.
        // No additional check is performed on the size of the image,
        // passing an invalid combination of image size and offset
        // will lead to an undefined behavior.
        // This function does nothing if the texture was not
        // previously created.
        void update(const Image& image, u32 x, u32 y);

        // Updates the texture from the contents of a window.
        // Although the source window can be smaller than the texture,
        // this function is usually used for updating the whole texture.
        // The other overload, which has (x, y) additional arguments,
        // is more convenient for updating a sub-area of the texture.
        // No additional check is performed on the size of the window,
        // passing a window bigger than the texture will lead to an
        // undefined behavior.
        // This function does nothing if either the texture or the window
        // was not previously created.
        void update(const Window& window);

        // Updates a part of the texture from the contents of a window.
        // No additional check is performed on the size of the window,
        // passing an invalid combination of window size and offset
        // will lead to an undefined behavior.
        // This function does nothing if either the texture or the window
        // was not previously created.
        void update(const Window& window, u32 x, u32 y);

        // Enables or disable the smooth filter.
        // When the filter is activated, the texture appears smoother
        // so that pixels are less noticeable. However if you want
        // the texture to look exactly the same as its source file,
        // you should leave it disabled.
        // The smooth filter is disabled by default.
        void setSmooth(bool smooth);

        // Returns true if smooth filter is enabled.
        bool isSmooth() const;

        // Enables or disable conversion from sRGB.
        // When providing texture data from an image file or memory, it can
        // either be stored in a linear color space or an sRGB color space.
        // Most digital images account for gamma correction already, so they
        // would need to be "uncorrected" back to linear color space before
        // being processed by the hardware. The hardware can automatically
        // convert it from the sRGB color space to a linear color space when
        // it gets sampled. When the rendered image gets output to the final
        // framebuffer, it gets converted back to sRGB.
        // After enabling or disabling sRGB conversion, make sure to reload
        // the texture data in order for the setting to take effect.
        // This option is only useful in conjunction with an sRGB capable
        // framebuffer. This can be requested during window creation.
        void setSRGB(bool sRgb);

        // Returns true if the texture source is converted from sRGB or not.
        bool isSRGB() const;

        // Enables or disable repeating.
        // Repeating is involved when using texture coordinates
        // outside the texture rectangle [0, 0, width, height].
        // In this case, if repeat mode is enabled, the whole texture
        // will be repeated as many times as needed to reach the
        // coordinate (for example, if the X texture coordinate is
        // 3 * width, the texture will be repeated 3 times).
        // If repeat mode is disabled, the "extra space" will instead
        // be filled with border pixels.
        // Warning: on very old graphics cards, white pixels may appear
        // when the texture is repeated. With such cards, repeat mode
        // can be used reliably only if the texture has power-of-two
        // dimensions (such as 256x128).
        // Repeating is disabled by default.
        void setRepeated(bool repeated);

        // Returns true if the texture is repeated or not.
        bool isRepeated() const;

        // Generates a mipmap using the current texture data.
        // Mipmaps are pre-computed chains of optimized textures. Each
        // level of texture in a mipmap is generated by halving each of
        // the previous level's dimensions. This is done until the final
        // level has the size of 1x1. The textures generated in this process may
        // make use of more advanced filters which might improve the visual quality
        // of textures when they are applied to objects much smaller than they are.
        // This is known as minification. Because fewer texels (texture elements)
        // have to be sampled from when heavily minified, usage of mipmaps
        // can also improve rendering performance in certain scenarios.=
        // Mipmap generation relies on the necessary OpenGL extension being
        // available. If it is unavailable or generation fails due to another
        // reason, this function will return false. Mipmap data is only valid from
        // the time it is generated until the next time the base level image is
        // modified, at which point this function will have to be called again to
        // regenerate it.
        // Returns true if successful.
        bool generateMipmap();

        // Swaps the contents of this texture with those of another.
        void swap(Texture& other);

        // Gets the underlying OpenGL handle of the texture.
        // You shouldn't need to use this function, unless you have
        // very specific stuff to implement that SFML doesn't support,
        // or implement a temporary workaround until a bug is fixed.
        u32 getNativeHandle() const;

        // Binds a texture for rendering.
        // This function is not part of the graphics API, it mustn't be
        // used when drawing SFML entities. It must be used only if you
        // mix sf::Texture with OpenGL code.
        // The coordinateType argument controls how texture
        // coordinates will be interpreted. If Normalized (the default), they
        // must be in range [0 .. 1], which is the default way of handling
        // texture coordinates with OpenGL. If Pixels, they must be given
        // in pixels (range [0 .. size]). This mode is used internally by
        // the graphics classes of SFML, it makes the definition of texture
        // coordinates more intuitive for the high-level API, users don't need
        // to compute normalized values.
        static void bind(const Texture* texture, CoordinateType coordinateType = Normalized);

        // Gets the maximum texture size allowed.
        /// This maximum size is defined by the graphics driver.
        /// You can expect a value of 512 pixels for low-end graphics
        /// card, and up to 8192 pixels or more for newer hardware.
        static u32 getMaximumSize();
	};
}
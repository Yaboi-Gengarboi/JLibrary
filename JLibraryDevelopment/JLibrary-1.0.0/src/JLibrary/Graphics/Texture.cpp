// JLibraryDevelopment
// Texture.cpp
// Created on 2021-07-13 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Source file for the Texture class.

#include <JLibrary/Graphics/Texture.hpp>
#include <JLibrary/Graphics/TextureSaver.hpp>
#include <JLibrary/Math/Matrix.hpp>
#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
#include <JLibrary/Utility/Array.hpp>
#include <JLibrary/Window/Window.hpp>
using namespace jlib;

#include <cassert>

#include <cstring>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <utility>
using std::swap;

namespace
{
    Mutex idMutex;
    Mutex maximumSizeMutex;

    // Thread-safe unique identifier generator,
    // is used for states cache (see RenderTarget).
    u64 getUniqueID()
    {
        Lock lock(idMutex);
        static u64 id = 1; // start at 1, zero is "no texture."
        return id++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

u32 Texture::getValidSize(u32 size)
{
    // If hardware supports NPOT textures, then just return the unmodified size.
    if (GLEXT_texture_non_power_of_two)
        return size;
    // If hardware doesn't support NPOT textures, we calculate the nearest power of two.
    u32 powerOfTwo = 1;
    while (powerOfTwo < size)
        powerOfTwo *= 2;

    return powerOfTwo;
}

void Texture::invalidateMipmap()
{
    if (!flags_[5])
        return;

    TransientContextLock lock;

    // Make sure that the current texture binding will be preserved.
    TextureSaver saver;

    glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));

    flags_[5] = false;
}

Texture::Texture()
{
    width_ = 0;
    height_ = 0;
    actualWidth_ = 0;
    actualHeight_ = 0;
    texture_ = 0;
    cacheID_ = 0;
}

Texture::Texture(const Texture& other)
{
    width_ = 0;
    height_ = 0;
    actualWidth_ = 0;
    actualHeight_ = 0;
    texture_ = 0;
    cacheID_ = getUniqueID();

    flags_[0] = other.flags_[0];
    flags_[1] = other.flags_[1];
    flags_[2] = other.flags_[2];
    flags_[3] = false;
    flags_[4] = false;
    flags_[5] = false;

    if (other.texture_ != 0)
    {
        if (create(other.width_, other.height_))
            update(other);
        else
            cout << "Failed to copy texture, failed to create new texture." << endl;
    }
}

Texture& Texture::operator = (const Texture& other)
{
    Texture temp(other);
    swapWith(temp);
    return *this;
}

Texture::~Texture()
{
    // Destroy the OpenGL texture.
    if (texture_ != 0)
    {
        TransientContextLock lock;

        GLuint texture = static_cast<GLuint>(texture_);
        glCheck(glDeleteTextures(1, &texture));
    }
}

bool Texture::create(u32 width, u32 height)
{
    // Check if texture parameters are valid before creating it.
    if ((width == 0) || (height == 0))
    {
        cout << "Failed to create texture, invalid size (" << width << "x" << height << ")" << endl;
        return false;
    }

    TransientContextLock lock;

    // Make sure that extensions are initialized.
    ensureExtensionsInit();

    // Compute the internal texture dimensions depending on NPOT textures support.
    u32 actualWidth = getValidSize(width);
    u32 actualHeight = getValidSize(height);

    // Check the maximum texture size.
    u32 maxSize = getMaximumSize();
    if ((actualWidth > maxSize) || (actualHeight > maxSize))
    {
        cout << "Failed to create texture, its internal size is too high "
             << "(" << actualWidth << "x" << actualHeight << ", "
             << "maximum is " << maxSize << "x" << maxSize << ")" << endl;
        return false;
    }

    // All the validity checks passed, we can store the new texture settings.
    width_ = width;
    height_ = height;
    actualWidth_ = actualWidth;
    actualHeight_ = actualHeight;
    flags_[3] = false;
    flags_[4] = false;

    // Create the OpenGL texture if it doesn't exist yet.
    if (texture_ != 0)
    {
        GLuint texture;
        glCheck(glGenTextures(1, &texture));
        texture_ = static_cast<u32>(texture);
    }

    // Make sure that the current texture binding will be preserved.
    TextureSaver saver;

    static bool textureEdgeClamp = GLEXT_texture_edge_clamp || GLEXT_GL_VERSION_1_2 || Context::isExtensionAvailable("GL_EXT_texture_edge_clamp");

    if (!flags_[2] && !textureEdgeClamp)
    {
        static bool warned = false;

        if (!warned)
        {
            cout << "OpenGL extension SGIS_texture_edge_clamp unavailable" << endl;
            cout << "Artifacts may occur along texture edges" << endl;
            cout << "Ensure that hardware acceleration is enabled if available" << endl;

            warned = true;
        }
    }

    static bool textureSrgb = GLEXT_texture_sRGB;

    if (flags_[1] && !textureSrgb)
    {
        static bool warned = false;

        if (!warned)
        {
            #ifndef JLIB_OPENGL_ES
                cout << "OpenGL extension EXT_texture_sRGB unavailable" << endl;
            #else
                cout << "OpenGL ES extension EXT_sRGB unavailable" << endl;
            #endif

            cout << "Automatic sRGB to linear conversion disabled" << endl;

            warned = true;
        }

        flags_[1] = false;
    }

    // Initialize the texture.
    glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
    glCheck(glTexImage2D(GL_TEXTURE_2D, 0, (flags_[1] ? GLEXT_GL_SRGB8_ALPHA8 : GL_RGBA), actualWidth_, actualHeight_, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, flags_[2] ? GL_REPEAT : (textureEdgeClamp ? GLEXT_GL_CLAMP_TO_EDGE : GLEXT_GL_CLAMP)));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, flags_[2] ? GL_REPEAT : (textureEdgeClamp ? GLEXT_GL_CLAMP_TO_EDGE : GLEXT_GL_CLAMP)));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));
    cacheID_ = getUniqueID();

    flags_[5] = false;

    return true;
}

bool Texture::loadFromFile(const string& filename, const IntRect& area)
{
    Image image;
    return image.loadFromFile(filename) && loadFromImage(image, area);
}

bool Texture::loadFromMemory(const void* data, size_t size, const IntRect& area)
{
    Image image;
    return image.loadFromMemory(data, size) && loadFromImage(image, area);
}

bool Texture::loadFromStream(InputStream& stream, const IntRect& area)
{
    Image image;
    return image.loadFromStream(stream) && loadFromImage(image, area);
}

bool Texture::loadFromImage(const Image& image, const IntRect& area)
{
    // Retrieve the image size.
    int width = static_cast<int>(image.width());
    int height = static_cast<int>(image.height());

    // Load the entire image if the source area is either empty or contains the whole image.
    if (area.width == 0 || (area.height == 0) ||
        ((area.vertex.x <= 0) && (area.vertex.y <= 0) && (area.width >= width) && (area.height >= height)))
    {
        // Load the entire image.
        if (create(image.width(), image.height()))
        {
            update(image);
            return true;
        }
        else
            return false;
    }
    else
    {
        // Load a sub-area of the image.

        // Adjust the rectangle to the size of the image.
        IntRect rectangle = area;
        if (rectangle.vertex.x < 0) 
            rectangle.vertex.x = 0;
        if (rectangle.vertex.y < 0)
            rectangle.vertex.y = 0;
        if (rectangle.vertex.x + rectangle.width > width) 
            rectangle.width = width - rectangle.vertex.x;
        if (rectangle.vertex.y + rectangle.height > height) 
            rectangle.height = height - rectangle.vertex.y;

        // Create the texture and upload the pixels.
        if (create(rectangle.width, rectangle.height))
        {
            TransientContextLock lock;

            // Make sure that the current texture binding will be preserved.
            TextureSaver saver;

            // Copy the pixels to the texture, row by row.
            const u8* pixels = image.getPixelPtr() + 4 * (rectangle.vertex.x + (width * rectangle.vertex.y));
            glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
            for (i32 i = 0; i < rectangle.height; ++i)
            {
                glCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, rectangle.width, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels));
                pixels += 4 * width;
            }

            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));
            flags_[5] = false;

            // Force an OpenGL flush, so that the texture will appear updated
            // in all contexts immediately (solves problems in multi-threaded apps).
            glCheck(glFlush());

            return true;
        }
    }

    return false;
}

u32 Texture::width() const
{
    return width_;
}

u32 Texture::height() const
{
    return height_;
}

Image Texture::copyToImage() const
{
    // Easy case: empty texture.
    if (!texture_)
        return Image();

    TransientContextLock lock;

    // Make sure that the current texture binding will be preserved.
    TextureSaver saver;

    // Create an array of pixels.
    Array<u8> pixels(width_ * height_ * 4);

    #ifdef JLIB_OPENGL_ES

        // OpenGL ES doesn't have the glGetTexImage function, the only way to read
        // from a texture is to bind it to a FBO and use glReadPixels.
        GLuint frameBuffer = 0;
        glCheck(GLEXT_glGenFramebuffers(1, &frameBuffer));
        if (frameBuffer)
        {
            GLint previousFrameBuffer;
            glCheck(glGetIntegerv(GLEXT_GL_FRAMEBUFFER_BINDING, &previousFrameBuffer));

            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, frameBuffer));
            glCheck(GLEXT_glFramebufferTexture2D(GLEXT_GL_FRAMEBUFFER, GLEXT_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0));
            glCheck(glReadPixels(0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]));
            glCheck(GLEXT_glDeleteFramebuffers(1, &frameBuffer));

            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, previousFrameBuffer));
        }

    #else

        if ((width_ == actualWidth_) && (height_ == actualHeight_) && !flags_[3])
        {
            // Texture is not padded nor flipped, we can use a direct copy.
            glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
            glCheck(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]));
        }
        else
        {
            // Texture is either padded or flipped, we have to use a slower algorithm.

            // All the pixels will first be copied to a temporary array
            Array<u8> allPixels(actualWidth_ * actualHeight_ * 4);
            glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
            glCheck(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &allPixels[0]));

            // Then we copy the useful pixels from the temporary array to the final one.
            const u8* src = allPixels.data();
            u8* dst = &pixels[0];
            int srcPitch = actualWidth_ * 4;
            int dstPitch = width_ * 4;

            // Handle the case where source pixels are flipped vertically.
            if (flags_[3])
            {
                src += srcPitch * (height_ - 1);
                srcPitch = -srcPitch;
            }

            for (u32 i = 0; i < height_; ++i)
            {
                memcpy(dst, src, dstPitch);
                src += srcPitch;
                dst += dstPitch;
            }
        }

    #endif // SFML_OPENGL_ES

    // Create the image.
    Image image;
    image.create(width_, height_, &pixels[0]);

    return image;
}

void Texture::update(const u8* pixels)
{
    // Update the whole texture.
    update(pixels, width_, height_, 0, 0);
}

void Texture::update(const u8* pixels, u32 width, u32 height, u32 x, u32 y)
{
    assert(x + width <= width_);
    assert(y + height <= height_);

    if (pixels && texture_)
    {
        TransientContextLock lock;

        // Make sure that the current texture binding will be preserved.
        TextureSaver saver;

        // Copy pixels from the given array to the texture.
        glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
        glCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));
        flags_[3] = false;
        flags_[5] = false;
        cacheID_ = getUniqueID();

        // Force an OpenGL flush, so that the texture data will appear updated
        // in all contexts immediately (solves problems in multi-threaded apps).
        glCheck(glFlush());
    }
}

void Texture::update(const Texture& texture)
{
    // Update the whole texture.
    update(texture, 0, 0);
}

void Texture::update(const Texture& texture, u32 x, u32 y)
{
    assert(x + texture.width_ <= width_);
    assert(y + texture.height_ <= height_);

    if (!texture_ || !texture.texture_)
        return;

    #ifndef JLIB_OPENGL_ES

        {
            TransientContextLock lock;

            // Make sure that extensions are initialized.
            ensureExtensionsInit();
        }

        if (GLEXT_framebuffer_object && GLEXT_framebuffer_blit)
        {
            TransientContextLock lock;

            // Save the current bindings so we can restore them after we are done.
            GLint readFramebuffer = 0;
            GLint drawFramebuffer = 0;

            glCheck(glGetIntegerv(GLEXT_GL_READ_FRAMEBUFFER_BINDING, &readFramebuffer));
            glCheck(glGetIntegerv(GLEXT_GL_DRAW_FRAMEBUFFER_BINDING, &drawFramebuffer));

            // Create the framebuffers.
            GLuint sourceFrameBuffer = 0;
            GLuint destFrameBuffer = 0;
            glCheck(GLEXT_glGenFramebuffers(1, &sourceFrameBuffer));
            glCheck(GLEXT_glGenFramebuffers(1, &destFrameBuffer));

            if (!sourceFrameBuffer || !destFrameBuffer)
            {
                cout << "Cannot copy texture, failed to create a frame buffer object" << endl;
                return;
            }

            // Link the source texture to the source frame buffer.
            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_READ_FRAMEBUFFER, sourceFrameBuffer));
            glCheck(GLEXT_glFramebufferTexture2D(GLEXT_GL_READ_FRAMEBUFFER, GLEXT_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.texture_, 0));

            // Link the destination texture to the destination frame buffer.
            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_DRAW_FRAMEBUFFER, destFrameBuffer));
            glCheck(GLEXT_glFramebufferTexture2D(GLEXT_GL_DRAW_FRAMEBUFFER, GLEXT_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0));

            // A final check, just to be sure...
            GLenum sourceStatus;
            glCheck(sourceStatus = GLEXT_glCheckFramebufferStatus(GLEXT_GL_READ_FRAMEBUFFER));

            GLenum destStatus;
            glCheck(destStatus = GLEXT_glCheckFramebufferStatus(GLEXT_GL_DRAW_FRAMEBUFFER));

            if ((sourceStatus == GLEXT_GL_FRAMEBUFFER_COMPLETE) && (destStatus == GLEXT_GL_FRAMEBUFFER_COMPLETE))
            {
                // Blit the texture contents from the source to the destination texture.
                glCheck(GLEXT_glBlitFramebuffer(
                    0, texture.flags_[3] ? texture.height_ : 0, texture.width_, texture.flags_[3] ? 0 : texture.height_,
                    x, y, x + texture.width_, y + texture.height_, 
                    GL_COLOR_BUFFER_BIT, GL_NEAREST
                ));
            }
            else
                cout << "Cannot copy texture, failed to link texture to frame buffer" << endl;

            // Restore previously bound framebuffers
            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_READ_FRAMEBUFFER, readFramebuffer));
            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_DRAW_FRAMEBUFFER, drawFramebuffer));

            // Delete the framebuffers
            glCheck(GLEXT_glDeleteFramebuffers(1, &sourceFrameBuffer));
            glCheck(GLEXT_glDeleteFramebuffers(1, &destFrameBuffer));

            // Make sure that the current texture binding will be preserved.
            TextureSaver saver;

            // Set the parameters of this texture.
            glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));
            flags_[3] = false;
            flags_[5] = false;
            cacheID_ = getUniqueID();

            // Force an OpenGL flush, so that the texture data will appear updated
            // in all contexts immediately (solves problems in multi-threaded apps).
            glCheck(glFlush());

            return;
        }

    #endif // JLIB_OPENGL_ES

    update(texture.copyToImage(), x, y);
}

void Texture::update(const Image& image)
{
    // Update the whole texture.
    update(image.getPixelPtr(), image.width(), image.height(), 0, 0);
}

void Texture::update(const Image& image, u32 x, u32 y)
{
    update(image.getPixelPtr(), image.width(), image.height(), x, y);
}

void Texture::update(const Window& window)
{
    update(window, 0, 0);
}

void Texture::update(const Window& window, u32 x, u32 y)
{
    assert(x + window.getWidth() <= width_);
    assert(y + window.getHeight() <= height_);

    if (texture_ && window.setActive(true))
    {
        TransientContextLock lock;

        // Make sure that the current texture binding will be preserved.
        TextureSaver saver;

        // Copy pixels from the back-buffer to the texture.
        glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
        glCheck(glCopyTexSubImage2D(GL_TEXTURE_2D, 0, x, y, 0, 0, window.getWidth(), window.getHeight()));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));
        flags_[3] = true;
        flags_[5] = false;
        cacheID_ = getUniqueID();

        // Force an OpenGL flush, so that the texture will appear updated
        // in all contexts immediately (solves problems in multi-threaded apps).
        glCheck(glFlush());
    }
}

void Texture::setSmooth(bool smooth)
{
    if (smooth != flags_[0])
    {
        flags_[0] = smooth;

        if (texture_)
        {
            TransientContextLock lock;

            // Make sure that the current texture binding will be preserved.
            TextureSaver saver;

            glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));

            if (flags_[5])
                glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
            else
                glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR : GL_NEAREST));
        }
    }
}

bool Texture::isSmooth() const
{
    return flags_[0];
}

void Texture::setSRGB(bool sRgb)
{
    flags_[1] = sRgb;
}

bool Texture::isSRGB() const
{
    return flags_[1];
}

void Texture::setRepeated(bool repeated)
{
    if (repeated != flags_[2])
    {
        flags_[2] = repeated;

        if (texture_)
        {
            TransientContextLock lock;

            // Make sure that the current texture binding will be preserved.
            TextureSaver saver;

            static bool textureEdgeClamp = GLEXT_texture_edge_clamp;

            if (!flags_[2] && !textureEdgeClamp)
            {
                static bool warned = false;

                if (!warned)
                {
                    cout << "OpenGL extension SGIS_texture_edge_clamp unavailable" << endl;
                    cout << "Artifacts may occur along texture edges" << endl;
                    cout << "Ensure that hardware acceleration is enabled if available" << endl;

                    warned = true;
                }
            }

            glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, flags_[2] ? GL_REPEAT : (textureEdgeClamp ? GLEXT_GL_CLAMP_TO_EDGE : GLEXT_GL_CLAMP)));
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, flags_[2] ? GL_REPEAT : (textureEdgeClamp ? GLEXT_GL_CLAMP_TO_EDGE : GLEXT_GL_CLAMP)));
        }
    }
}

bool Texture::isRepeated() const
{
    return flags_[2];
}

bool Texture::generateMipmap()
{
    if (texture_)
        return false;

    TransientContextLock lock;

    // Make sure that extensions are initialized.
    ensureExtensionsInit();

    if (!GLEXT_framebuffer_object)
        return false;

    // Make sure that the current texture binding will be preserved.
    TextureSaver saver;

    glCheck(glBindTexture(GL_TEXTURE_2D, texture_));
    glCheck(GLEXT_glGenerateMipmap(GL_TEXTURE_2D));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags_[0] ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));

    flags_[5] = true;

    return true;
}

void Texture::swapWith(Texture& other)
{
    swap(width_, other.width_);
    swap(height_, other.height_);
    swap(actualWidth_, other.actualWidth_);
    swap(actualHeight_, other.actualHeight_);
    swap(texture_, other.texture_);
    swap(flags_, other.flags_);

    cacheID_ = getUniqueID();
    other.cacheID_ = getUniqueID();
}

u32 Texture::getNativeHandle() const
{
    return texture_;
}

void Texture::bind(const Texture* texture, CoordinateType coordinateType)
{
    TransientContextLock lock;

    if (texture && texture->texture_)
    {
        // Bind the texture,
        glCheck(glBindTexture(GL_TEXTURE_2D, texture->texture_));

        // Check if we need to define a special texture matrix.
        if ((coordinateType == Pixels) || texture->flags_[3])
        {
            Matrix<GLfloat, 4, 4> mat =
            {
                { 1.f, 0.f, 0.f, 0.f },
                { 0.f, 1.f, 0.f, 0.f },
                { 0.f, 0.f, 1.f, 0.f },
                { 0.f, 0.f, 0.f, 1.f }
            };

            // If non-normalized coordinates (= pixels) are requested, we need to
            // setup scale factors that convert the range [0 .. size] to [0 .. 1].
            if (coordinateType == Pixels)
            {
                mat[0] = 1.f / texture->actualWidth_;
                mat[5] = 1.f / texture->actualHeight_;
            }

            // If pixels are flipped we must invert the Y axis.
            if (texture->flags_[3])
            {
                mat[5] = -mat[5];
                mat[13] = static_cast<float>(texture->height_) / texture->actualHeight_;
            }

            // Load the matrix.
            glCheck(glMatrixMode(GL_TEXTURE));
            glCheck(glLoadMatrixf(mat.begin()));

            // Go back to model-view mode (jlib::RenderTarget relies on it).
            glCheck(glMatrixMode(GL_MODELVIEW));
        }
    }
    else
    {
        // Bind no texture.
        glCheck(glBindTexture(GL_TEXTURE_2D, 0));

        // Reset the texture matrix.
        glCheck(glMatrixMode(GL_TEXTURE));
        glCheck(glLoadIdentity());

        // Go back to model-view mode (jlib::RenderTarget relies on it).
        glCheck(glMatrixMode(GL_MODELVIEW));
    }
}

u32 Texture::getMaximumSize()
{
    Lock lock(maximumSizeMutex);

    static bool checked = false;
    static GLint size = 0;

    if (!checked)
    {
        checked = true;
        TransientContextLock lock;
        glCheck(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size));
    }

    return static_cast<u32>(size);
}
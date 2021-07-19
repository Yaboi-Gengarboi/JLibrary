// JLibraryDevelopment
// RenderTexture.cpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Source file for the RenderTexture class.

#include <JLibrary/Graphics/RenderTexture.hpp>
#include <JLibrary/Graphics/RenderTextureImplFBO.hpp>
#include <JLibrary/Graphics/RenderTextureImplDefault.hpp>
using namespace jlib;

#include <iostream>
using std::cout;
using std::endl;

RenderTexture::RenderTexture()
{
	impl_ = nullptr;
}

RenderTexture::~RenderTexture()
{
	delete impl_;
}

bool RenderTexture::create(u32 width, u32 height, const ContextSettings& settings)
{
    // Create the texture.
    if (!texture_.create(width, height))
    {
        cout << "Impossible to create render texture (failed to create the target texture)." << endl;
        return false;
    }

    // We disable smoothing by default for render textures.
    setSmooth(false);

    // Create the implementation.
    delete impl_;
    if (RenderTextureImplFBO::isAvailable())
    {
        // Use frame-buffer object (FBO).
        impl_ = new RenderTextureImplFBO;

        // Mark the texture as being a framebuffer object attachment.
        texture_.flags_[4] = true;
    }
    else // Use default implementation.
        impl_ = new RenderTextureImplDefault;

    // Initialize the render texture.
    if (!impl_->create(width, height, texture_.texture_, settings))
        return false;

    // We can now initialize the render target part.
    RenderTarget::initialize();

    return true;
}

u32 RenderTexture::getMaximumAntialiasingLevel()
{
    if (RenderTextureImplFBO::isAvailable())
        return RenderTextureImplFBO::getMaximumAntialiasingLevel();
    else
        return RenderTextureImplDefault::getMaximumAntialiasingLevel();
}

bool RenderTexture::isSmooth() const
{
    return texture_.isSmooth();
}

void RenderTexture::setSmooth(bool smooth)
{
    texture_.setSmooth(smooth);
}

bool RenderTexture::isRepeated() const
{
    return texture_.isRepeated();
}

void RenderTexture::setRepeated(bool repeated)
{
    texture_.setRepeated(repeated);
}

bool RenderTexture::generateMipmap()
{
    return texture_.generateMipmap();
}

bool RenderTexture::setActive(bool active)
{
    bool result = impl_ && impl_->activate(active);

    // Update RenderTarget tracking.
    if (result)
        RenderTarget::setActive(active);

    return result;
}

void RenderTexture::display()
{
    // Update the target texture.
    if (impl_ && (RenderTextureImplFBO::isAvailable() || setActive(true)))
    {
        impl_->updateTexture(texture_.texture_);
        texture_.flags_[3] = true;
        texture_.invalidateMipmap();
    }
}

u32 RenderTexture::getWidth() const
{
    return texture_.width_;
}

u32 RenderTexture::getHeight() const
{
    return texture_.height_;
}

const Texture& RenderTexture::getTexture() const
{
    return texture_;
}
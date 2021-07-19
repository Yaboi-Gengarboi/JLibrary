// JLibraryDevelopment
// RenderTextureImplDefault.cpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Source file for the RenderTextureImplDefault class.

#include <JLibrary/Graphics/RenderTextureImplDefault.hpp>
#include <JLibrary/Graphics/TextureSaver.hpp>
using namespace jlib;

bool RenderTextureImplDefault::create(u32 width, u32 height, u32 textureID, 
									  const ContextSettings& settings)
{
    // Store the dimensions.
    width = width_;
    height = height_;

    // Create the in-memory OpenGL context.
    context_ = new Context(settings, width, height);

    return true;
}

bool RenderTextureImplDefault::activate(bool active)
{
    return context_->setActive(active);
}

void RenderTextureImplDefault::updateTexture(u32 textureID)
{
    // Make sure that the current texture binding will be preserved.
    TextureSaver saver;

    // Copy the rendered pixels to the texture.
    glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
    glCheck(glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, width_, height_));
}

RenderTextureImplDefault::RenderTextureImplDefault()
{
    context_ = nullptr;
    width_ = 0;
    height_ = 0;
}

RenderTextureImplDefault::~RenderTextureImplDefault()
{
    // Destroy the context.
    delete context_;
}

u32 RenderTextureImplDefault::getMaximumAntialiasingLevel()
{
    // If the system is so old that it doesn't support FBOs, chances are it is
    // also using either a software renderer or some CPU emulated support for AA.
    // In order to not cripple performance in this rare case, we just return 0 here.
    return 0;
}

u32 RenderTextureImplDefault::getWidth() const
{
    return width_;
}

u32 RenderTextureImplDefault::getHeight() const
{
    return height_;
}
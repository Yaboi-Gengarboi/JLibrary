// JLibraryDevelopment
// RenderTextureImplDefault.hpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Header file for the RenderTextureImplDefault class.

#pragma once

#include <JLibrary/Graphics/Context.hpp>
#include <JLibrary/Graphics/GlResource.hpp>
#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Graphics/RenderTextureImpl.hpp>

namespace jlib
{
	class RenderTextureImplDefault : public RenderTextureImpl, public RenderTarget
	{
        Context* context_;
        u32 width_;
        u32 height_; 

        // Creates the render texture implementation.
        // Returns true if successful.
        virtual bool create(u32 width, u32 height, u32 textureID, const ContextSettings& settings);

        // Activates or deactivates the render texture for rendering.
        // Returns true if successful.
        virtual bool activate(bool active);

        // Updates the pixels of the target texture.
        virtual void updateTexture(u32 textureID);

        public:

        // Default constructor.
        RenderTextureImplDefault();

        // Destructor.
        ~RenderTextureImplDefault();

        // Gets the maximum anti-aliasing level supported by the system.
        static u32 getMaximumAntialiasingLevel();

        // Returns the width of the rendering region of the texture.
        u32 getWidth() const;

        // Returns the height of the rendering region of the texture.
        u32 getHeight() const;
	};
}
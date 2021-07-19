// JLibraryDevelopment
// RenderTextureImplFBO.hpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Header file for the RenderTextureImplFBO class.

#pragma once

#include <JLibrary/Graphics/Context.hpp>
#include <JLibrary/Graphics/GlResource.hpp>
#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Graphics/RenderTextureImpl.hpp>
#include <map>

namespace jlib
{
    class RenderTextureImplFBO : public RenderTextureImpl, GlResource
    {
        std::map<u64, u32> frameBuffers_;            // OpenGL frame buffer objects per context
        std::map<u64, u32> multisampleFrameBuffers_; // Optional per-context OpenGL frame buffer objects with multisample attachments
        u32                depthStencilBuffer_;      // Optional depth/stencil buffer attached to the frame buffer
        u32                colorBuffer_;             // Optional multisample color buffer attached to the frame buffer
        u32                width_;                   // Width of the attachments
        u32                height_;                  // Height of the attachments
        Context*           context_;                 // Backup OpenGL context, used when none already exist
        u32                textureID_;               // The ID of the texture to attach to the FBO
        bool               multisample_;             // Whether we have to create a multisample frame buffer as well
        bool               stencil_;                 // Whether we have stencil attachment

        // Creates the render texture implementation.
        // Returns true if successful.
        virtual bool create(u32 width, u32 height, u32 textureId, const ContextSettings& settings);

        // Creates an FBO in the current context.
        // Returns true if successful.
        bool createFrameBuffer();

        // Activates or deactivates the render texture for rendering.
        // Returns true if successful.
        virtual bool activate(bool active);

        // Updates the pixels of the target texture.
        virtual void updateTexture(u32 textureID);

        public:

        // Default constructor.
        RenderTextureImplFBO();

        // Destructor.
        ~RenderTextureImplFBO();

        // Returns true if the system supports FBOs.
        static bool isAvailable();

        // Gets the maximum anti-aliasing level supported by the system.
        static u32 getMaximumAntialiasingLevel();

        // Returns the width of the rendering region of the texture.
        u32 getWidth() const;

        // Returns the height of the rendering region of the texture.
        u32 getHeight() const;

        // Unbinds the currently bound FBO.
        static void unbind();
    };
}
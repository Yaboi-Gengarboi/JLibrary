// JLibraryDevelopment
// RenderTexture.hpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the RenderTexture class.

#pragma once

#include <JLibrary/Graphics/Context.hpp>
#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Graphics/Texture.hpp>

namespace jlib
{
	class RenderTextureImpl;

	class RenderTexture : public RenderTarget
	{
		RenderTextureImpl* impl_;
		Texture texture_;

		public:

		// Default constructor.
		// Constructs an empty, invalid render - texture.You must
		// call create to have a valid render-texture.
		RenderTexture();

		// Destructor.
		virtual ~RenderTexture();

		// Before calling this function, the render-texture is in
		// an invalid state, thus it is mandatory to call it before
		// doing anything with the render-texture.
		// The last parameter, settings, is useful if you want to enable
		// multi-sampling or use the render-texture for OpenGL rendering that
		// requires a depth or stencil buffer. Otherwise it is unnecessary, and
		// you should leave this parameter at its default value.
		// Returns true if successful.
		bool create(u32 width, u32 height, const ContextSettings& settings = ContextSettings());

        // Gets the maximum anti-aliasing level supported by the system.
        static u32 getMaximumAntialiasingLevel();

        // Returns true if the smooth filtering is enabled.
        bool isSmooth() const;

        // Enables or disables texture smoothing.
        // This function is similar to Texture::setSmooth.
        // This parameter is disabled by default.
        void setSmooth(bool smooth);

        // Returns true if the texture is repeated.
        bool isRepeated() const;

        // Enables or disables texture repeating.
        // This function is similar to Texture::setRepeated.
        // This parameter is disabled by default.
        void setRepeated(bool repeated);

        // Generates a mipmap using the current texture data.
        // This function is similar to Texture::generateMipmap and operates
        // on the texture used as the target for drawing.
        // Be aware that any draw operation may modify the base level image data.
        // For this reason, calling this function only makes sense after all
        // drawing is completed and display has been called. Not calling display
        // after subsequent drawing will lead to undefined behavior if a mipmap
        // had been previously generated.
        // Returns true if successful.
        bool generateMipmap();

        // Activates or deactivates the render-texture for rendering.
        // This function makes the render-texture's context current for
        // future OpenGL rendering operations (so you shouldn't care
        // about it if you're not doing direct OpenGL stuff).
        // Only one context can be current in a thread, so if you
        // want to draw OpenGL geometry to another render target
        // (like a RenderWindow) don't forget to activate it again.
        // Returns true if successful.
        bool setActive(bool active = true);

        // Updates the contents of the target texture.
        // This function updates the target texture with what
        // has been drawn so far. Like for windows, calling this
        // function is mandatory at the end of rendering. Not calling
        // it may leave the texture in an undefined state.
        void display();

        // Returns the width of the rendering region of the texture.
        virtual u32 getWidth() const;

        // Returns the height of the rendering region of the texture.
        virtual u32 getHeight() const;

        // Gets a read-only reference to the target texture.
        // After drawing to the render-texture and calling Display,
        // you can retrieve the updated texture using this function,
        // and draw it using a sprite (for example).
        // The internal jlib::Texture of a render-texture is always the
        // same instance, so that it is possible to call this function
        // once and keep a reference to the texture even after it is
        // modified.
        const Texture& getTexture() const;
	};
} 